//  Copyright (c) 2015-2015 The swp Authors. All rights reserved.
//  Created on: 2016年12月30日 Author: kerry

#include "trades/trades_logic.h"
#include "basic/native_library.h"
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

Tradeslogic::~Tradeslogic() {}

bool Tradeslogic::Init() {
  bool r = false;
  std::string path = DEFAULT_CONFIG_PATH;
  config::FileConfig *config = config::FileConfig::GetFileConfig();
  if (config == NULL)
    return false;
  r = config->LoadConfig(path);
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

  switch (packet->operate_code) {
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

} // namespace trades_logic
