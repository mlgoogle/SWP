//  Copyright (c) 2016-2017 The quotations Authors. All rights reserved.
//  Created on: 2017年1月7日 Author: kerry

#include "trades/schduler_engine.h"
#include "trades/trades_proto_buf.h"
#include "trades/operator_code.h"
#include "net/comm_head.h"
#include "net/packet_processing.h"
#include "logic/logic_unit.h"
#include "basic/template.h"

namespace trades_logic {

TradesManager* TradesEngine::schduler_mgr_ = NULL;
TradesEngine* TradesEngine::schduler_engine_ = NULL;

TradesManager::TradesManager() {
  trades_cache_ = new TradesCache();
  Init();
}

TradesManager::~TradesManager() {
  DeinitThreadrw(lock_);
  trades_cache_->trades_map_.clear();
  if (trades_cache_) {
    delete trades_cache_;
    trades_cache_ = NULL;
  }

}

void TradesManager::InitDB(trades_logic::TradesDB* trades_db) {
  trades_db_ = trades_db;
}

void TradesManager::Init() {
  InitThreadrw(&lock_);
}

void TradesManager::InitGoodsData() {
  std::list<trades_logic::GoodsInfo> list;
  trades_db_->OnFetchPlatformGoods(&list);
  while (list.size() > 0) {
    trades_logic::GoodsInfo goods_info = list.front();
    list.pop_front();
    SetGoodsUnit(goods_info);
  }
  list.clear();
}

void TradesManager::SetGoods(trades_logic::GoodsInfo& goods_info) {
  base_logic::WLockGd lk(lock_);
}

void TradesManager::SetGoodsUnit(trades_logic::GoodsInfo& goods_info) {
  GOODS_MAP goods_map;
  base::MapGet<PLAT_GOODS_MAP, PLAT_GOODS_MAP::iterator, int32, GOODS_MAP>(
      trades_cache_->trades_map_, goods_info.platform_id(), goods_map);
  goods_map[goods_info.id()] = goods_info;
  trades_cache_->trades_map_[goods_info.platform_id()] = goods_map;
}

void TradesManager::OnTimePosition(
    const int socket, trades_logic::TradesPosition& trades_position) {
  net_reply::TradesPosition r_trades_position;
  OpenPosition(trades_position);
  r_trades_position.set_position_id(trades_position.position_id());
  r_trades_position.set_id(trades_position.uid());
  r_trades_position.set_code_id(trades_position.code_id());
  r_trades_position.set_symbol(trades_position.symbol());
  r_trades_position.set_name(trades_position.name());
  r_trades_position.set_buy_sell(trades_position.buy_sell());
  r_trades_position.set_amount(trades_position.amount());
  r_trades_position.set_open_price(trades_position.open_price());
  r_trades_position.set_position_time(trades_position.open_position_time());
  r_trades_position.set_open_cost(trades_position.open_cost());
  r_trades_position.set_open_charge(trades_position.open_charge());
  r_trades_position.set_close_time(trades_position.close_position_time());
  r_trades_position.set_close_price(0.0);
  r_trades_position.set_gross_profit(0.0);
  r_trades_position.set_limit(0.0);
  r_trades_position.set_stop(0.0);
  r_trades_position.set_close_type(trades_position.close_type());
  r_trades_position.set_is_deferred(false);
  r_trades_position.set_deferred(0.0);
  r_trades_position.set_interval(
      trades_position.close_position_time()
          - trades_position.open_position_time());
  struct PacketControl packet_control;
  MAKE_HEAD(packet_control, S_TRADES_OPEN_POSITION, TRADES_TYPE, 0, 0, 0);
  packet_control.body_ = r_trades_position.get();
  send_message(socket, &packet_control);
}

void TradesManager::OpenPosition(
    trades_logic::TradesPosition& trades_position) {
  bool r = false;
  trades_logic::GoodsInfo good_info;
  {
    base_logic::RLockGd lk(lock_);
    //获取对应交易的商品
    bool r = false;
    GOODS_MAP goods_map;
    r =
        base::MapGet<PLAT_GOODS_MAP, PLAT_GOODS_MAP::iterator, int32, GOODS_MAP>(
            trades_cache_->trades_map_, 1002, goods_map);
    if (!r)
      return;

    r = base::MapGet<GOODS_MAP, GOODS_MAP::iterator, int32,
        trades_logic::GoodsInfo>(goods_map, trades_position.code_id(),
                                 good_info);
    if (!r)
      return;
  }
  swp_logic::Quotations quotation;
  trades_position.set_open_position_time(time(NULL));
  trades_position.set_close_position_time(
      trades_position.open_position_time() + ONE_MINUTE);
  //获取当前行情
  std::string key = good_info.platform_name() + ":" + good_info.exchange_name()
      + ":" + good_info.symbol();

  quotation.set_type(FORXE_TYPE);
  GetQuotations(key, quotation);
  trades_position.set_symbol(good_info.symbol());
  trades_position.set_name(good_info.name());
  trades_position.set_open_price(quotation.current_price());
  trades_position.set_open_charge(good_info.open());
  trades_position.set_close_type(TIMER_TYPE);
  //建仓总成本
  double open_all_cost = good_info.deposit() * trades_position.amount();
  //建仓成本
  double open_const = open_all_cost * (1 - trades_position.open_charge());

  //写入数据库 扣除用户费用及记录收入总金额
  trades_position.set_open_cost(open_const);

  r = trades_db_->OnOpenPosition(trades_position);
  //放入定时队列中
  if (r)
    SetTimePosition(trades_position);
}

bool TradesManager::DistributionTask() {
  base_logic::WLockGd lk(lock_);
  time_t current_time = time(NULL);
  trades_cache_->task_temp_list_.sort(trades_logic::TimeTask::cmp);
  std::list<trades_logic::TradesPosition> result_list;
  //获取当前行情
  while (trades_cache_->task_temp_list_.size() > 0) {
    trades_logic::TimeTask time_task = trades_cache_->task_temp_list_.front();
    trades_cache_->task_temp_list_.pop_front();
    if (current_time >= time_task.end_time()) {
      //时间到平仓
      TRADES_MAP::iterator trades_map_it = trades_cache_->all_trades_map_.find(
          time_task.id());
      trades_logic::TradesPosition trades_position = trades_map_it->second;
      double close_price = 7.123;
      trades_position.check_buy_sell(close_price);
      //写入结果数据库中,批量写入
      result_list.push_back(trades_position);
    } else {
      break;
    }
  }
  //批量写入数据库，做金额操作
  return true;
}

void TradesManager::SetTimePosition(
    trades_logic::TradesPosition& trades_position) {
  base_logic::WLockGd lk(lock_);
  TRADES_MAP user_trades_map;
  PLAT_TRADES_MAP::iterator plat_trades_it = trades_cache_->plat_trades_map_
      .find(1002);
  GOODS_TRADES_MAP& goods_map = plat_trades_it->second;
  GOODS_TRADES_MAP::iterator goods_trades_it = goods_map.find(
      trades_position.code_id());
  TRADES_MAP& trades_map = goods_trades_it->second;
  trades_map[trades_position.position_id()] = trades_position;
  trades_cache_->all_trades_map_[trades_position.position_id()] =
      trades_position;

  USER_TRADES_MAP::iterator user_trades_it = trades_cache_->user_trades_map_
      .find(trades_position.uid());
  if (user_trades_it != trades_cache_->user_trades_map_.end())
    user_trades_map = user_trades_it->second;

  user_trades_map[trades_position.position_id()] = trades_position;
  trades_cache_->user_trades_map_[trades_position.uid()] = user_trades_map;
}

void TradesManager::GetQuotationsNoLock(const std::string& key,
                                        swp_logic::Quotations& quotation) {
  QUOTATIONS_ALL_MAP::iterator quotations_all_it = trades_cache_
      ->quotations_map_.find(quotation.type());
  QUOTATIONS_MAP quotations = quotations_all_it->second;

  QUOTATIONS_MAP::iterator quotations_it = quotations.find(key);
  quotation = quotations_it->second;
  // quotations[key] = quotation;
}

void TradesManager::GetQuotations(const std::string& key,
                                  swp_logic::Quotations& quotation) {
  base_logic::RLockGd lk(lock_);
  GetQuotationsNoLock(key, quotation);
}

void TradesManager::SetQuotations(swp_logic::Quotations& quotation) {
  base_logic::WLockGd lk(lock_);
  QUOTATIONS_ALL_MAP::iterator quotations_it = trades_cache_->quotations_map_
      .find(quotation.type());
  QUOTATIONS_MAP quotations = quotations_it->second;
  std::string key;
  key = quotation.platform() + ":" + quotation.exchange_name() + ":"
      + quotation.symbol();
  quotations[key] = quotation;
  trades_cache_->quotations_map_[quotation.type()] = quotations;
}

void TradesManager::SendCurrentPosition(const int socket, const int64 uid) {
  base_logic::RLockGd lk(lock_);
  TRADES_MAP trades_map;
  int32 base_num = 5;
  bool r = base::MapGet<USER_TRADES_MAP, USER_TRADES_MAP::iterator, int64,
      TRADES_MAP>(trades_cache_->user_trades_map_, uid, trades_map);
  if (!r)
    return;

  net_reply::AllTradesPosition net_trades_positions;
  //遍历发送
  for (TRADES_MAP::iterator it = trades_map.begin(); it != trades_map.end();
      it++) {
    trades_logic::TradesPosition trades_position = it->second;
    net_reply::TradesPosition* net_trades_position =
        new net_reply::TradesPosition;
    net_trades_position->set_amount(trades_position.amount());
    net_trades_position->set_buy_sell(trades_position.buy_sell());
    net_trades_position->set_close_price(trades_position.close_price());
    net_trades_position->set_close_time(trades_position.close_position_time());
    net_trades_position->set_close_type(trades_position.close_type());
    net_trades_position->set_code_id(trades_position.code_id());
    net_trades_position->set_deferred(trades_position.deferred());
    net_trades_position->set_gross_profit(0.0);
    net_trades_position->set_id(trades_position.uid());
    net_trades_position->set_interval(
        trades_position.close_position_time()
            - trades_position.open_position_time());
    net_trades_position->set_is_deferred(trades_position.is_deferred());
    net_trades_position->set_limit(trades_position.limit());
    net_trades_position->set_name(trades_position.name());
    net_trades_position->set_open_charge(trades_position.open_charge());
    net_trades_position->set_open_cost(trades_position.open_cost());
    net_trades_position->set_open_price(trades_position.open_price());
    net_trades_position->set_position_id(trades_position.position_id());
    net_trades_position->set_position_time(
        trades_position.open_position_time());
    net_trades_position->set_stop(trades_position.stop());
    net_trades_position->set_symbol(trades_position.symbol());
    net_trades_positions.set_unit(net_trades_position->get());
    if (net_trades_positions.Size() % base_num == 0
        && net_trades_positions.Size() != 0) {
      struct PacketControl packet_control;
      MAKE_HEAD(packet_control, S_TRADES_CURRENT_POSITION, TRADES_TYPE, 0, 0,
                0);
      packet_control.body_ = net_trades_positions.get();
      send_message(socket, &packet_control);
      net_trades_positions.Reset();
    }
  }

  if (net_trades_positions.Size() > 0) {
    struct PacketControl packet_control;
    MAKE_HEAD(packet_control, S_TRADES_CURRENT_POSITION, TRADES_TYPE, 0, 0, 0);
    packet_control.body_ = net_trades_positions.get();
    send_message(socket, &packet_control);
  }
}

void TradesManager::SendGoods(const int socket, const int32 pid) {
  base_logic::WLockGd lk(lock_);
  GOODS_MAP goods_map;
  int32 base_num = 5;
  bool r = base::MapGet<PLAT_GOODS_MAP, PLAT_GOODS_MAP::iterator, int32,
      GOODS_MAP>(trades_cache_->trades_map_, pid, goods_map);
  if (!r)
    return;

  net_reply::Goods net_reply_goods;
  //遍历发送
  for (GOODS_MAP::iterator it = goods_map.begin(); it != goods_map.end();
      it++) {
    trades_logic::GoodsInfo goods = it->second;
    net_reply::GoodsUnit* goods_unit = new net_reply::GoodsUnit;
    goods_unit->set_exchange_name(goods.exchange_name());
    goods_unit->set_amount(goods.amount());
    goods_unit->set_close(goods.close());
    goods_unit->set_code(goods.code());
    goods_unit->set_deferred(goods.deferred());
    goods_unit->set_deposit(goods.deposit());
    goods_unit->set_max_lot(goods.max());
    goods_unit->set_min_lot(goods.min());
    goods_unit->set_open(goods.open());
    goods_unit->set_platform_name(goods.platform_name());
    goods_unit->set_profit(goods.profit());
    goods_unit->set_sort(goods.sort());
    goods_unit->set_status(goods.status());
    goods_unit->set_symbol(goods.symbol());
    goods_unit->set_unit(goods.unit());
    goods_unit->set_name(goods.name());
    goods_unit->set_show_name(goods.show_name());
    goods_unit->set_show_symbol(goods.show_symbol());
    goods_unit->set_id(goods.id());
    net_reply_goods.set_unit(goods_unit->get());
    if (net_reply_goods.Size() % base_num == 0 && net_reply_goods.Size() != 0) {
      struct PacketControl packet_control;
      MAKE_HEAD(packet_control, S_TRADES_GOODS_DATA, TRADES_TYPE, 0, 0, 0);
      packet_control.body_ = net_reply_goods.get();
      send_message(socket, &packet_control);
      net_reply_goods.Reset();
    }
  }

  if (net_reply_goods.Size() > 0) {
    struct PacketControl packet_control;
    MAKE_HEAD(packet_control, S_TRADES_GOODS_DATA, TRADES_TYPE, 0, 0, 0);
    packet_control.body_ = net_reply_goods.get();
    send_message(socket, &packet_control);
  }
}

void TradesManager::TimeEvent(int opcode, int time) {
  switch (opcode) {
    default:
      break;
  }
}

}
