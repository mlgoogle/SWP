//  Copyright (c) 2015-2015 The swp Authors. All rights reserved.
//  Created on: 2016年12月30日 Author: kerry

#ifndef SWP_TRANSACTIONS_TRANSACTIONS_LOGIC_
#define SWP_TRANSACTIONS_TRANSACTIONS_LOGIC_


#include "core/common.h"
#include "basic/basictypes.h"
//#include "net/comm_head.h"
//#include "net/packet_processing.h"


namespace transactions_logic {

class Transactionslogic {
 public:
  Transactionslogic();
  virtual ~Transactionslogic();

 private:
    static Transactionslogic    *instance_;

 public:
    static Transactionslogic *GetInstance();
    static void FreeInstance();

    bool OnTransactionsConnect(struct server *srv, const int socket);

    bool OnTransactionsMessage(struct server *srv, const int socket,
            const void *msg, const int len);

    bool OnTransactionsClose(struct server *srv, const int socket);

    bool OnBroadcastConnect(struct server *srv, const int socket,
            const void *data, const int len);

    bool OnBroadcastMessage(struct server *srv, const int socket,
            const void *msg, const int len);

    bool OnBroadcastClose(struct server *srv, const int socket);

    bool OnIniTimer(struct server *srv);

    bool OnTimeout(struct server *srv, char* id, int opcode, int time);

 private:
    bool Init();
};
}  // namespace transactions_logic

#endif

