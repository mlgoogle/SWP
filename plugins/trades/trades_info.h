//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月3日 Author: kerry

#ifndef SWP_TRADES_INFOS_H_
#define SWP_TRADES_INFOS_H_

#include <string>
#include <map>
#include <list>

#include "basic/basictypes.h"
#include "logic/base_values.h"

namespace trades_logic {

class GoodsInfo {
 public:
  GoodsInfo();

  GoodsInfo(const GoodsInfo& goods_info);

  GoodsInfo& operator =(const GoodsInfo& goods_info);

  ~GoodsInfo() {
    if (data_ != NULL) {
      data_->Release();
    }
  }

  const int32 id() const {
    return data_->id_;
  }

  const int32 platform_id() const {
    return data_->plaform_id_;
  }

  const std::string& name() const {
    return data_->name_;
  }

  const std::string& code() const {
    return data_->code_;
  }

  const std::string& symbol() const {
    return data_->symbol_;
  }

  const std::string& unit() const {
    return data_->unit_;
  }

  const double amount() const {
    return data_->amount_;
  }

  const double profit() const {
    return data_->profit_;
  }

  const double deposit() const {
    return data_->deferred_;
  }

  const double close() const {
    return data_->close_;
  }

  const double open() const {
    return data_->open_;
  }

  const double deferred() const {
    return data_->deferred_;
  }

  const double max() const {
    return data_->max_;
  }

  const double min() const {
    return data_->min_;
  }

  const std::string& exchange_name() const {
    return data_->exchange_name_;
  }

  const std::string& platform_name() const {
    return data_->platform_name_;
  }

  const int8 status() const {
    return data_->status_;
  }

  const int8 sort() const {
    return data_->sort_;
  }

  void set_id(const int32 id) {
    data_->id_ = id;
  }

  void set_platform_id(const int32 platform_id) {
    data_->plaform_id_ = platform_id;
  }

  void set_name(const std::string& name) {
    data_->name_ = name;
  }

  void set_code(const std::string& code) {
    data_->code_ = code;
  }

  void set_symbol(const std::string& symbol) {
    data_->symbol_ = symbol;
  }

  void set_unit(const std::string& unit) {
    data_->unit_ = unit;
  }

  void set_amount(const double amount) {
    data_->amount_ = amount;
  }

  void set_profit(const double profit) {
    data_->profit_ = profit;
  }

  void set_deposit(const double deposit) {
    data_->deferred_ = deposit;
  }

  void set_close(const double close) {
    data_->close_ = close;
  }

  void set_open(const double open) {
    data_->open_ = open;
  }

  void set_deferred(const double deferred) {
    data_->deferred_ = deferred;
  }

  void set_max(const double max) {
    data_->max_ = max;
  }

  void set_min(const double min) {
    data_->min_ = min;
  }

  void set_exchange_name(const std::string& exchange_name) {
    data_->exchange_name_ = exchange_name;
  }

  void set_platform_name(const std::string& platform_name) {
    data_->platform_name_ = platform_name;
  }

  void set_sort(const int8 sort) {
    data_->sort_ = sort;
  }

  void set_status(const int8 status){
    data_->status_;
  }


  void ValueSerialization(base_logic::DictionaryValue* dict);
 private:
  class Data {
   public:
    Data()
        : refcount_(1),
          id_(0),
          plaform_id_(0),
          amount_(0.0),
          profit_(0.0),
          deposit_(0.0),
          close_(0.0),
          open_(0.0),
          min_(0.0),
          max_(0.0),
          deferred_(0.0),
          sort_(0),
          status_(0) {
    }

    ~Data() {
    }

   public:
    int32 id_;
    int32 plaform_id_;
    int8 sort_;
    int8 status_;
    std::string name_;
    std::string code_;
    std::string symbol_;
    std::string unit_;
    double amount_;
    double profit_;
    double deposit_;
    double close_;
    double open_;
    double deferred_;
    double max_;
    double min_;
    std::string exchange_name_;
    std::string platform_name_;

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
