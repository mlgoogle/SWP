//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月8日 Author: kerry

#ifndef SWP_QUOTATION_PROTO_BUF_H_
#define SWP_QUOTATION_PROTO_BUF_H_

#include "basic/basictypes.h"
#include "logic/base_values.h"
#include <list>
#include <string>

namespace quotations_logic {

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

class Login {
 public:
  Login()
      : aid_(NULL),
        password_(NULL),
        value_(NULL) {
  }

  ~Login() {
    if (aid_) {
      delete aid_;
      aid_ = NULL;
    }
    if (password_) {
      delete password_;
      password_ = NULL;
    }
  }

  void set_aid(const int64 aid) {
    aid_ = new base_logic::FundamentalValue(aid);
  }

  void set_passowrd(const std::string& password) {
    password_ = new base_logic::StringValue(password);
  }

  base_logic::DictionaryValue* get() {
    value_ = new base_logic::DictionaryValue();
    if (aid_ != NULL)
      value_->Set(L"aid", aid_);
    if (password_ != NULL)
      value_->Set(L"password", password_);
    return value_;
  }

 public:
  base_logic::FundamentalValue* aid_;
  base_logic::StringValue* password_;
  base_logic::DictionaryValue* value_;

};

}

namespace net_request {

class RealTimeUnit {
 public:
  RealTimeUnit()
   :exchange_name_(NULL)
   ,platform_name_(NULL)
   ,good_type_(NULL){

  }

  ~RealTimeUnit() {
    if (exchange_name_) {delete exchange_name_; exchange_name_ = NULL;}
    if (platform_name_) {delete platform_name_; platform_name_ = NULL;}
    if (good_type_) {delete good_type_; good_type_ = NULL;}
  }

  void set_htt_packet(base_logic::DictionaryValue* value);

  void set_exchange_name(const std::string& exchange_name){
    exchange_name_ = new base_logic::StringValue(exchange_name);
  }

  void set_platform_name(const std::string& platform_name) {
    platform_name_ = new base_logic::StringValue(platform_name);
  }

  void set_good_type(const std::string& good_type) {
    good_type_ = new base_logic::StringValue(good_type);
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

  const std::string good_type() const {
    std::string good_type;
    good_type_->GetAsString(&good_type);
    return good_type;
  }

 public:
  base_logic::StringValue* exchange_name_;
  base_logic::StringValue* platform_name_;
  base_logic::StringValue* good_type_;
};


class RealTime {
 public:
  RealTime()
   :id_(NULL)
   ,token_(NULL)
   ,goods_infos_(NULL){}

  ~RealTime(){
    if (id_) {delete id_; id_ = NULL;}
    if (token_){delete token_; token_ = NULL;}
    if (goods_infos_){delete goods_infos_; goods_infos_ = NULL;}
  }

  void set_htt_packet(base_logic::DictionaryValue* value);

  void set_id(const int64 id) {
    id_ = new base_logic::FundamentalValue(id);
  }
  void set_token(const std::string& token) {
    token_ = new base_logic::StringValue(token);
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


 public:
  base_logic::FundamentalValue* id_;
  base_logic::StringValue* token_;
  base_logic::ListValue* goods_infos_;
};


class TimeLine {
 public:
  TimeLine()
   :id_(NULL)
   ,token_(NULL)
   ,exchange_name_(NULL)
   ,platform_name_(NULL)
   ,good_type_(NULL){}

  ~TimeLine(){
    if (id_) {delete id_; id_ = NULL;}
    if (token_) {delete token_; token_ = NULL;}
    if (exchange_name_) {delete exchange_name_; exchange_name_ = NULL;}
    if (platform_name_) {delete platform_name_; platform_name_ = NULL;}
    if (good_type_) {delete good_type_; good_type_ = NULL;}
  }

  void set_htt_packet(base_logic::DictionaryValue* value);

  void set_id(const int64 id) {
    id_ = new base_logic::FundamentalValue(id);
  }

  void set_token(const std::string& token) {
    token_ = new base_logic::StringValue(token);
  }

  void set_exchange_name(const std::string& exchange_name) {
    exchange_name_ = new base_logic::StringValue(exchange_name);
  }

  void set_platform_name(const std::string& platform_name) {
    platform_name_ = new base_logic::StringValue(platform_name);
  }

