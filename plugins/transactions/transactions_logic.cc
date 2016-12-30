//  Copyright (c) 2015-2015 The swp Authors. All rights reserved.
//  Created on: 2016年12月30日 Author: kerry

#include  <string>
#include "transactions/transactions_logic.h"
#include "core/common.h"
#include "config/config.h"
#include "basic/native_library.h"
#include "net/errno.h"
#include "logic/logic_comm.h"
#include "logic/logic_unit.h"

#define DEFAULT_CONFIG_PATH     "./plugins/transactions/transactions_config.xml"

namespace transactions_logic {

Transactionslogic* Transactionslogic::instance_ = NULL;

Transactionslogic::Transactionslogic() {
  if (!Init())
    assert(0);
}

Transactionslogic::~Transactionslogic() {
}

bool Transactionslogic::Init() {
  bool r = false;
  std::string path = DEFAULT_CONFIG_PATH;
  config::FileConfig* config = config::FileConfig::GetFileConfig();
  if (config == NULL)
    return false;
  r = config->LoadConfig(path);
  return true;
}

Transactionslogic*
Transactionslogic::GetInstance() {
  if (instance_ == NULL)
    instance_ = new Transactionslogic();
  return instance_;
}

void Transactionslogic::FreeInstance() {
  delete instance_;
  instance_ = NULL;
}

bool Transactionslogic::OnTransactionsConnect(struct server *srv,
                                              const int socket) {
  return true;
}

bool Transactionslogic::OnTransactionsMessage(struct server *srv,
                                              const int socket, const void *msg,
                                              const int len) {
  bool r = false;
  struct PacketHead* packet = NULL;
  if (srv == NULL || socket < 0 || msg == NULL || len < PACKET_HEAD_LENGTH)
    return false;

  switch (packet->operate_code) {
    default:
      break;
  }
  return true;
}

bool Transactionslogic::OnTransactionsClose(struct server *srv,
                                            const int socket) {
  return true;
}

bool Transactionslogic::OnBroadcastConnect(struct server *srv, const int socket,
                                           const void *msg, const int len) {
  return true;
}

bool Transactionslogic::OnBroadcastMessage(struct server *srv, const int socket,
                                           const void *msg, const int len) {
  return true;
}

bool Transactionslogic::OnBroadcastClose(struct server *srv, const int socket) {
  return true;
}

bool Transactionslogic::OnIniTimer(struct server *srv) {
  if (srv->add_time_task != NULL) {
  }
  return true;
}

bool Transactionslogic::OnTimeout(struct server *srv, char *id, int opcode,
                                  int time) {
  switch (opcode) {
    default:
      break;
  }
  return true;
}

}  // namespace transactions_logic

