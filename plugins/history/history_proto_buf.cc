//  Copyright (c) 2016-2017 The SWP Authors. All rights reserved.
//  Created on: 2016年1月12日 Author: kerry

#include "history_proto_buf.h"
#include "basic/basic_util.h"

namespace history_logic {

namespace net_request {

void HistoryPosition::set_http_packet(base_logic::DictionaryValue* value) {
  bool r = false;
  int64 id = 0;
  std::string token;
  r = value->GetBigInteger(L"id", &id);
  if (r)
    set_id(id);

  r = value->GetString(L"token", &token);
  if (r)
    set_token(token);
}

}

namespace net_reply {

}

}
