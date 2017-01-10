//  Copyright (c) 2016-2017 The quotations Authors. All rights reserved.
//  Created on: 2017年1月7日 Author: kerry

#ifndef QUOTATIONS_SCHDULER_ENGINE_H__
#define QUOTATIONS_SCHDULER_ENGINE_H__

#include "logic/swp_infos.h"
#include "thread/base_thread_handler.h"
#include "thread/base_thread_lock.h"

typedef std::list<swp_logic::Quotations> QUOTATIONS_LIST;
typedef std::map<std::string, QUOTATIONS_LIST> QUOTATIONS_MAP; /*现货ID，行情*/
typedef std::map<int64,QUOTATIONS_MAP> QUOTATIONS_ALL_MAP; /*股票,现货,期货 QUOTATIONS_MAP*/

namespace quotations_logic {

class QuotationsCache {
 public:
  QUOTATIONS_ALL_MAP  quotations_map_;
};

class QuotationsManager {
 public:
  QuotationsManager();
  virtual ~QuotationsManager();

  void SetQuotations(swp_logic::Quotations& quotation);

  void LoginQuotationsCenter(const int socket);

  void TimeEvent(int opcode, int time);
 private:
  void  Init();
 private:
  QuotationsCache *quotations_cache_;
  struct threadrw_t *lock_;
};

class QuotationsEngine {
 private:
  static QuotationsEngine* schduler_engine_;
  static QuotationsManager* schduler_mgr_;

  QuotationsEngine() {
  }
  virtual ~QuotationsEngine() {
  }
 public:
  static QuotationsManager* GetSchdulerManager() {
    if (schduler_mgr_ == NULL)
      schduler_mgr_ = new QuotationsManager();
    return schduler_mgr_;
  }

  static QuotationsEngine* GetQuotationsEngine() {
    if (schduler_engine_ == NULL)
      schduler_engine_ = new QuotationsEngine();
    return schduler_engine_;
  }
};
}

#endif
