//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#include "logic/swp_infos.h"
#include "basic/template.h"
#include "logic/logic_comm.h"

namespace swp_logic {

TradesPosition::TradesPosition() {
  data_ = new Data();
}

TradesPosition::TradesPosition(const TradesPosition& trades_positions)
: data_(trades_positions.data_) {
  if (data_ != NULL) {
    data_->AddRef();
  }
}

TradesPosition& TradesPosition::operator =(const TradesPosition& trades_positions) {
  if (trades_positions.data_ != NULL) {
    trades_positions.data_->AddRef();
  }

  if (data_ != NULL) {
    data_->Release();
  }

  data_ = trades_positions.data_;
  return (*this);
}

void TradesPosition::ValueSerialization(base_logic::DictionaryValue* dict) {
  dict->GetBigInteger(L"tid", &data_->position_id_);
  dict->GetBigInteger(L"uid", &data_->uid_);
  dict->GetInteger(L"code_id", &data_->code_id_);
  dict->GetInteger(L"buy_sell", &data_->buy_sell_);
  dict->GetString(L"symbol", &data_->symbol_);
  dict->GetString(L"name", &data_->name_);
  dict->GetInteger(L"close_type", &data_->close_type_);
  dict->GetBigInteger(L"amount", &data_->amount_);
  dict->GetBigInteger(L"open_position_time", &data_->open_position_time_);
  dict->GetBigInteger(L"close_position_time", &data_->close_position_time_);
  dict->GetReal(L"gross_profit", &data_->gross_profit_);
  dict->GetReal(L"open_price", &data_->open_price_);
  dict->GetReal(L"open_cost", &data_->open_cost_);
  dict->GetReal(L"open_charge", &data_->open_charge_);
  dict->GetReal(L"close_price", &data_->close_price_);
  dict->GetReal(L"pos_limit", &data_->limit_);
  dict->GetReal(L"stop", &data_->stop_);
  dict->GetReal(L"deferred", &data_->deferred_);
  int32 int_result = 0;
  dict->GetInteger(L"result", &int_result);
  if (int_result == 1)
    data_->result_ = true;
  else
    data_->result_ = false;
}


Quotations::Quotations() {
  data_ = new Data();
}

Quotations::Quotations(const Quotations& quotations)
    : data_(quotations.data_) {
  if (data_ != NULL) {
    data_->AddRef();
  }
}

Quotations& Quotations::operator =(const Quotations& quotations) {
  if (quotations.data_ != NULL) {
    quotations.data_->AddRef();
  }

  if (data_ != NULL) {
    data_->Release();
  }

  data_ = quotations.data_;
  return (*this);
}


void Quotations::ValueDeserialize(std::string& str) {
  int32 error_code;
  std::string error_str;
  base_logic::ValueSerializer* engine = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON);
  if (engine == NULL) {
    LOG_ERROR("engine create null");
  }
  base_logic::DictionaryValue* dict =  (base_logic::DictionaryValue*)engine->Deserialize(&str,&error_code,&error_str);
  dict->GetReal(L"current_price", &data_->current_price_);
  dict->GetReal(L"high_price", &data_->high_price_);
  dict->GetReal(L"low_price", &data_->low_price_);
  dict->GetReal(L"opening_today_price", &data_->opening_today_price_);
  dict->GetReal(L"closed_yesterday_price", &data_->closed_yesterday_price_);
  dict->GetReal(L"change", &data_->change_);
  dict->GetReal(L"pchg", &data_->pchg_);
  dict->GetBigInteger(L"current_unix_time", &data_->current_unix_time_);
  dict->GetString(L"platform_name",&data_->platform_name_);
  dict->GetString(L"symbol", &data_->symbol_);
  dict->GetString(L"exchange_name", &data_->exchange_name_);
}

std::string Quotations::ValueSerialize() {
  std::string json_content;
  base_logic::DictionaryValue dict;
  if (!data_)
    return "";
  dict.SetReal(L"current_price", data_->current_price_);
  dict.SetReal(L"high_price", data_->high_price_);
  dict.SetReal(L"low_price", data_->low_price_);
  dict.SetReal(L"opening_today_price", data_->opening_today_price_);
  dict.SetReal(L"closed_yesterday_price", data_->closed_yesterday_price_);
  dict.SetReal(L"change", data_->change_);
  dict.SetReal(L"pchg", data_->pchg_);
  dict.SetBigInteger(L"current_unix_time", data_->current_unix_time_);
  if (!data_->platform_name_.empty())
    dict.SetString(L"platform_name", data_->platform_name_);
  if (!data_->symbol_.empty())
    dict.SetString(L"symbol", data_->symbol_);
  if (!data_->exchange_name_.empty())
    dict.SetString(L"exchange_name", data_->exchange_name_);

  base_logic::ValueSerializer* engine = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON);
  if (engine == NULL) {
    LOG_ERROR("engine create null");
  }
  bool r = engine->Serialize(dict, &json_content);
  return json_content;
}

}  // namespace quotations_logic
