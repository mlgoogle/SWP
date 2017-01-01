//  Copyright (c) 2015-2015 The swp Authors. All rights reserved.
//  Created on: 2016年12月30日 Author: kerry

#include "quotations/quotations_logic.h"
#include "basic/native_library.h"
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

Quotationslogic::~Quotationslogic() {}

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

bool Quotationslogic::OnQuotationsConnect(struct server *srv, const int socket) {
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
  return true;
}

bool Quotationslogic::OnBroadcastMessage(struct server *srv, const int socket,
                                     const void *msg, const int len) {
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

} // namespace trades_logic
