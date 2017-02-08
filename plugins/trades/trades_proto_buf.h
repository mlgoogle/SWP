//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月8日 Author: kerry

#ifndef SWP_TRADES_PROTO_BUF_H_
#define SWP_TRADES_PROTO_BUF_H_

#include "basic/basictypes.h"
#include "logic/base_values.h"
#include <list>
#include <string>

namespace trades_logic {

namespace net_other {
class RealTime {
 public:
  RealTime()
      : change_(NULL),
        pchg_(NULL),
        opening_today_price_(NULL),
        closed_yesterday_price_(NULL),
        current_price_(NULL),
        current_unix_time_(NULL),
        high_price_(NULL),
        low_price_(NULL),
        type_(NULL),
        exchange_name_(NULL),
        platform_name_(NULL),
        symbol_(NULL) {
  }

  ~RealTime() {
    if (change_) {
      delete change_;
      change_ = NULL;
    }
    if (pchg_) {
      delete pchg_;
      pchg_ = NULL;
    }
    if (opening_today_price_) {
      delete opening_today_price_;
      opening_today_price_ = NULL;
    }
    if (closed_yesterday_price_) {
      delete closed_yesterday_price_;
      closed_yesterday_price_ = NULL;
    }
    if (current_price_) {
      delete current_price_;
      current_price_ = NULL;
    }
    if (current_unix_time_) {
      delete current_unix_time_;
      current_unix_time_ = NULL;
    }
    if (high_price_) {
      delete high_price_;
      high_price_ = NULL;
    }
    if (low_price_) {
      delete low_price_;
      low_price_ = NULL;
    }
    if (type_) {
      delete type_;
      type_ = NULL;
    }
    if (exchange_name_) {
      delete exchange_name_;
      exchange_name_ = NULL;
    }
    if (platform_name_) {
      delete platform_name_;
      platform_name_ = NULL;
    }
    if (symbol_) {
      delete symbol_;
      symbol_ = NULL;
    }
  }

  void set_http_packet(base_logic::DictionaryValue* value);

  void set_change(const double change) {
    change_ = new base_logic::FundamentalValue(change);
  }

  void set_pchg(const double pchg) {
    pchg_ = new base_logic::FundamentalValue(pchg);
  }

  void set_opening_today_price(const double opening_today_price) {
    opening_today_price_ = new base_logic::FundamentalValue(
        opening_today_price);
  }

  void set_closed_yesterday_price(const double closed_yesterday_price) {
    closed_yesterday_price_ = new base_logic::FundamentalValue(
        closed_yesterday_price);
  }

  void set_current_price(const double current_price) {
    current_price_ = new base_logic::FundamentalValue(current_price);
  }

  void set_current_unix_time(const int64 current_unix_time) {
    current_unix_time_ = new base_logic::FundamentalValue(current_unix_time);
  }

  void set_high_price(const double high_price) {
    high_price_ = new base_logic::FundamentalValue(high_price);
  }

  void set_low_price(const double low_price) {
    low_price_ = new base_logic::FundamentalValue(low_price);
  }

  void set_type(const int32 type) {
    type_ = new base_logic::FundamentalValue(type);
  }

  void set_exchange_name(const std::string& exchange_name) {
    exchange_name_ = new base_logic::StringValue(exchange_name);
  }

  void set_platform_name(const std::string& platform_name) {
    platform_name_ = new base_logic::StringValue(platform_name);
  }

  void set_symbol(const std::string& symbol) {
    symbol_ = new base_logic::StringValue(symbol);
  }

  const double change() const {
    double change = 0;
    change_->GetAsReal(&change);
    return change;
  }

  const double pchg() const {
    double pchg = 0;
    pchg_->GetAsReal(&pchg);
    return pchg;
  }

  const double opening_today_price() const {
    double opening_today_price = 0;
    opening_today_price_->GetAsReal(&opening_today_price);
    return opening_today_price;
  }

  const double closed_yesterday_price() const {
    double closed_yesterday_price = 0;
    closed_yesterday_price_->GetAsReal(&closed_yesterday_price);
    return closed_yesterday_price;
  }

  const double current_price() const {
    double current_price = 0;
    current_price_->GetAsReal(&current_price);
    return current_price;
  }

  const int64 current_unix_time() const {
    int64 current_unix_time = 0;
    current_unix_time_->GetAsBigInteger(&current_unix_time);
    return current_unix_time;
  }

  const double high_price() const {
    double high_price = 0;
    high_price_->GetAsReal(&high_price);
    return high_price;
  }

  const double low_price() const {
    double low_price = 0;
    low_price_->GetAsReal(&low_price);
    return low_price;
  }

  const int32 type() const {
    int32 type = 0;
    type_->GetAsInteger(&type);
    return type;
  }

  const std::string exchange_name() const {
    std::string exchange_name;
    exchange_name_->GetAsString(&exchange_name);
    return exchange_name;
  }

  const std::string platform_name() const {
    std::string platform_name;
    platform_name_->GetAsString(&platform_name);
    return platform_name;
  }

  const std::string symbol() const {
    std::string symbol;
    symbol_->GetAsString(&symbol);
    return symbol;
  }

