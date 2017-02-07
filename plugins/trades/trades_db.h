//  Copyright (c) 2015-2015 The KID Authors. All rights reserved.
//  Created on: 2015年9月17日 Author: kerry

#ifndef SWP_TRADES_DB_H_
#define SWP_TRADES_DB_H_

#include <string>
#include <list>
#include "trades/trades_info.h"
#include "storage/data_engine.h"
#include "config/config.h"
#include "basic/basictypes.h"
#include "logic/base_values.h"
#include "basic/scoped_ptr.h"

namespace trades_logic {

class TradesDB {
 public:
  TradesDB(config::FileConfig* config);
  ~TradesDB();

 public:
  bool OnFetchPlatformGoods(std::list<trades_logic::GoodsInfo>* list);
 public:
  static void CallFecthPlatformGoods(void* param, base_logic::Value* value);
 private:
  base_logic::DataEngine* mysql_engine_;
};

}  // namespace trades_logic

#endif /* SWP_TRADES_DB_H_ */
