//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#ifndef SWP_PUB_LOGIC_SWP_INFOS_H_
#define SWP_PUB_LOGIC_SWP_INFOS_H_

#include <string>
#include <map>
#include <list>

#include "basic/basictypes.h"
#include "logic/base_values.h"
#include "basic/radom_in.h"

enum {
  STOCK_TYPE = 1,
  GOODS_TYPE = 2,
  FUTURES_TYPE = 3,
  FORXE_TYPE = 4,
};

enum BSTYPE {
  BUY_TYPE = 1,
  SELL_TYPE = 2
};

enum TIMETYPE {
  ONE_MINUTE = 60,
  FIVE_MINUTE = 300,
  HALF_HOUR = 1800,
  ONE_HOUR = 3600
};

namespace swp_logic {



class TradesPosition {
 public:
  TradesPosition();
  TradesPosition(const TradesPosition& trades_positions);

  TradesPosition& operator =(const TradesPosition& trades_positions);

  ~TradesPosition() {
    if (data_ != NULL) {
      data_->Release();
    }
  }

  static bool close_after(const TradesPosition& t_trades_position, const TradesPosition& r_trades_position){
    return Data::close_after(t_trades_position.data_, r_trades_position.data_);
  }
  void ValueSerialization(base_logic::DictionaryValue* dict);

  bool check_buy_sell(double close_price) {
    int32 buy_sell = 0;
    data_->close_price_ = close_price;
    double difference = close_price - data_->open_price_;
    if (difference > 0)
      buy_sell = BUY_TYPE;
    else if (difference < 0)
      buy_sell = SELL_TYPE;
    if (difference == 0)
      data_->result_ = false;
    else
      data_->result_ = (buy_sell == data_->buy_sell_) ? true : false;
    return data_->result_;
  }


  void c_gross_profit() {
    if (data_->close_type_)
      data_->gross_profit_ = data_->open_cost_;
  }

  void create_position_id() {
    data_->position_id_ = base::SysRadom::GetInstance()->GetRandomID();
  }

  void set_uid(const int64 uid) {
    data_->uid_ = uid;
  }

  void set_position_id(const int64 position_id) {
    data_->position_id_ = position_id;
  }

  void set_code_id(const int32 code_id) {
    data_->code_id_ = code_id;
  }

  void set_buy_sell(const int32 buy_sell) {
    data_->buy_sell_ = buy_sell;
  }

  void set_close_type(const int32 close_type) {
    data_->close_type_ = close_type;
  }

  void set_is_deferred(const bool is_deferred) {
    data_->deferred_ = is_deferred;
  }

  void set_amount(const int64 amount) {
    data_->amount_ = amount;
  }

  void set_open_position_time(const int64 open_position_time) {
    data_->open_position_time_ = open_position_time;
  }

  void set_close_position_time(const int64 close_position_time) {
    data_->close_position_time_ = close_position_time;
  }

  void set_open_price(const double open_price) {
    data_->open_price_ = open_price;
  }

  void set_open_cost(const double open_cost) {
    data_->open_cost_ = open_cost;
  }

  void set_open_all_cost(const double open_all_cost) {
    data_->open_all_cost_ = open_all_cost;
  }

  void set_open_charge(const double open_charge) {
    data_->open_charge_ = open_charge;
  }

  void set_close_price(const double close_price) {
    data_->close_price_ = close_price;
  }

  void set_limit(const double limit) {
    data_->limit_ = limit;
  }

  void set_stop(const double stop) {
    data_->stop_ = stop;
  }

  void set_deferred(const double deferred) {
    data_->deferred_ = deferred;
  }

  void set_code(const std::string& code) {
    data_->code_ = code;
  }

  void set_symbol(const std::string& symbol) {
    data_->symbol_ = symbol;
  }

  void set_name(const std::string& name) {
    data_->name_ = name;
  }

  void set_result(const bool result) {
    data_->result_ = result;
  }

  void set_gross_profit(const double gross_profit) {
    data_->gross_profit_ = gross_profit;
  }

  void set_goods_key(const std::string& goods_key) {
    data_->goods_key_ = goods_key;
  }
  const int64 uid() const {
    return data_->uid_;
  }

  const int64 position_id() const {
    return data_->position_id_;
  }

  const int32 code_id() const {
    return data_->code_id_;
  }

  const int32 buy_sell() const {
    return data_->buy_sell_;
  }

  const int32 close_type() const {
    return data_->close_type_;
  }

  const bool is_deferred() const {
    return data_->is_deferred_;
  }

  const int64 amount() const {
    return data_->amount_;
  }

  const int64 open_position_time() const {
    return data_->open_position_time_;
  }

  const int64 close_position_time() const {
    return data_->close_position_time_;
  }

  const double open_price() const {
    return data_->open_price_;
  }

  const double open_cost() const {
    return data_->open_cost_;
  }

  const double open_all_cost() const {
    return data_->open_all_cost_;
  }

  const double open_charge() const {
    return data_->open_charge_;
  }

  const double close_price() const {
    return data_->close_price_;
  }

  const double limit() const {
    return data_->limit_;
  }

  const double stop() const {
    return data_->stop_;
  }

  const double gross_profit() const {
    return data_->gross_profit_;
  }

  const double deferred() const {
    return data_->deferred_;
  }

  const bool result() const {
    return data_->result_;
  }

  const std::string& code() const {
    return data_->code_;
  }

  const std::string& symbol() const {
    return data_->symbol_;
  }

  const std::string& name() const {
    return data_->name_;
  }

  const std::string& goods_key() const {
    return data_->goods_key_;
  }

