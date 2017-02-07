//  Copyright (c) 2015-2015 The swp Authors. All rights reserved.
//  Created on: 2016年12月30日 Author: kerry

#include "trades/trades_logic.h"
#include "trades/schduler_engine.h"
#include "trades/trades_proto_buf.h"
#include "basic/native_library.h"
#include "trades/operator_code.h"
#include "config/config.h"
#include "core/common.h"
#include "logic/logic_comm.h"
#include "logic/logic_unit.h"
#include "net/errno.h"
#include <string>

#define DEFAULT_CONFIG_PATH "./plugins/trades/trades_config.xml"

namespace trades_logic {

Tradeslogic *Tradeslogic::instance_ = NULL;

Tradeslogic::Tradeslogic() {
  if (!Init())
    assert(0);
}

Tradeslogic::~Tradeslogic() {
  if (trades_db_){delete trades_db_; trades_db_ = NULL;}
  trades_logic::TradesEngine::FreeSchdulerManager();
  trades_logic::TradesEngine::FreeTradesEngine();
}

bool Tradeslogic::Init() {
  bool r = false;
  std::string path = DEFAULT_CONFIG_PATH;
  config::FileConfig *config = config::FileConfig::GetFileConfig();
  if (config == NULL)
    return false;
  r = config->LoadConfig(path);
  trades_logic::TradesEngine::GetSchdulerManager();
  trades_db_ = new trades_logic::TradesDB(config);
  trades_logic::TradesEngine::GetSchdulerManager()->InitDB(trades_db_);
  trades_logic::TradesEngine::GetSchdulerManager()->InitGoodsData();
  return true;
}

Tradeslogic *Tradeslogic::GetInstance() {
  if (instance_ == NULL)
    instance_ = new Tradeslogic();
  return instance_;
}

void Tradeslogic::FreeInstance() {
  delete instance_;
  instance_ = NULL;
}

bool Tradeslogic::OnTradesConnect(struct server *srv, const int socket) {
  return true;
}

bool Tradeslogic::OnTradesMessage(struct server *srv, const int socket,
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
    case R_TRADES_GOODS_DATA:{
      OnPlatformsGoods(srv, socket, packet);
      break;
    }
  default:
    break;
  }
  return true;
}

bool Tradeslogic::OnTradesClose(struct server *srv, const int socket) {
  return true;
}

bool Tradeslogic::OnBroadcastConnect(struct server *srv, const int socket,
                                     const void *msg, const int len) {
  return true;
}

bool Tradeslogic::OnBroadcastMessage(struct server *srv, const int socket,
                                     const void *msg, const int len) {
  return true;
}

bool Tradeslogic::OnBroadcastClose(struct server *srv, const int socket) {
  return true;
}

bool Tradeslogic::OnIniTimer(struct server *srv) {
  if (srv->add_time_task != NULL) {
  }
  return true;
}

bool Tradeslogic::OnTimeout(struct server *srv, char *id, int opcode,
                            int time) {
  switch (opcode) {
  default:
    break;
  }
  return true;
}

bool Tradeslogic::OnPlatformsGoods(struct server* srv, int socket,
                                  struct PacketHead *packet) {
  trades_logic::net_request::Goods goods;
  struct PacketControl* packet_control = (struct PacketControl*) (packet);
  goods.set_http_packet(packet_control->body_);
  trades_logic::TradesEngine::GetSchdulerManager()->SendGoods(socket, goods.pid());
  return true;

}


} // namespace trades_logic
