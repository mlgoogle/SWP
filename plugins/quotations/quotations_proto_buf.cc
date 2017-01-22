//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月8日 Author: kerry

#include "quotations_proto_buf.h"
#include "basic/basic_util.h"

namespace quotations_logic {

namespace net_other {

void RealTime::set_http_packet(base_logic::DictionaryValue* value) {
  bool r = false;
  double change = 0.0;
  double pchg = 0.0;
  double opening_today_price = 0.0;
  double closed_yesterday_price = 0.0;
  double current_price = 0.0;
  int64 current_unix_time = 0.0;
  double high_price = 0.0;
  double low_price = 0.0;
  int64  type = 0.0;
  std::string exchange_name;
  std::string platform_name;
  std::string symbol;

  r = value->GetReal(L"change", &change);
  if (r)
    set_change(change);

  r = value->GetReal(L"pchg", &pchg);
  if (r)
    set_pchg(pchg);

  r = value->GetReal(L"openingTodayPrice", &opening_today_price);
  if (r)
    set_opening_today_price(opening_today_price);

  r = value->GetReal(L"closedYesterdayPrice", &closed_yesterday_price);
  if (r)
    set_closed_yesterday_price(closed_yesterday_price);

  r = value->GetReal(L"currentPrice", &current_price);
  if (r)
    set_current_price(current_price);

  r = value->GetBigInteger(L"priceTime", &current_unix_time);
  if (r)
    set_current_unix_time(current_unix_time);

  r = value->GetReal(L"lowPrice", &low_price);
  if (r)
    set_low_price(low_price);

  r = value->GetReal(L"highPrice", &high_price);
  if (r)
    set_high_price(high_price);

  r = value->GetBigInteger(L"type", &type);
  if (r)
    set_type(type);

  r = value->GetString(L"exchangeName", &exchange_name);
  if (r)
    set_exchange_name(exchange_name);

  r = value->GetString(L"platformName", &platform_name);
  if (r)
    set_platform_name(platform_name);

  r = value->GetString(L"symbol", &symbol);
  if (r)
    set_symbol(symbol);
}

}

namespace net_request {



void TimeLine::set_htt_packet(base_logic::DictionaryValue* value) {
  bool r = false;
  int64 id = 0;
  std::string token;
  std::string exchange_name;
  std::string platform_name;
  std::string good_type;

  r = value->GetBigInteger(L"id",& id);
  if (r)
    set_id(id);

  r = value->GetString(L"token", &token);
  if (r)
    set_token(token);

  r = value->GetString(L"exchangeName",&exchange_name);
  if (r)
    set_exchange_name(exchange_name);

  r = value->GetString(L"platformName", &platform_name);
  if (r)
    set_platform_name(platform_name);

  r = value->GetString(L"goodType", &good_type);
  if (r)
    set_good_type(good_type);
}


void RealTimeUnit::set_htt_packet(base_logic::DictionaryValue* value) {
  bool r = false;
  std::string exchange_name;
  std::string platform_name;
  std::string good_type;
  r = value->GetString(L"exchangeName", &exchange_name);
  if (r)
    set_exchange_name(exchange_name);

  r = value->GetString(L"platformName", &platform_name);
  if (r)
    set_platform_name(platform_name);

  r = value->GetString(L"goodType", &good_type);
  if (r)
    set_good_type(good_type);
}

void RealTime::set_htt_packet(base_logic::DictionaryValue* value) {
  bool r = false;
  int64 id = 0;
  std::string token;

  r = value->GetBigInteger(L"id", &id);
  if (r)
    set_id(id);

  r = value->GetString(L"token", &token);
  if (r)
    set_token(token);

  r = value->GetList(L"goodsinfos", &goods_infos_);
}


}

namespace net_reply {

}

}
