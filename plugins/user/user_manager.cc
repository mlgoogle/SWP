// Copyright (c) 2016 The tourism Authors. All rights reserved.
// user_manager.cc
// Created on: 2016年8月10日.
// Author: Paco.

#include "user/user_manager.h"

#include <stdio.h>

#include "glog/logging.h"

#include "user/user_opcode.h"
#include "user/user_interface.h"

namespace user {
UserManager* UserManager::instance_ = NULL;

UserManager* UserManager::GetInstance() {
  if (instance_ == NULL)
    instance_ = new UserManager();
  return instance_;
}

void UserManager::FreeInstance() {
  if (instance_ == NULL) {
    delete instance_;
    instance_ = NULL;
  }
}

UserManager::UserManager() {

}

UserManager::~UserManager() {

}

int32 UserManager::AssignPacket(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  UserInterface* interface = UserInterface::GetInstance();
  LOG(INFO)<< "AssignPacket opcode" << (int)packet->operate_code();
  switch (packet->operate_code()) {
    case PACKET_HEART_REQ: {
      interface->HeartPacket(socket, packet);
      break;
    }
    case ACCOUNT_INFO_REQ: {
	  interface->AccountInfo(socket, packet);
	  break;
    }
    case ORDER_LIST_REQ: {
	  interface->OrderList(socket, packet);
	  break;
    }
    case ORDER_DETAIL_REQ: {
	  interface->OrderDetail(socket, packet);
	  break;
    }
    case BANKCARD_LIST_REQ: {
	  interface->BankcardList(socket, packet);
	  break;
    }
    case BIND_BANKCARD_REQ: {
	  interface->BindBankcard(socket, packet);
	  break;
    }
    case UNBIND_BANKCARD_REQ: {
	  interface->UnbindBankcard(socket, packet);
	  break;
    }
    case CHANGE_DEFAULT_BANKCARD_REQ: {
	  interface->ChangeDefaultBankcard(socket, packet);
	  break;
    }
    case BANK_ACCOUNT_INFO_REQ: {
      interface->BankAccountInfo(socket, packet);
      break;
    }
    case CREDIT_LIST_REQ: {
	  interface->CreditList(socket, packet);
	  break;
    }
    case CREDIT_DETAIL_REQ: {
	  interface->CreditDetail(socket, packet);
	  break;
    }
    case USER_WITHDRAW_REQ: {
	  interface->UserWithdraw(socket, packet);
	  break;
    }
    case USER_WITHDRAW_LIST_REQ: {
	  interface->UserWithdrawList(socket, packet);
	  break;
    }
		/*case USER_WITHDRAW_DETAIL_REQ: {
	  interface->UserWithdrawDetail(socket, packet);
	  break;
	  }*/
    case OBTAIN_VERIFY_CODE_REQ: {
	  interface->ObtainVerifyCode(socket, packet);
	  break;
    }
		/*case CHANGE_USER_INFO_REQ: {
	  interface->ChangeUserInfo(socket, packet);
	  break;
	  }*/
		/*case DEVICE_TOKEN_REQ: {
      interface->DeviceToken(socket, packet);
      break;
	  }*/
		/*case WX_PLACE_ORDER_REQ: {
      interface->WXPlaceOrder(socket, packet);
      break;
    }
    case WXPAY_CLIENT_REQ: {
      interface->WXPayClientResponse(socket, packet);
      break;
    }
    case WXPAY_SERVER_REQ: {
      interface->WXPayServerResponse(socket, packet);
      break;
    }
    case ALIPAY_SEVER_REQ: {
      interface->AlipayServer(socket, packet);
      break;
    }
    case ALIPAY_CLIENT_REQ: {
      interface->AlipayClient(socket, packet);
      break;
    }
    case CHECK_SMS_CODE_REQ: {
      interface->CheckSMSCode(socket, packet);
      break;
	  }*/
  }
  return err;
}

int32 UserManager::CheckHeartLoss() {
  UserInterface* interface = UserInterface::GetInstance();
  //  interface->CheckHeartLoss();
  return 0;
}

int32 UserManager::InitShareGuideData() {
  UserInterface* interface = UserInterface::GetInstance();
  //interface->InitShareGuide();
  return 0;
}

int32 UserManager::OnSockClose(const int fd) {
  UserInterface* interface = UserInterface::GetInstance();
  //  interface->CloseSocket(fd);
  return 0;
}

int32 UserManager::OrderStatusCheck() {
  UserInterface* interface = UserInterface::GetInstance();
  //interface->NopayOrderStatusCheck();
  return 0;
}

}  // namespace user

