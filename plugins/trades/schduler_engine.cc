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
