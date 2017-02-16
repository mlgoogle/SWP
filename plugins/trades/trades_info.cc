//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#include "trades/trades_info.h"
#include "basic/template.h"
#include "logic/logic_comm.h"

namespace trades_logic {


TimeTask::TimeTask() {
  data_ = new Data();
}

TimeTask::TimeTask(const TimeTask& time_task)
: data_(time_task.data_) {
  if (data_ != NULL) {
    data_->AddRef();
  }
}

TimeTask& TimeTask::operator =(const TimeTask& time_task) {
  if (time_task.data_ != NULL) {
    time_task.data_->AddRef();
  }

  if (data_ != NULL) {
    data_->Release();
  }

  data_ = time_task.data_;
  return (*this);
}


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


GoodsInfo::GoodsInfo() {
  data_ = new Data();
}

GoodsInfo::GoodsInfo(const GoodsInfo& goods_info)
    : data_(goods_info.data_) {
  if (data_ != NULL) {
    data_->AddRef();
  }
}

GoodsInfo& GoodsInfo::operator =(const GoodsInfo& goods_info) {
  if (goods_info.data_ != NULL) {
    goods_info.data_->AddRef();
  }

  if (data_ != NULL) {
    data_->Release();
  }

  data_ = goods_info.data_;
  return (*this);
}

void GoodsInfo::ValueSerialization(base_logic::DictionaryValue* dict) {
  dict->GetInteger(L"id", &data_->id_);
  dict->GetInteger(L"platform_id", &data_->plaform_id_);
  dict->GetString(L"name", &data_->name_);
  dict->GetString(L"code", &data_->code_);
  dict->GetString(L"symbol", &data_->symbol_);
  dict->GetString(L"unit", &data_->unit_);
  dict->GetReal(L"amount", &data_->amount_);
  dict->GetReal(L"profit", &data_->profit_);
  dict->GetReal(L"deposit", &data_->deposit_);
  dict->GetReal(L"close", &data_->close_);
  dict->GetReal(L"open", &data_->open_);
  dict->GetReal(L"deferred", &data_->deferred_);
  dict->GetReal(L"max", &data_->max_);
  dict->GetReal(L"min", &data_->min_);
  dict->GetString(L"exchange_name", &data_->exchange_name_);
  dict->GetString(L"platform_name", &data_->platform_name_);
  int8 status = 1;
  if (dict->GetCharInteger(L"status", &status))
    data_->status_ = status;
  int8 sort = 1;
  if (dict->GetCharInteger(L"sort", &sort))
    data_->sort_ = sort;

}

}  // namespace trades_logic