 public:
  base_logic::FundamentalValue* change_;
  base_logic::FundamentalValue* pchg_;
  base_logic::FundamentalValue* opening_today_price_;
  base_logic::FundamentalValue* closed_yesterday_price_;
  base_logic::FundamentalValue* current_price_;
  base_logic::FundamentalValue* current_unix_time_;
  base_logic::FundamentalValue* high_price_;
  base_logic::FundamentalValue* low_price_;
  base_logic::FundamentalValue* type_;
  base_logic::StringValue* exchange_name_;
  base_logic::StringValue* platform_name_;
  base_logic::StringValue* symbol_;
};
}



namespace net_request {

class OpenPosition {
 public:
  OpenPosition()
      : id_(NULL),
        token_(NULL),
        code_id_(NULL),
        buy_sell_(NULL),
        amount_(NULL),
        price_(NULL),
        limit_(NULL),
        stop_(NULL),
        deferred_(NULL) {
  }

  ~OpenPosition() {
    if (id_) {
      delete id_;
      id_ = NULL;
    }
    if (token_) {
      delete token_;
      token_ = NULL;
    }
    if (code_id_) {
      delete code_id_;
      code_id_ = NULL;
    }
    if (buy_sell_) {
      delete buy_sell_;
      buy_sell_ = NULL;
    }
    if (amount_) {
      delete amount_;
      amount_ = NULL;
    }
    if (price_) {
      delete price_;
      price_ = NULL;
    }
    if (limit_) {
      delete limit_;
      limit_ = NULL;
    }
    if (stop_) {
      delete stop_;
      stop_ = NULL;
    }
    if (deferred_) {
      delete deferred_;
      deferred_ = NULL;
    }
  }

  void set_http_packet(base_logic::DictionaryValue* value);

  void set_id(const int64 id) {
    id_ = new base_logic::FundamentalValue(id);
  }

  void set_token(const std::string& token) {
    token_ = new base_logic::StringValue(token);
  }

  void set_code_id(const int32 code_id) {
    code_id_ = new base_logic::FundamentalValue(code_id);
  }

  void set_buy_sell(const int32 buy_sell) {
    buy_sell_ = new base_logic::FundamentalValue(buy_sell);
  }

  void set_amount(const int64 amount) {
    amount_ = new base_logic::FundamentalValue(amount);
  }

  void set_price(const double price) {
    price_ = new base_logic::FundamentalValue(price);
  }

  void set_limit(const double limit) {
    limit_ = new base_logic::FundamentalValue(limit);
  }

  void set_stop(const double stop) {
    stop_ = new base_logic::FundamentalValue(stop);
  }

  void set_deferred(const int32 deferred) {
    deferred_ = new base_logic::FundamentalValue(deferred);
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

  const int32 code_id() const {
    int32 code_id;
    code_id_->GetAsInteger(&code_id);
    return code_id;
  }

  const int32 buy_sell() const {
    int32 buy_sell;
    buy_sell_->GetAsInteger(&buy_sell);
    return buy_sell;
  }

  const int64 amount() const {
    int64 amount = 0;
    amount_->GetAsBigInteger(&amount);
    return amount;
  }

  const double price() const {
    double price = 0.0;
    price_->GetAsReal(&price);
    return price;
  }

  const double limit() const {
    double limit = 0.0;
    limit_->GetAsReal(&limit);
    return limit;
  }

  const double stop() const {
    double stop = 0.0;
    stop_->GetAsReal(&stop);
    return stop;
  }

  const int32 deferred() const {
    int32 deferred = 0;
    deferred_->GetAsInteger(&deferred);
    return deferred;
  }

 public:
  base_logic::FundamentalValue* id_;
  base_logic::StringValue* token_;
  base_logic::FundamentalValue* code_id_;
  base_logic::FundamentalValue* buy_sell_;
  base_logic::FundamentalValue* amount_;
  base_logic::FundamentalValue* price_;
  base_logic::FundamentalValue* limit_;
  base_logic::FundamentalValue* stop_;
  base_logic::FundamentalValue* deferred_;
};
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
        id_(NULL),
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

  void set_id(const int32 id){
    id_ = new base_logic::FundamentalValue(id);
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
    if (id_ != NULL)
      value_->Set(L"id", id_);
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
  base_logic::FundamentalValue* id_;
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
      : goods_info_(NULL),
        value_(NULL) {
    goods_info_ = new base_logic::ListValue;
  }

  ~Goods() {
    if (value_) {
      delete value_;
      value_ = NULL;
    }
  }

  void set_unit(base_logic::DictionaryValue* value) {
    goods_info_->Append((base_logic::Value*) (value));
  }

  base_logic::DictionaryValue* get() {
    value_ = new base_logic::DictionaryValue();
    if (!goods_info_->empty()) {
      value_->Set(L"goodsinfo", goods_info_);
    } else {
      delete goods_info_;
      goods_info_ = NULL;
    }
    return value_;
  }

  const int32 Size() {
    return goods_info_->GetSize();
  }

  void Reset() {
    if (value_) {
      delete value_;
      value_ = NULL;
    }
    goods_info_ = new base_logic::ListValue;
  }

 private:
  base_logic::ListValue* goods_info_;
  base_logic::DictionaryValue* value_;
};

}

}
#endif
