//  Copyright (c) 2016-2017 The SWP Authors. All rights reserved.
//  Created on: 2017年1月7日 Author: kerry

#include "history/schduler_engine.h"
#include "history/history_proto_buf.h"
#include "history/operator_code.h"
#include "history/errno.h"
#include "net/comm_head.h"
#include "net/packet_processing.h"
#include "logic/logic_unit.h"
#include "basic/template.h"

namespace history_logic {

HistoryManager* HistoryEngine::schduler_mgr_ = NULL;
HistoryEngine* HistoryEngine::schduler_engine_ = NULL;

HistoryManager::HistoryManager() {
  history_cache_ = new HistoryCache();
  Init();
}

HistoryManager::~HistoryManager() {
  DeinitThreadrw(lock_);

}

void HistoryManager::Init() {
  InitThreadrw(&lock_);
}

void HistoryManager::InitDB(history_logic::HistoryDB* history_db) {
  history_db_ = history_db;
}

void HistoryManager::InitHistoryTradesData() {
  std::list<history_logic::TradesPosition> list;
  history_db_->OnHistroyTradesRecord(&list);
  while (list.size() > 0) {
    history_logic::TradesPosition trades = list.front();
    list.pop_front();
    SetHistoryTradesNoLock(trades);
  }
}

void HistoryManager::SendHistoryTrades(const int socket, const int64 session,
                                       const int64 uid, const int64 pos,
                                       const int64 count) {
  std::list<history_logic::TradesPosition> trades_list;
  {
    base_logic::RLockGd lk(lock_);
    GetHistoryTradesNoLock(uid, trades_list, 0, 0);
  }

  //没有对应的历史记录
  if (trades_list.size() <=0){
    send_error(socket,ERROR_TYPE,ERROR_TYPE,NO_HAVE_HISTROY_DATA);
    return;
  }
  int32 base_num = 5;
  base_num = base_num < count ? base_num : count;
  int32 t_start = 0;
  int32 t_count = 0;

  history_logic::net_reply::AllTradesPosition net_trades_positions;

  while (trades_list.size() > 0 && t_count < count) {
    history_logic::TradesPosition trades_position = trades_list.front();
    trades_list.pop_front();
    t_start++;
    if (t_start < pos)
      continue;
    net_reply::TradesPosition* net_trades_position =
        new net_reply::TradesPosition;
    net_trades_position->set_amount(trades_position.amount());
    net_trades_position->set_buy_sell(trades_position.buy_sell());
    net_trades_position->set_close_price(trades_position.close_price());
    net_trades_position->set_close_time(trades_position.close_position_time());
    net_trades_position->set_close_type(trades_position.close_type());
    net_trades_position->set_gross_profit(trades_position.gross_profit());
    net_trades_position->set_code_id(trades_position.code_id());
    net_trades_position->set_deferred(trades_position.deferred());
    net_trades_position->set_gross_profit(trades_position.gross_profit());
    net_trades_position->set_id(trades_position.uid());
    net_trades_position->set_close_type(trades_position.close_type());
    net_trades_position->set_interval(
        trades_position.close_position_time()
            - trades_position.open_position_time());
    net_trades_position->set_result(trades_position.result());
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
    t_count++;
    if (net_trades_positions.Size() % base_num == 0
        && net_trades_positions.Size() != 0) {
      struct PacketControl packet_control;
      MAKE_HEAD(packet_control, S_HISTORY_TRADES, HISTORY_TYPE, 0, session, 0);
      packet_control.body_ = net_trades_positions.get();
      send_message(socket, &packet_control);
      net_trades_positions.Reset();
    }
  }

  if (net_trades_positions.Size() > 0) {
    struct PacketControl packet_control;
    MAKE_HEAD(packet_control, S_HISTORY_TRADES, HISTORY_TYPE, 0, session, 0);
    packet_control.body_ = net_trades_positions.get();
    send_message(socket, &packet_control);
  }
}

void HistoryManager::GetHistoryTradesNoLock(
    const int64 uid, std::list<history_logic::TradesPosition>& list,
    const int64 pos, const int64 count) {
  TRADES_MAP trades_map;
  base::MapGet<ALL_TRADES_MAP, ALL_TRADES_MAP::iterator, int64, TRADES_MAP>(
      history_cache_->all_trades_map_, uid, trades_map);

  for (TRADES_MAP::iterator it = trades_map.begin(); it != trades_map.end();
      it++) {
    history_logic::TradesPosition trades = it->second;
    list.push_back(trades);
  }
}

void HistoryManager::SetHistoryTradesNoLock(
    history_logic::TradesPosition& trades) {
  TRADES_MAP trades_map;
  base::MapGet<ALL_TRADES_MAP, ALL_TRADES_MAP::iterator, int64, TRADES_MAP>(
      history_cache_->all_trades_map_, trades.uid(), trades_map);
  trades_map[trades.position_id()] = trades;
  history_cache_->all_trades_map_[trades.uid()] = trades_map;
}

}
