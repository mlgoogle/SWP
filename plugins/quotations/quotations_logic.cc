//  Copyright (c) 2015-2015 The swp Authors. All rights reserved.
//  Created on: 2016年12月30日 Author: kerry

#include "quotations/quotations_logic.h"
#include "quotations/quotations_proto_buf.h"
#include "quotations/operator_code.h"
#include "quotations/schduler_engine.h"
#include "logic/swp_infos.h"
#include "config/config.h"
#include "core/common.h"
#include "logic/logic_comm.h"
#include "logic/logic_unit.h"
#include "net/errno.h"
#include <string>

#define DEFAULT_CONFIG_PATH "./plugins/trades/trades_config.xml"

namespace quatations_logic {

Quotationslogic *Quotationslogic::instance_ = NULL;

Quotationslogic::Quotationslogic() {
  if (!Init())
    assert(0);
}

Quotationslogic::~Quotationslogic() {
}

bool Quotationslogic::Init() {
  bool r = false;
  std::string path = DEFAULT_CONFIG_PATH;
  config::FileConfig *config = config::FileConfig::GetFileConfig();
  if (config == NULL)
    return false;
  r = config->LoadConfig(path);
  return true;
}

Quotationslogic *Quotationslogic::GetInstance() {
  if (instance_ == NULL)
    instance_ = new Quotationslogic();
  return instance_;
}

void Quotationslogic::FreeInstance() {
  delete instance_;
  instance_ = NULL;
}

bool Quotationslogic::OnQuotationsConnect(struct server *srv,
                                          const int socket) {
  return true;
}

bool Quotationslogic::OnQuotationsMessage(struct server *srv, const int socket,
                                          const void *msg, const int len) {
  bool r = false;
  struct PacketHead *packet = NULL;
  if (srv == NULL || socket < 0 || msg == NULL || len < PACKET_HEAD_LENGTH)
    return false;

  switch (packet->operate_code) {
    default:
      break;
  }
  return true;
}

bool Quotationslogic::OnQuotationsClose(struct server *srv, const int socket) {
  return true;
}

bool Quotationslogic::OnBroadcastConnect(struct server *srv, const int socket,
                                         const void *msg, const int len) {
  //像行情数据中心注册
  quotations_logic::QuotationsEngine::GetSchdulerManager()
      ->LoginQuotationsCenter(socket);
  return true;
}

bool Quotationslogic::OnBroadcastMessage(struct server *srv, const int socket,
                                         const void *msg, const int len) {
  bool r = false;
  struct PacketHead *packet = NULL;
  if (srv == NULL || socket < 0 || msg == NULL || len < PACKET_HEAD_LENGTH)
    return false;

  if (!net::PacketProsess::UnpackStream(msg, len, &packet)) {
    LOG_ERROR2("UnpackStream Error socket %d", socket);
    return false;
  }

  switch (packet->operate_code) {
    case QUOTATIONS_REAL_TIME_DATA: {
      OnQutations(srv, socket, packet);
      break;
    }
    default:
      break;
  }
  return true;
}

bool Quotationslogic::OnBroadcastClose(struct server *srv, const int socket) {
  return true;
}

bool Quotationslogic::OnIniTimer(struct server *srv) {
  if (srv->add_time_task != NULL) {
  }
  return true;
}

bool Quotationslogic::OnTimeout(struct server *srv, char *id, int opcode,
                                int time) {
  switch (opcode) {
    default:
      break;
  }
  return true;
}

bool Quotationslogic::OnQutations(struct server* srv, int socket,
                                  struct PacketHead *packet) {
  quotations_logic::net_request::RealTime real_time;
  swp_logic::Quotations quotations;
  quotations.set_change(real_time.change());
  quotations.set_closed_yesterday_price(real_time.closed_yesterday_price());
  quotations.set_current_price(real_time.current_price());
  quotations.set_current_unix_time(real_time.current_unix_time());
  quotations.set_exchange_name(real_time.exchange_name());
  quotations.set_high_price(real_time.high_price());
  quotations.set_low_price(real_time.low_price());
  quotations.set_opening_today_price(real_time.opening_today_price());
  quotations.set_pchg(real_time.pchg());
  quotations.set_platform_name(real_time.platform_name());
  quotations.set_symbol(real_time.symbol());
  quotations_logic::QuotationsEngine::GetSchdulerManager()->SetQuotations(
      quotations);
  return true;
}

}  // namespace trades_logic