 private:
  class Data {
   public:
    Data()
        : refcount_(1),
          uid_(0),
          position_id_(0),
          code_id_(0),
          buy_sell_(0),
          close_type_(0),
          is_deferred_(false),
          result_(false),
          amount_(0),
          open_position_time_(0),
          close_position_time_(0),
          gross_profit_(0.0),
          open_price_(0.0),
          open_cost_(0.0),
          open_all_cost_(0.0),
          open_charge_(0.0),
          close_price_(0.0),
          limit_(0.0),
          stop_(0.0),
          deferred_(0.0) {
    }

    static bool close_after(const Data* t_data,
                      const Data* r_data) {
      return t_data->close_position_time_ > r_data->close_position_time_;
    }
   public:
    int64 uid_;
    int64 position_id_;
    int32 code_id_;  //属于哪个商品
    int32 buy_sell_;  // 1,买 2,卖
    int32 close_type_;
    bool is_deferred_;
    bool result_;
    int64 amount_;
    int64 open_position_time_;
    int64 close_position_time_;
    double gross_profit_;
    double open_price_;
    double open_cost_;
    double open_all_cost_;
    double open_charge_;
    double close_price_;
    double limit_;
    double stop_;
    double deferred_;
    std::string code_;
    std::string symbol_;
    std::string name_;
    std::string goods_key_;

    void AddRef() {
      __sync_fetch_and_add(&refcount_, 1);
    }
    void Release() {
      __sync_fetch_and_sub(&refcount_, 1);
      if (!refcount_)
        delete this;
    }
   private:
    int refcount_;
  };
  Data* data_;
};


class Quotations {
 public:
  Quotations();

  Quotations(const Quotations& quotations);

  Quotations& operator =(const Quotations& quotations);

  ~Quotations() {
    if (data_ != NULL) {
      data_->Release();
    }
  }


  static bool before(const Quotations& t_info, const Quotations& r_info){
    return Data::before(t_info.data_, r_info.data_);
  }

  static bool after(const Quotations& t_info, const Quotations& r_info){
    return Data::after(t_info.data_, r_info.data_);
  }

  static bool cmp(const Quotations& t_info, const Quotations& r_info){
    return Data::after(t_info.data_, r_info.data_);
  }

  void set_platform_name(const std::string& platform) {
    data_->platform_name_ = platform;
  }

  void set_symbol(const std::string& symbol) {
    data_->symbol_ = symbol;
  }

  void set_exchange_name(const std::string& exchange_name) {
    data_->exchange_name_ = exchange_name;
  }

  void set_current_price(const double current_price) {
    data_->current_price_ = current_price;
  }

  void set_high_price(const double high_price) {
    data_->high_price_ = high_price;
  }

  void set_low_price(const double low_price) {
    data_->low_price_ = low_price;
  }

  void set_opening_today_price(const double opening_today_price) {
    data_->opening_today_price_ = opening_today_price;
  }

  void set_closed_yesterday_price(const double closed_yesterday_price) {
    data_->closed_yesterday_price_ = closed_yesterday_price;
  }

  void set_change(const double change) {
    data_->change_ = change;
  }

  void set_pchg(const double pchg) {
    data_->pchg_ = pchg;
  }

  void set_type(const int32 type) {
    data_->type_ = type;
  }

  void set_current_unix_time(const int64 current_unix_time) {
    data_->current_unix_time_ = current_unix_time;
  }

  const std::string& platform() const {
    return data_->platform_name_;
  }

  const std::string& symbol() const {
    return data_->symbol_;
  }

  const std::string& exchange_name() const {
    return data_->exchange_name_;
  }
  const double current_price() const {
    return data_->current_price_;
  }

  const double high_price() const {
    return data_->high_price_;
  }

  const double low_price() const {
    return data_->low_price_;
  }

  const double opening_today_price() const {
    return data_->opening_today_price_;
  }

  const double closed_yesterday_price() const {
    return data_->closed_yesterday_price_;
  }

  const double change() const {
    return data_->change_;
  }

  const double pchg() const {
    return data_->pchg_;
  }

  const int64 current_unix_time() const {
    return data_->current_unix_time_;
  }

  const int32 type() const {
    return data_->type_;
  }

  std::string ValueSerialize();
  void ValueDeserialize(std::string& str);

 private:
  class Data {
   public:
    Data()
        : refcount_(1),
          type_(0),
          current_price_(0.0),
          high_price_(0.0),
          low_price_(0.0),
          opening_today_price_(0.0),
          closed_yesterday_price_(0.0),
          change_(0.0),
          pchg_(0.0),
          current_unix_time_(0) {
    }

    ~Data() {
    }

   public:
    std::string platform_name_;
    std::string symbol_;
    std::string exchange_name_;
    int32  type_;//1,股票 2，现货 3，期货
    double current_price_;
    double high_price_;
    double low_price_;
    double opening_today_price_;
    double closed_yesterday_price_;
    double change_;
    double pchg_;
    int64 current_unix_time_;

    static bool before(const Data* t_info, const Data* r_info){
      return t_info->current_unix_time_ <= r_info->current_unix_time_;
    }

    static bool after(const Data* t_info, const Data* r_info){
      return t_info->current_unix_time_ > r_info->current_unix_time_;
    }

    void AddRef() {
      __sync_fetch_and_add(&refcount_, 1);
    }
    void Release() {
      __sync_fetch_and_sub(&refcount_, 1);
      if (!refcount_)
        delete this;
    }

   private:
    int refcount_;
  };
  Data* data_;
};

}  // namespace quotations_logic

#endif /* QUOTATIONS_PUB_LOGIC_QUOTATIONS_INFOS_H_ */
