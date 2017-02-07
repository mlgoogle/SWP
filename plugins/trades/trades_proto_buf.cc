//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月8日 Author: kerry

#include "trades/trades_proto_buf.h"
#include "basic/basic_util.h"

namespace trades_logic {

namespace net_request {

void Goods::set_http_packet(base_logic::DictionaryValue* value) {
  bool r = false;
  int64 id = 0;
  std::string token;
  int64 pid = 0;
  r = value->GetBigInteger(L"id", &id);
  if (r) {
    set_id(id);
  }

  r = value->GetString(L"token", &token);
  if (r)
    set_token(token);

  r = value->GetBigInteger(L"pid", &pid);
  if (r) {
    int32 temp = 0;
    temp = pid;
    set_pid(temp);
  }
}

}

}
