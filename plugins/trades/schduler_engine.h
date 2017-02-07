//  Copyright (c) 2016-2017 The quotations Authors. All rights reserved.
//  Created on: 2017年1月7日 Author: kerry

#ifndef TRADES_SCHDULER_ENGINE_H__
#define TRADES_SCHDULER_ENGINE_H__

#include "logic/swp_infos.h"
#include "trades/trades_db.h"
#include "trades/trades_info.h"
#include "thread/base_thread_handler.h"
#include "thread/base_thread_lock.h"

typedef std::map<int32,trades_logic::GoodsInfo> GOODS_MAP;
typedef std::map<int32,GOODS_MAP> PLAT_GOODS_MAP; /*对应平台能交易的商品*/

namespace trades_logic {

class TradesCache {
 public:
  PLAT_GOODS_MAP  trades_map_;
};

class TradesManager {
 public:
  TradesManager();
  virtual ~TradesManager();

  void SetGoods(trades_logic::GoodsInfo& goods_info);


  void TimeEvent(int opcode, int time);

  void InitDB(trades_logic::TradesDB* trades_db);

  void InitGoodsData();

  void SendGoods(const int socket,const int32 pid);


 private:
  void  Init();
  void SetGoodsUnit(trades_logic::GoodsInfo& goods_info);
 private:
  TradesCache *trades_cache_;
  trades_logic::TradesDB*  trades_db_;
  struct threadrw_t *lock_;
};

class TradesEngine {
 private:
  static TradesEngine* schduler_engine_;
  static TradesManager* schduler_mgr_;

  TradesEngine() {
  }
  virtual ~TradesEngine() {
  }
 public:
  static TradesManager* GetSchdulerManager() {
    if (schduler_mgr_ == NULL)
      schduler_mgr_ = new TradesManager();
    return schduler_mgr_;
  }

  static TradesEngine* GetTradesEngine() {
    if (schduler_engine_ == NULL)
      schduler_engine_ = new TradesEngine();
    return schduler_engine_;
  }

  static void FreeSchdulerManager(){
    if (schduler_mgr_) {delete schduler_mgr_; schduler_mgr_ = NULL;}
  }

  static void FreeTradesEngine(){
    if (schduler_engine_) {delete schduler_engine_; schduler_engine_ = NULL;}
  }
};
}

#endif
