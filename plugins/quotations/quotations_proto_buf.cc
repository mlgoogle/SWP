//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月8日 Author: kerry

#include "quotations_proto_buf.h"
#include "basic/basic_util.h"

namespace quotations_logic {

namespace net_request {

void RealTime::set_http_packet(base_logic::DictionaryValue* value) {
  bool r = false;
  double change = 0.0;
  double pchg = 0.0;
  double opening_today_price = 0.0;
  double closed_yesterday_price = 0.0;
  double current_price = 0.0;
  double current_unix_time = 0.0;
  double high_price = 0.0;
  double low_price = 0.0;
  double type = 0.0;
  std::string exchange_name;
  std::string platform_name;
  std::string symbol;

  r = value->GetReal(L"change", &change);
  if (r)
    set_change(change);

  r = value->GetReal(L"pchg", &pchg);
  if (r)
    set_pchg(pchg);

  r = value->GetReal(L"opening_today_price", &opening_today_price);
  if (r)
    set_opening_today_price(opening_today_price);

  r = value->GetReal(L"closed_yesterday_price", &closed_yesterday_price);
  if (r)
    set_closed_yesterday_price(closed_yesterday_price);

  r = value->GetReal(L"current_price", &current_price);
  if (r)
    set_current_price(current_price);

  r = value->GetReal(L"current_unix_time", &current_unix_time);
  if (r)
    set_current_unix_time(current_unix_time);

  r = value->GetReal(L"low_price", &low_price);
  if (r)
    set_low_price(low_price);

  r = value->GetReal(L"high_price", &high_price);
  if (r)
    set_high_price(high_price);

  r = value->GetReal(L"type", &type);
  if (r)
    set_type(type);

  r = value->GetString(L"exchange_name", &exchange_name);
  if (r)
    set_exchange_name(exchange_name);

  r = value->GetString(L"platform_name", &platform_name);
  if (r)
    set_platform_name(platform_name);

  r = value->GetString(L"symbol", &symbol);
  if (r)
    set_symbol(symbol);
}

}

namespace net_reply {

}

}
