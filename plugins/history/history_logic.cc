//  Copyright (c) 2017-2018 The SWP Authors. All rights reserved.
//  Created on: 2017年1月12日 Author: kerry

#include "history/history_logic.h"
#include "history/history_proto_buf.h"
#include "history/operator_code.h"
#include "history/errno.h"
#include "history/schduler_engine.h"
#include "logic/swp_infos.h"
#include "config/config.h"
#include "core/common.h"
#include "logic/logic_comm.h"
#include "logic/logic_unit.h"
#include "net/errno.h"
#include <string>

#define DEFAULT_CONFIG_PATH "./plugins/history/history_config.xml"

namespace history_logic {

Historylogic *Historylogic::instance_ = NULL;

Historylogic::Historylogic() {
  if (!Init())
    assert(0);
}

Historylogic::~Historylogic() {
  if (history_db_) {
    delete history_db_;
    history_db_ = NULL;
  }
  history_logic::HistoryEngine::FreeSchdulerManager();
  history_logic::HistoryEngine::FreeHistoryEngine();
}

bool Historylogic::Init() {
  bool r = false;
  std::string path = DEFAULT_CONFIG_PATH;
  config::FileConfig *config = config::FileConfig::GetFileConfig();
  if (config == NULL)
    return false;
  r = config->LoadConfig(path);
  history_db_ = new history_logic::HistoryDB(config);
  history_logic::HistoryEngine::GetSchdulerManager()->InitDB(history_db_);
  history_logic::HistoryEngine::GetSchdulerManager()->InitHistoryTradesData();
  return true;
}

Historylogic *Historylogic::GetInstance() {
  if (instance_ == NULL)
    instance_ = new Historylogic();
  return instance_;
}

void Historylogic::FreeInstance() {
  delete instance_;
  instance_ = NULL;
}

bool Historylogic::OnHistoryConnect(struct server *srv, const int socket) {
  std::string ip;
  int port;
  logic::SomeUtils::GetIPAddress(socket, ip, port);
  LOG_MSG2("ip {%s} prot {%d}", ip.c_str(), port);
  return true;
}

bool Historylogic::OnHistoryMessage(struct server *srv, const int socket,
                                    const void *msg, const int len) {
  bool r = false;
  struct PacketHead *packet = NULL;
  if (srv == NULL || socket < 0 || msg == NULL || len < PACKET_HEAD_LENGTH)
    return false;

  if (!net::PacketProsess::UnpackStream(msg, len, &packet)) {
    LOG_ERROR2("UnpackStream Error socket %d", socket);
    send_error(socket,ERROR_TYPE,ERROR_TYPE,FORMAT_ERRNO);
    return false;
  }

  switch (packet->operate_code) {
    case R_HISTORY_TRADES: {
      OnHistoryTrades(srv, socket, packet);
      break;
    }
    default:
      break;
  }
  return true;
}

bool Historylogic::OnHistoryClose(struct server *srv, const int socket) {
  return true;
}

bool Historylogic::OnBroadcastConnect(struct server *srv, const int socket,
                                      const void *msg, const int len) {
  return true;
}

bool Historylogic::OnBroadcastMessage(struct server *srv, const int socket,
                                      const void *msg, const int len) {

  return true;
}

bool Historylogic::OnBroadcastClose(struct server *srv, const int socket) {
  return true;
}

bool Historylogic::OnIniTimer(struct server *srv) {
  if (srv->add_time_task != NULL) {
  }
  return true;
}

bool Historylogic::OnTimeout(struct server *srv, char *id, int opcode,
                             int time) {
  switch (opcode) {
    default:
      break;
  }
  return true;
}

bool Historylogic::OnHistoryTrades(struct server* srv, int socket,
                                   struct PacketHead *packet) {
  history_logic::net_request::HistoryPosition history_position;
  struct PacketControl* packet_control = (struct PacketControl*) (packet);
  bool r = history_position.set_http_packet(packet_control->body_);
  if (!r){
    LOG_DEBUG2("packet_length %d",packet->packet_length);
    send_error(socket,ERROR_TYPE,ERROR_TYPE,FORMAT_ERRNO);
    return false;
  }
  history_logic::HistoryEngine::GetSchdulerManager()->SendHistoryTrades(
      socket, packet->session_id,history_position.id(), history_position.start(), history_position.count());
  return true;
}

}  // namespace trades_logic
