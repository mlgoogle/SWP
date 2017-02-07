//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月8日 Author: kerry

#ifndef SWP_TRADES_PROTO_BUF_H_
#define SWP_TRADES_PROTO_BUF_H_

#include "basic/basictypes.h"
#include "logic/base_values.h"
#include <list>
#include <string>

namespace trades_logic {

namespace net_request {

class Goods {
 public:
  Goods()
      : id_(NULL),
        token_(NULL),
        pid_(NULL) {

  }

  ~Goods() {
    if (id_) {
      delete id_;
      id_ = NULL;
    }
    if (token_) {
      delete token_;
      token_ = NULL;
    }
    if (pid_) {
      delete pid_;
      pid_ = NULL;
    }
  }

  void set_http_packet(base_logic::DictionaryValue* value);

  void set_id(const int64 id) {
    id_ = new base_logic::FundamentalValue(id);
  }

  void set_token(const std::string& token) {
    token_ = new base_logic::StringValue(token);
  }

  void set_pid(const int32 pid) {
    pid_ = new base_logic::FundamentalValue(pid);
  }

  const int64 id() const {
    int64 id = 0;
    id_->GetAsBigInteger(&id);
    return id;
  }

  const std::string token() const {
    std::string token;
    token_->GetAsString(&token);
    return token;
  }

  const int32 pid() const {
    int32 pid = 0;
    pid_->GetAsInteger(&pid);
    return pid;
  }

 public:
  base_logic::FundamentalValue* id_;
  base_logic::StringValue* token_;
  base_logic::FundamentalValue* pid_;
};

}

namespace net_reply {

class GoodsUnit {
 public:
  GoodsUnit()
      : exchange_name_(NULL),
        platform_name_(NULL),
        code_(NULL),
        symbol_(NULL),
        unit_(NULL),
        amount_(NULL),
        profit_(NULL),
        deposit_(NULL),
        open_(NULL),
        close_(NULL),
        name_(NULL),
        deferred_(NULL),
        max_lot_(NULL),
        min_lot_(NULL),
        status_(NULL),
        sort_(NULL),
        value_(NULL) {
  }

  ~GoodsUnit() {
    if (value_) {
      delete value_;
      value_ = NULL;
    }
  }

  void set_exchange_name(const std::string& exchange_name) {
    exchange_name_ = new base_logic::StringValue(exchange_name);
  }

  void set_platform_name(const std::string& platform_name) {
    platform_name_ = new base_logic::StringValue(platform_name);
  }

  void set_code(const std::string& code) {
    code_ = new base_logic::StringValue(code);
  }

  void set_symbol(const std::string& symbol) {
    symbol_ = new base_logic::StringValue(symbol);
  }

  void set_unit(const std::string& unit) {
    unit_ = new base_logic::StringValue(unit);
  }

  void set_amount(const double amount) {
    amount_ = new base_logic::FundamentalValue(amount);
  }

  void set_profit(const double profit) {
    profit_ = new base_logic::FundamentalValue(profit);
  }

  void set_deposit(const double deposit) {
    deposit_ = new base_logic::FundamentalValue(deposit);
  }

  void set_open(const double open) {
    open_ = new base_logic::FundamentalValue(open);
  }

  void set_close(const double close) {
    close_ = new base_logic::FundamentalValue(close);
  }

  void set_deferred(const double deferred) {
    deferred_ = new base_logic::FundamentalValue(deferred);
  }

  void set_max_lot(const double max_lot) {
    max_lot_ = new base_logic::FundamentalValue(max_lot);
  }

  void set_min_lot(const double min_lot) {
    min_lot_ = new base_logic::FundamentalValue(min_lot);
  }

  void set_status(const int8 status) {
    status_ = new base_logic::FundamentalValue(status);
  }

  void set_sort(const int8 sort) {
    sort_ = new base_logic::FundamentalValue(sort);
  }

  void set_name(const std::string& name) {
    name_ = new base_logic::StringValue(name);
  }

  base_logic::DictionaryValue* get() {
    value_ = new base_logic::DictionaryValue();
    if (exchange_name_ != NULL)
      value_->Set(L"exchangeName", exchange_name_);
    if (platform_name_ != NULL)
      value_->Set(L"platformName", platform_name_);
    if (code_ != NULL)
      value_->Set(L"code", code_);
    if (symbol_ != NULL)
      value_->Set(L"symbol", symbol_);
    if (unit_ != NULL)
      value_->Set(L"unit", unit_);
    if (amount_ != NULL)
      value_->Set(L"amount", amount_);
    if (profit_ != NULL)
      value_->Set(L"profit", profit_);
    if (deposit_ != NULL)
      value_->Set(L"deposit", deposit_);
    if (open_ != NULL)
      value_->Set(L"open", open_);
    if (close_ != NULL)
      value_->Set(L"close", close_);
    if (deferred_ != NULL)
      value_->Set(L"deferred", deferred_);
    if (max_lot_ != NULL)
      value_->Set(L"maxLot", max_lot_);
    if (min_lot_ != NULL)
      value_->Set(L"minLot", min_lot_);
    if (status_ != NULL)
      value_->Set(L"status", status_);
    if (sort_ != NULL)
      value_->Set(L"sort", sort_);
    if (name_ != NULL)
      value_->Set(L"name", name_);

    return value_;
  }
 private:
  base_logic::StringValue* exchange_name_;
  base_logic::StringValue* platform_name_;
  base_logic::StringValue* code_;
  base_logic::StringValue* symbol_;
  base_logic::StringValue* unit_;
  base_logic::StringValue* name_;
  base_logic::FundamentalValue* amount_;
  base_logic::FundamentalValue* profit_;
  base_logic::FundamentalValue* deposit_;
  base_logic::FundamentalValue* open_;
  base_logic::FundamentalValue* close_;
  base_logic::FundamentalValue* deferred_;
  base_logic::FundamentalValue* max_lot_;
  base_logic::FundamentalValue* min_lot_;
  base_logic::FundamentalValue* status_;
  base_logic::FundamentalValue* sort_;
  base_logic::DictionaryValue* value_;
};


class Goods {
 public:
  Goods()
   :goods_info_(NULL)
   ,value_(NULL){
    goods_info_ = new base_logic::ListValue;
  }

  ~Goods(){
    if (value_) {delete value_; value_ = NULL;}
  }

  void set_unit(base_logic::DictionaryValue* value){
    goods_info_->Append((base_logic::Value*)(value));
  }


  base_logic::DictionaryValue* get() {
     value_ = new base_logic::DictionaryValue();
     if (!goods_info_->empty()){
       value_->Set(L"goodsinfo", goods_info_);
     }else{
       delete goods_info_;
       goods_info_ = NULL;
     }
     return value_;
   }

  const int32 Size(){
    return goods_info_->GetSize();
  }

  void Reset(){
    if (value_) {delete value_; value_ = NULL;}
    goods_info_ = new base_logic::ListValue;
  }

 private:
  base_logic::ListValue*  goods_info_;
  base_logic::DictionaryValue* value_;
};

}

}
#endif
