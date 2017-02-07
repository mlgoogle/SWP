//  Copyright (c) 2015-2015 The KID Authors. All rights reserved.
//  Created on: 2015年9月17日 Author: kerry
#include <mysql.h>
#include "logic/logic_unit.h"
#include "trades/trades_db.h"
#include "basic/basic_util.h"

namespace trades_logic {

TradesDB::TradesDB(config::FileConfig* config) {
  mysql_engine_ = base_logic::DataEngine::Create(MYSQL_TYPE);
  mysql_engine_->InitParam(config->mysql_db_list_);
}

TradesDB::~TradesDB() {
  if (mysql_engine_) {
    delete mysql_engine_;
    mysql_engine_ = NULL;
  }
}

bool TradesDB::OnFetchPlatformGoods(std::list<trades_logic::GoodsInfo>* list){
  bool r = false;
  base_logic::DictionaryValue* dict = new base_logic::DictionaryValue();

  std::string sql;
  sql = "call proc_FetchPlatformGoods()";
  base_logic::ListValue *listvalue;
  dict->SetString(L"sql", sql);
  r = mysql_engine_->ReadData(0, (base_logic::Value *) (dict),
                              CallFecthPlatformGoods);
  if (!r)
    return false;
  dict->GetList(L"resultvalue", &listvalue);
  while (listvalue->GetSize()) {
    trades_logic::GoodsInfo goods;
    base_logic::Value *result_value;
    listvalue->Remove(0, &result_value);
    base_logic::DictionaryValue *dict_result_value =
        (base_logic::DictionaryValue *) (result_value);
    goods.ValueSerialization(dict_result_value);
    list->push_back(goods);
    delete dict_result_value;
    dict_result_value = NULL;
  }

  if (dict) {
    delete dict;
    dict = NULL;
  }
  return true;
}

void TradesDB::CallFecthPlatformGoods(void* param, base_logic::Value* value) {
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
        info_value->SetInteger(L"id", atoi(rows[0]));

      if (rows[1] != NULL)
        info_value->SetInteger(L"platform_id", atoi(rows[1]));

      if (rows[2] != NULL)
        info_value->SetString(L"code", rows[2]);

      if (rows[3] != NULL)
        info_value->SetString(L"name", rows[3]);

      if (rows[4] != NULL)
        info_value->SetString(L"symbol", rows[4]);

      if (rows[5] != NULL)
        info_value->SetString(L"unit", rows[5]);

      if (rows[6] != NULL) {
        double temp = 0.0;
        bool r = base::BasicUtil::StringUtil::StringToDouble(
            std::string(rows[6]), &temp);
        info_value->SetReal(L"amount", temp);
      }

      if (rows[7] != NULL) {
        double temp = 0.0;
        bool r = base::BasicUtil::StringUtil::StringToDouble(
            std::string(rows[7]), &temp);
        info_value->SetReal(L"profit", temp);
      }

      if (rows[8] != NULL) {
        double temp = 0.0;
        bool r = base::BasicUtil::StringUtil::StringToDouble(
            std::string(rows[8]), &temp);
        info_value->SetReal(L"deposit", temp);
      }

      if (rows[9] != NULL) {
        double temp = 0.0;
        bool r = base::BasicUtil::StringUtil::StringToDouble(
            std::string(rows[9]), &temp);
        info_value->SetReal(L"open", temp);
      }

      if (rows[10] != NULL) {
        double temp = 0.0;
        bool r = base::BasicUtil::StringUtil::StringToDouble(
            std::string(rows[10]), &temp);
        info_value->SetReal(L"close", temp);
      }

      if (rows[11] != NULL) {
        double temp = 0.0;
        bool r = base::BasicUtil::StringUtil::StringToDouble(
            std::string(rows[11]), &temp);
        info_value->SetReal(L"deferred", temp);
      }

      if (rows[12] != NULL) {
        double temp = 0.0;
        bool r = base::BasicUtil::StringUtil::StringToDouble(
            std::string(rows[12]), &temp);
        info_value->SetReal(L"max", temp);
      }

      if (rows[13] != NULL) {
        double temp = 0.0;
        bool r = base::BasicUtil::StringUtil::StringToDouble(
            std::string(rows[13]), &temp);
        info_value->SetBigInteger(L"min", temp);
      }

      if (rows[14] != NULL)
        info_value->SetString(L"exchange_name", rows[14]);

      if (rows[15] != NULL)
        info_value->SetString(L"platform_name", rows[15]);

      if (rows[16] != NULL)
        info_value->SetCharInteger(L"status",
                                   logic::SomeUtils::StringToIntChar(rows[16]));

      if (rows[17] != NULL)
        info_value->SetCharInteger(L"sort",
                                   logic::SomeUtils::StringToIntChar(rows[16]));

      list->Append((base_logic::Value *) (info_value));
    }
  }
  dict->Set(L"resultvalue", (base_logic::Value *) (list));
}

}  // namespace trades_logic

