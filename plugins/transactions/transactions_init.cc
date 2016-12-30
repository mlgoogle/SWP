//  Copyright (c) 2015-2015 The SWP Authors. All rights reserved.
//  Created on: 2016年12月30日 Author: kerry

#include "transactions/transactions_init.h"
#include "core/common.h"
#include "core/plugins.h"
#include "transactions/transactions_logic.h"

struct transactionsplugin {
  char* id;
  char* name;
  char* version;
  char* provider;
};

static void *OnTransactionsStart() {
  signal(SIGPIPE, SIG_IGN);
  struct transactionsplugin* transactions = (struct transactionsplugin*) calloc(
      1, sizeof(struct transactionsplugin));
  transactions->id = "transactions";
  transactions->name = "transactions";
  transactions->version = "1.0.0";
  transactions->provider = "kerry";
  if (!transactions_logic::Transactionslogic::GetInstance())
    assert(0);
  return transactions;
}

static handler_t OnTransactionsShutdown(struct server* srv, void* pd) {
  transactions_logic::Transactionslogic::FreeInstance();

  return HANDLER_GO_ON;
}

static handler_t OnTransactionsConnect(struct server *srv, int fd, void *data,
                                       int len) {
  transactions_logic::Transactionslogic::GetInstance()->OnTransactionsConnect(
      srv, fd);
  return HANDLER_GO_ON;
}

static handler_t OnTransactionsMessage(struct server *srv, int fd, void *data,
                                       int len) {
  transactions_logic::Transactionslogic::GetInstance()->OnTransactionsMessage(
      srv, fd, data, len);
  return HANDLER_GO_ON;
}

static handler_t OnTransactionsClose(struct server *srv, int fd) {
  transactions_logic::Transactionslogic::GetInstance()->OnTransactionsClose(srv,
                                                                            fd);
  return HANDLER_GO_ON;
}

static handler_t OnUnknow(struct server *srv, int fd, void *data, int len) {
  return HANDLER_GO_ON;
}

static handler_t OnBroadcastConnect(struct server* srv, int fd, void *data,
                                    int len) {
  transactions_logic::Transactionslogic::GetInstance()->OnBroadcastConnect(srv,
                                                                           fd,
                                                                           data,
                                                                           len);
  return HANDLER_GO_ON;
}

static handler_t OnBroadcastClose(struct server* srv, int fd) {
  transactions_logic::Transactionslogic::GetInstance()->OnBroadcastClose(srv,
                                                                         fd);
  return HANDLER_GO_ON;
}

static handler_t OnBroadcastMessage(struct server* srv, int fd, void *data,
                                    int len) {
  transactions_logic::Transactionslogic::GetInstance()->OnBroadcastMessage(srv,
                                                                           fd,
                                                                           data,
                                                                           len);
  return HANDLER_GO_ON;
}

static handler_t OnIniTimer(struct server* srv) {
  transactions_logic::Transactionslogic::GetInstance()->OnIniTimer(srv);
  return HANDLER_GO_ON;
}

static handler_t OnTimeOut(struct server* srv, char* id, int opcode, int time) {
  transactions_logic::Transactionslogic::GetInstance()->OnTimeout(srv, id,
                                                                  opcode, time);
  return HANDLER_GO_ON;
}

int transactions_plugin_init(struct plugin *pl) {
  pl->init = OnTransactionsStart;
  pl->clean_up = OnTransactionsShutdown;
  pl->connection = OnTransactionsConnect;
  pl->connection_close = OnTransactionsClose;
  pl->connection_close_srv = OnBroadcastClose;
  pl->connection_srv = OnBroadcastConnect;
  pl->handler_init_time = OnIniTimer;
  pl->handler_read = OnTransactionsMessage;
  pl->handler_read_srv = OnBroadcastMessage;
  pl->handler_read_other = OnUnknow;
  pl->time_msg = OnTimeOut;
  pl->data = NULL;
  return 0;
}