  void set_good_type(const std::string& good_type) {
    good_type_ = new base_logic::StringValue(good_type);
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

  const std::string good_type() const {
    std::string good_type;
    good_type_->GetAsString(&good_type);
    return good_type;
  }

 public:
  base_logic::FundamentalValue* id_;
  base_logic::StringValue* token_;
  base_logic::StringValue*  exchange_name_;
  base_logic::StringValue*  platform_name_;
  base_logic::StringValue*  good_type_;
};

}

namespace net_reply {

class RealTimeUnit{
 public:
  RealTimeUnit()
      : change_(NULL),
        pchg_(NULL),
        opening_today_price_(NULL),
        closed_yesterday_price_(NULL),
        current_price_(NULL),
        current_unix_time_(NULL),
        high_price_(NULL),
        low_price_(NULL),
        exchange_name_(NULL),
        platform_name_(NULL),
        symbol_(NULL),
        value_(NULL) {
  }

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

  void set_exchange_name(const std::string& exchange_name) {
    exchange_name_ = new base_logic::StringValue(exchange_name);
  }

  void set_platform_name(const std::string& platform_name) {
    platform_name_ = new base_logic::StringValue(platform_name);
  }

  void set_symbol(const std::string& symbol) {
    symbol_ = new base_logic::StringValue(symbol);
  }

  ~RealTimeUnit() {
    if (value_) {
      delete value_;
      value_ = NULL;
    }
  }

  base_logic::DictionaryValue* get() {
    value_ = new base_logic::DictionaryValue();
    if (change_ != NULL)
      value_->Set(L"change", change_);
    if (pchg_ != NULL)
      value_->Set(L"pchg", pchg_);
    if (opening_today_price_ != NULL)
      value_->Set(L"openingTodayPrice", opening_today_price_);
    if (closed_yesterday_price_ != NULL)
      value_->Set(L"closedYesterdayPrice", closed_yesterday_price_);
    if (current_price_ != NULL)
      value_->Set(L"currentPrice", current_price_);
    if (current_unix_time_ != NULL)
      value_->Set(L"priceTime", current_unix_time_);
    if (high_price_ != NULL)
      value_->Set(L"highPrice", high_price_);
    if (low_price_ != NULL)
      value_->Set(L"lowPrice", low_price_);
    if (exchange_name_ != NULL)
      value_->Set(L"exchangeName", exchange_name_);
    if (platform_name_ != NULL)
      value_->Set(L"platformName", platform_name_);
    if (symbol_ != NULL)
      value_->Set(L"goodType", symbol_);
    return value_;
  }
 private:
  base_logic::FundamentalValue* change_;
  base_logic::FundamentalValue* pchg_;
  base_logic::FundamentalValue* opening_today_price_;
  base_logic::FundamentalValue* closed_yesterday_price_;
  base_logic::FundamentalValue* current_price_;
  base_logic::FundamentalValue* current_unix_time_;
  base_logic::FundamentalValue* high_price_;
  base_logic::FundamentalValue* low_price_;
  base_logic::StringValue* exchange_name_;
  base_logic::StringValue* platform_name_;
  base_logic::StringValue* symbol_;
  base_logic::DictionaryValue* value_;
};


class RealTime {
 public:
  RealTime()
   :price_info_(NULL)
   ,value_(NULL){
    price_info_ = new base_logic::ListValue;
  }

  ~RealTime(){
    if (value_) {delete value_; value_ = NULL;}
  }

  void set_unit(base_logic::DictionaryValue* value){
    price_info_->Append((base_logic::Value*)(value));
  }


  base_logic::DictionaryValue* get() {
     value_ = new base_logic::DictionaryValue();
     if (!price_info_->empty()){
       value_->Set(L"priceinfo", price_info_);
     }else{
       delete price_info_;
       price_info_ = NULL;
     }
     return value_;
   }

  void Reset(){
    if (value_) {delete value_; value_ = NULL;}
    //if (price_info_) {delete price_info_; price_info_ = NULL;}
    price_info_ = new base_logic::ListValue;
  }
  const int32 Size(){
    return price_info_->GetSize();
  }

 private:
  base_logic::ListValue*  price_info_;
  base_logic::DictionaryValue* value_;
};

typedef RealTime TimeLine;


}



}
#endif
