//  Copyright (c) 2017-2018 The SWP Authors. All rights reserved.
//  Created on: 2017年2月12日 Author: kerry
#include <mysql.h>
#include "logic/logic_unit.h"
#include "history/history_db.h"
#include "basic/basic_util.h"

namespace history_logic {

HistoryDB::HistoryDB(config::FileConfig* config) {
  mysql_engine_ = base_logic::DataEngine::Create(MYSQL_TYPE);
  mysql_engine_->InitParam(config->mysql_db_list_);
}

HistoryDB::~HistoryDB() {
  if (mysql_engine_) {
    delete mysql_engine_;
    mysql_engine_ = NULL;
  }
}

bool HistoryDB::OnHistroyTradesRecord(
    std::list<swp_logic::TradesPosition>* list) {
  bool r = false;
  base_logic::DictionaryValue* dict = new base_logic::DictionaryValue();

  std::string sql;
  sql = "call proc_GetHistiryTrades()";
  base_logic::ListValue *listvalue;
  dict->SetString(L"sql", sql);
  r = mysql_engine_->ReadData(0, (base_logic::Value *) (dict),
                              CallHistroyTradesTradesRecord);
  if (!r)
    return false;
  dict->GetList(L"resultvalue", &listvalue);
  while (listvalue->GetSize()) {
    swp_logic::TradesPosition trades;
    base_logic::Value *result_value;
    listvalue->Remove(0, &result_value);
    base_logic::DictionaryValue *dict_result_value =
        (base_logic::DictionaryValue *) (result_value);
    trades.ValueSerialization(dict_result_value);
    list->push_back(trades);
    delete dict_result_value;
    dict_result_value = NULL;
  }

  if (dict) {
    delete dict;
    dict = NULL;
  }
  return true;
}

void HistoryDB::CallHistroyTradesTradesRecord(void* param,
                                              base_logic::Value* value) {
  base_logic::DictionaryValue *dict = (base_logic::DictionaryValue *) (value);
  base_logic::ListValue *list = new base_logic::ListValue();
  base_storage::DBStorageEngine *engine =
      (base_storage::DBStorageEngine *) (param);
  MYSQL_ROW rows;
  int32 num = engine->RecordCount();
  if (num > 0) {
    while (rows = (*(MYSQL_ROW *) (engine->FetchRows())->proc)) {
      base_logic::DictionaryValue *info_value =
          new base_logic::DictionaryValue();

      if (rows[0] != NULL)
        info_value->SetBigInteger(L"tid", atoll(rows[0]));

      if (rows[1] != NULL)
        info_value->SetBigInteger(L"uid", atoll(rows[1]));

      if (rows[2] != NULL)
        info_value->SetInteger(L"code_id", atoi(rows[2]));

      if (rows[3] != NULL)
        info_value->SetInteger(L"buy_sell", atoi(rows[3]));

      if (rows[4] != NULL)
        info_value->SetString(L"symbol", rows[4]);

      if (rows[5] != NULL)
        info_value->SetString(L"name", rows[5]);

      if (rows[6] != NULL)
        info_value->SetInteger(L"close_type", atoi(rows[6]));

      if (rows[7] != NULL)
        info_value->SetBigInteger(L"amount", atoll(rows[7]));

      if (rows[8] != NULL)
        info_value->SetBigInteger(L"open_position_time", atoll(rows[8]));

      if (rows[9] != NULL)
        info_value->SetBigInteger(L"close_position_time", atoll(rows[9]));

      if (rows[10] != NULL)
        info_value->SetReal(L"gross_profit", atof(rows[10]));

      if (rows[11] != NULL)
        info_value->SetReal(L"open_price", atof(rows[11]));

      if (rows[12] != NULL)
        info_value->SetReal(L"open_cost", atof(rows[12]));

      if (rows[13] != NULL)
        info_value->SetReal(L"open_charge", atof(rows[13]));

      if (rows[14] != NULL)
        info_value->SetReal(L"close_price", atof(rows[14]));

      if (rows[15] != NULL)
        info_value->SetReal(L"pos_limit", atof(rows[15]));

      if (rows[16] != NULL)
        info_value->SetReal(L"stop", atof(rows[16]));

      if (rows[17] != NULL)
        info_value->SetReal(L"deferred", atof(rows[17]));

      if (rows[18] != NULL)
        info_value->SetInteger(L"result", atol(rows[18]));

      list->Append((base_logic::Value *) (info_value));
    }
  }
  dict->Set(L"resultvalue", (base_logic::Value *) (list));
}

}  // namespace history_logic

