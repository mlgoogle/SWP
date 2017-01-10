//  Copyright (c) 2016-2017 The quotations Authors. All rights reserved.
//  Created on: 2017年1月7日 Author: kerry

#include "quotations/schduler_engine.h"
#include "quotations/quotations_proto_buf.h"
#include "quotations/operator_code.h"
#include "net/comm_head.h"
#include "net/packet_processing.h"
#include "logic/logic_unit.h"
#include "basic/template.h"

namespace quotations_logic {

QuotationsManager* QuotationsEngine::schduler_mgr_ = NULL;
QuotationsEngine* QuotationsEngine::schduler_engine_ = NULL;

QuotationsManager::QuotationsManager() {
  quotations_cache_ = new QuotationsCache();
  Init();
}

QuotationsManager::~QuotationsManager() {
  DeinitThreadrw(lock_);
  quotations_cache_->quotations_map_.clear();
  if (quotations_cache_) {
    delete quotations_cache_;
    quotations_cache_ = NULL;
  }

}

void QuotationsManager::Init() {
  InitThreadrw(&lock_);
}

void QuotationsManager::SetQuotations(swp_logic::Quotations& quotation) {
  base_logic::WLockGd lk(lock_);
  bool r = false;
  QUOTATIONS_MAP exchange_quotations;
  QUOTATIONS_LIST quotations_list;
  r = base::MapGet<QUOTATIONS_ALL_MAP, QUOTATIONS_ALL_MAP::iterator, int32,
      QUOTATIONS_MAP>(quotations_cache_->quotations_map_, quotation.type(),
                      exchange_quotations);
  r = base::MapGet<QUOTATIONS_MAP, QUOTATIONS_MAP::iterator, std::string,
      QUOTATIONS_LIST>(exchange_quotations, quotation.symbol(),
                       quotations_list);
  quotations_list.push_back(quotation);
  exchange_quotations[quotation.symbol()] = quotations_list;
  quotations_cache_->quotations_map_[quotation.type()] = exchange_quotations;
}

void QuotationsManager::TimeEvent(int opcode, int time) {
  switch (opcode) {
    default:
      break;
  }
}

void QuotationsManager::LoginQuotationsCenter(const int socket) {
  quotations_logic::net_reply::Login login;
  login.set_aid(10001);
  login.set_passowrd("1234567x");
  struct PacketControl  packet_control;
  MAKE_HEAD(packet_control, LOGIN_QUOTATIONS, 1, 0, 0, 0);
  packet_control.body_ = login.get();
  send_message(socket, &packet_control);
}
}
