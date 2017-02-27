//  Copyright (c) 2017-2018 The SWP Authors. All rights reserved.
//  Created on: 2017年2月12日 Author: kerry

#ifndef HISTORY_SCHDULER_ENGINE_H__
#define HISTORY_SCHDULER_ENGINE_H__

#include "logic/swp_infos.h"
#include "history/history_info.h"
#include "history/history_db.h"
#include "thread/base_thread_handler.h"
#include "thread/base_thread_lock.h"

namespace history_logic {

typedef std::map<int64, swp_logic::TradesPosition> TRADES_MAP;/*交易ID为key*/
typedef std::map<int64, TRADES_MAP> ALL_TRADES_MAP;/*用户ID 为key*/

class HistoryCache {
 public:
  ALL_TRADES_MAP all_trades_map_;
};

class HistoryManager {
 public:
  HistoryManager();
  virtual ~HistoryManager();
  void InitDB(history_logic::HistoryDB* history_db);
  void InitHistoryTradesData();
  void SendHistoryTrades(const int socket,const int64 session, const int64 uid,
                         const int64 pos, const int64 count = 10);
 private:
  void Init();
  void SetHistoryTradesNoLock(swp_logic::TradesPosition& trades);
  void GetHistoryTradesNoLock(const int64 uid, std::list<swp_logic::TradesPosition>& list,
                              const int64 pos = 0, const int64 count = 10);
 private:
  history_logic::HistoryDB* history_db_;
  HistoryCache *history_cache_;
  struct threadrw_t *lock_;
};

class HistoryEngine {
 private:
  static HistoryEngine* schduler_engine_;
  static HistoryManager* schduler_mgr_;

  HistoryEngine() {
  }
  virtual ~HistoryEngine() {
  }
 public:
  static HistoryManager* GetSchdulerManager() {
    if (schduler_mgr_ == NULL)
      schduler_mgr_ = new HistoryManager();
    return schduler_mgr_;
  }

  static HistoryEngine* GetQuotationsEngine() {
    if (schduler_engine_ == NULL)
      schduler_engine_ = new HistoryEngine();
    return schduler_engine_;
  }


  static void FreeSchdulerManager() {
    if (schduler_mgr_) {
      delete schduler_mgr_;
      schduler_mgr_ = NULL;
    }
  }

  static void FreeHistoryEngine() {
    if (schduler_engine_) {
      delete schduler_engine_;
      schduler_engine_ = NULL;
    }
  }
};
}

#endif
