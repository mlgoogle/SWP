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


typedef std::map<int64,trades_logic::TradesPosition> TRADES_MAP; /*交易记录 uid或pid<->Trades*/
typedef std::map<int32,TRADES_MAP>  GOODS_TRADES_MAP;/*交易标的  商品ID<->交易记录*/
typedef std::map<int64,GOODS_TRADES_MAP> PLAT_TRADES_MAP;

//当前报价
typedef std::map<std::string, swp_logic::Quotations> QUOTATIONS_MAP;
typedef std::map<int64, QUOTATIONS_MAP> QUOTATIONS_ALL_MAP;


//定时渠道
typedef std::map<int64, trades_logic::TimeTask> TASKINFO_MAP;
typedef std::list<trades_logic::TimeTask> TASKINFO_LIST;

namespace trades_logic {

class TradesCache {
 public:
  PLAT_GOODS_MAP         trades_map_;
  PLAT_TRADES_MAP        plat_trades_map_;
  TRADES_MAP             all_trades_map_;
  QUOTATIONS_ALL_MAP     quotations_map_;

  TASKINFO_LIST          task_temp_list_;
  TASKINFO_MAP           task_temp_map_;
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

  void OpenPosition(trades_logic::TradesPosition& trades_position);

  void SetTimePosition(trades_logic::TradesPosition& trades_position);

  void SetQuotations(swp_logic::Quotations& quotation);

  void GetQuotations(const std::string& key, swp_logic::Quotations& quotation);

  void GetQuotationsNoLock(const std::string& key, swp_logic::Quotations& quotation);

  bool DistributionTask();
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
