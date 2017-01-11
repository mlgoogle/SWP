// Copyright (c) 2016 The tourism Authors. All rights reserved.
// user_interface.h
// Created on: 2016年8月10日.
// Author: Paco.
#ifndef PLUGINS_USER_USER_INTERFACE_H_
#define PLUGINS_USER_USER_INTERFACE_H_

#include "public/basic/basictypes.h"
#include "public/config/config.h"
#include "pub/net/proto_buf.h"
#include "pub/share/data_share_mgr.h"

#include "user/user_mysql.h"
namespace user {

class UserInterface {
 private:
  UserInterface();
  ~UserInterface();

 public:
  static UserInterface* GetInstance();
  static void FreeInstance();
  void test();
 public:
  void InitConfig(config::FileConfig* config);

  int32 HeartPacket(const int32 socket, PacketHead* packet);

  int32 AccountInfo(const int32 socket, PacketHead* packet);

  int32 OrderList(const int32 socket, PacketHead* packet);

  int32 OrderDetail(const int32 socket, PacketHead* packet);

  int32 BankcardList(const int32 socket, PacketHead* packet);

  int32 BindBankcard(const int32 socket, PacketHead* packet);

  int32 UnbindBankcard(const int32 socket, PacketHead* packet);

  int32 ChangeDefaultBankcard(const int32 socket, PacketHead* packet);
  
  int32 BankAccountInfo(const int32 socket, PacketHead* packet);

  int32 CreditList(const int32 socket, PacketHead* packet);

  int32 CreditDetail(const int32 socket, PacketHead* packet);

  int32 UserWithdraw(const int32 socket, PacketHead* packet);

  int32 UserWithdrawList(const int32 socket, PacketHead* packet);

  int32 UserWithdrawDetail(const int32 socket, PacketHead* packet);

  int32 ObtainVerifyCode(const int32 socket, PacketHead* packet);

  int32 ChangeUserInfo(const int32 socket, PacketHead* packet);

  int32 DeviceToken(const int32 socket, PacketHead* packet);

  int32 WXPlaceOrder(const int32 socket, PacketHead* packet);

  int32 WXPayClientResponse(const int32 socket, PacketHead* packet);

  int32 WXPayServerResponse(const int32 socket, PacketHead* packet);

  int32 AlipayServer(const int32 socket, PacketHead* packet);

  int32 AlipayClient(const int32 socket, PacketHead* packet);
  
  int32 CheckSMSCode(const int32 socket, PacketHead* packet);

  int32 CheckHeartLoss();
//更新共享数据，旅游分享和技能分享
  int32 InitShareGuide();
  //定时监测订单状态
  int32 NopayOrderStatusCheck();
  int32 CloseSocket(const int fd);

  void SendPacket(const int socket, PacketHead* packet);

  void SendError(const int socket, PacketHead* packet, int32 err, int16 opcode);

  void SendMsg(const int socket, PacketHead* packet, DicValue* dic,
               int16 opcode);

  void InitShareDataMgr(share::DataShareMgr* data);
 private:
  int32 InitShareType();
  int32 InitShareDetails();
  int32 InitShareSkills();

  static UserInterface* instance_;
  UserMysql* user_mysql_;
  share::DataShareMgr* data_share_mgr_;
};

}  // namespace user



#endif  // PLUGINS_USER_USER_INTERFACE_H_
