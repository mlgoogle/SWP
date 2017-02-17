//  Copyright (c) 2017-2018 The SWP Authors. All rights reserved.
//  Created on: 2017年2月12日 Author: kerry

#ifndef SWP_HISTORY_DB_H_
#define SWP_HISTORY_DB_H_

#include <string>
#include <list>
#include "history/history_info.h"
#include "storage/data_engine.h"
#include "config/config.h"
#include "basic/basictypes.h"
#include "logic/base_values.h"
#include "basic/scoped_ptr.h"

namespace history_logic {

class HistoryDB {
 public:
  HistoryDB(config::FileConfig* config);
  ~HistoryDB();

 public:
  bool OnHistroyTradesRecord(std::list<history_logic::TradesPosition>* list);

 public:
  static void CallHistroyTradesTradesRecord(void* param, base_logic::Value* value);
 private:
  base_logic::DataEngine* mysql_engine_;
};

}  // namespace history_logic

#endif /* SWP_HISTORY_DB_H_ */
