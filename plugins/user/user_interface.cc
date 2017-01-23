// Copyright (c) 2016 The tourism Authors. All rights reserved.
// user_interface.cc
// Created on: 2016年8月10日.
// Author: Paco.
#include "user/user_interface.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <sys/socket.h>

#include "public/basic/md5sum.h"
#include "glog/logging.h"

#include "user/user_proto.h"
#include "user/user_opcode.h"
#include "pub/util/util.h"
#include "pub/pay/wxpay/wx_order.h"

#define SHELL_SMS "./verify_code_sms.sh"
#define SMS_KEY "yd1742653sd"
namespace user {
UserInterface* UserInterface::instance_;

UserInterface* UserInterface::GetInstance() {
  if (instance_ == NULL)
    instance_ = new UserInterface();
  return instance_;
}

void UserInterface::FreeInstance() {
  if (instance_ == NULL) {
    delete instance_;
    instance_ = NULL;
  }
}

UserInterface::UserInterface() {
  user_mysql_ = NULL;
  data_share_mgr_ = NULL;
}

UserInterface::~UserInterface() {

}

void UserInterface::InitConfig(config::FileConfig* config) {
  user_mysql_ = new UserMysql(config);
//  data_share_mgr_ = share::DataShareMgr::GetInstance();
}

void UserInterface::InitShareDataMgr(share::DataShareMgr* data) {
  data_share_mgr_ = data;
}

int32 UserInterface::CheckHeartLoss() {
  int32 err = 0;
  do {
    data_share_mgr_->CheckHeartLoss();
  } while (0);

  return err;
}
	
int32 UserInterface::UserInfo(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
    UserInfoRecv rev(*packet);
    err = rev.Deserialize();
    if (err < 0)
    	break;
    DicValue dict;
    //    UserInfo* u = data_share_mgr_->GetUser(rev.uid());
    //    if (u != NULL) {
    //      dict.SetBigInteger(L"uid_", u->uid());
    //      dict.SetString(L"phone_num_", u->phone_num());
    //      dict.SetString(L"nickname_", u->nickname());
    //      dict.SetBigInteger(L"credit_lv_", u->credit_lv());
    //      dict.SetBigInteger(L"praise_lv_", u->praise_lv());
    //      dict.SetBigInteger(L"cash_lv_", u->cash_lv());
    //      dict.SetString(L"head_url_", u->head_url());
    //      dict.SetString(L"address_", u->usual_addr());
    //      dict.SetReal(L"longitude_", u->usual_lon());
    //      dict.SetReal(L"latitude_", u->usual_lat());
    //      SendMsg(socket, packet, &dict, USER_INFO_RLY);
    //      break;
    //    }
    err = user_mysql_->UserInfoSelect(rev.uid_str(), &dict);
    if (err < 0)
    	break;
    SendMsg(socket, packet, &dict, USER_INFO_RLY);
  } while (0);
  if (err < 0) {
    SendError(socket, packet, err, USER_INFO_RLY);
  }
  return err;
}

int32 UserInterface::AccountInfo(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
    AccountInfoRecv recv(*packet);
    err = recv.Deserialize();
    if (err < 0)
      break;
    DicValue dic;
    err = user_mysql_->AccountInfoSelect(recv.uid(), &dic);
    if (err < 0)
      break;
    SendMsg(socket, packet, &dic, ACCOUNT_INFO_RLY);
  } while (0);
  if (err < 0)
    SendError(socket, packet, err, ACCOUNT_INFO_RLY);
  return err;
}

int32 UserInterface::OrderList(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
    OrderListRecv recv(*packet);
    err = recv.Deserialize();
    if (err < 0)
      break;
    DicValue dic;
    err = user_mysql_->OrderListSelect(recv.uid(), recv.flow_type(),
							recv.start_pos(), recv.count(), &dic);
    if (err < 0)
      break;
    SendMsg(socket, packet, &dic, ORDER_LIST_RLY);
  } while (0);
  if (err < 0)
    SendError(socket, packet, err, ORDER_LIST_RLY);
  return err;
}

int32 UserInterface::OrderDetail(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
    OrderDetailRecv recv(*packet);
    err = recv.Deserialize();
    if (err < 0)
      break;
    DicValue dic;
    err = user_mysql_->OrderDetailSelect(recv.uid(),
						recv.flow_id(), recv.flow_type(), &dic);
    if (err < 0)
      break;
    SendMsg(socket, packet, &dic, ORDER_DETAIL_RLY);
  } while (0);
  if (err < 0)
    SendError(socket, packet, err, ORDER_DETAIL_RLY);
  return err;
}

int32 UserInterface::BankcardList(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
    BankcardListRecv recv(*packet);
    err = recv.Deserialize();
    if (err < 0)
      break;
    DicValue dic;
    err = user_mysql_->BankcardListSelect(recv.uid(), &dic);
    if (err < 0)
      break;
    SendMsg(socket, packet, &dic, BANKCARD_LIST_RLY);
  } while (0);
  if (err < 0)
    SendError(socket, packet, err, BANKCARD_LIST_RLY);
  return err;
}

int32 UserInterface::BindBankcard(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
    BindBankcardRecv recv(*packet);
    err = recv.Deserialize();
    if (err < 0)
      break;
	DicValue dic;
    err = user_mysql_->BindBankcardInsertAndSelect(recv.uid(), recv.bank_id(),
										  recv.branch_bank(),
										  recv.bankcard_num(), recv.bank_username(), &dic);
    if (err < 0)
      break;
    SendMsg(socket, packet, &dic, BIND_BANKCARD_RLY);
  } while (0);
  if (err < 0)
    SendError(socket, packet, err, BIND_BANKCARD_RLY);
  return err;
}

int32 UserInterface::UnbindBankcard(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
    UnbindBankcardRecv recv(*packet);
    err = recv.Deserialize();
    if (err < 0)
      break;
    if (time(NULL) - recv.timestamp() > 15 * 60) {
      err = VERIFY_CODE_OVERDUE;
      break;
    }
    std::stringstream ss;
    ss << SMS_KEY << recv.timestamp() << recv.verify_code() << recv.phone_num();
	base::MD5Sum md5(ss.str());
    if (md5.GetHash() != recv.verify_token()) {
      err = VERIFY_CODE_ERR;
      break;
	}
    err = user_mysql_->UnbindBankcardDelete(recv.phone_num(), recv.bankcard_id());
    if (err < 0)
      break;
    SendMsg(socket, packet, NULL, UNBIND_BANKCARD_RLY);
  } while (0);
  if (err < 0)
    SendError(socket, packet, err, UNBIND_BANKCARD_RLY);
  return err;
}
	
int32 UserInterface::ChangeDefaultBankcard(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
    ChangeDefaultBankcardRecv recv(*packet);
    err = recv.Deserialize();
    if (err < 0)
      break;
    err = user_mysql_->ChangeDefaultBankcard(recv.uid(), recv.bankcard_id());
    if (err < 0)
      break;
    SendMsg(socket, packet, NULL, CHANGE_DEFAULT_BANKCARD_RLY);
  } while (0);
  if (err < 0)
    SendError(socket, packet, err, CHANGE_DEFAULT_BANKCARD_RLY);
  return err;
}
	
int32 UserInterface::BankAccountInfo(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
  	BankAccountInfoRecv recv(*packet);
  	err = recv.Deserialize();
  	if (err < 0)
  		break;
  	DicValue dic;
  	err = user_mysql_->BankAccountInfoSelect(recv.bankcard_num(), &dic);
  	if (err < 0)
  		break;
  	SendMsg(socket, packet, &dic, BANK_ACCOUNT_INFO_RLY);
  } while (0);
  if (err < 0)
  	SendError(socket, packet, err, BANK_ACCOUNT_INFO_RLY);
  return err;
}
	
int UserInterface::split_string(const std::string &in, const char ch, std::vector<std::string> &out) { //last is ,??????????
  if (in.size() == 0)
    return 0;
  out.clear();

  size_t old_pos = 0, new_pos = 0;
  std::string tmp;
  while (true) {
    new_pos = in.find(ch, old_pos);
    if (new_pos != std::string::npos) {
      tmp = in.substr(old_pos, new_pos - old_pos);
      if (tmp != "")
      	out.push_back(tmp);
      old_pos = ++new_pos;
    } else if (old_pos <= in.size()) {
      tmp = in.substr(old_pos);
      if (tmp != "")
      	out.push_back(tmp);
      break;
    } else
      break;
  }

  return 0;
}

int32 UserInterface::CreditList(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
    CreditListRecv recv(*packet);
    err = recv.Deserialize();
    if (err < 0)
      break;
	
	std::string db_status;
	std::vector<std::string> split_status;
	split_string(recv.status(), ',', split_status);
	for (std::vector<std::string>::iterator it = split_status.begin();
		 it != split_status.end(); ++it) {
		if (*it == CREDIT_INPROCESS) {
		  db_status += DB_CREDIT_INPROCESS_STR;
		  db_status += DB_CREDIT_CLIENT_SUCCESS_STR;
		} else if (*it == CREDIT_SUCCESS)
		  db_status += DB_CREDIT_SERVER_SUCCESS_STR;
		else if (*it == CREDIT_FAIL) {
		  db_status += DB_CREDIT_CLIENT_FAIL_STR;
		  db_status += DB_CREDIT_SERVER_FAIL_STR;
		} else {
		  err = CREDIT_STATUS_ERR;
		  break;
		}
	}
    if (err < 0)
      break;

    DicValue dic;
    err = user_mysql_->CreditListSelect(recv.uid(), db_status.substr(0, db_status.size() - 1),
									recv.start_pos(), recv.count(), &dic);
    if (err < 0)
      break;
    SendMsg(socket, packet, &dic, CREDIT_LIST_RLY);
  } while (0);
  if (err < 0)
    SendError(socket, packet, err, CREDIT_LIST_RLY);
  return err;
}
	
int32 UserInterface::CreditDetail(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
    CreditDetailRecv recv(*packet);
    err = recv.Deserialize();
    if (err < 0)
      break;
    DicValue dic;
    err = user_mysql_->CreditDetailSelect(recv.uid(), recv.recharge_id(), &dic);
    if (err < 0)
      break;
    SendMsg(socket, packet, &dic, CREDIT_DETAIL_RLY);
  } while (0);
  if (err < 0)
    SendError(socket, packet, err, CREDIT_DETAIL_RLY);
  return err;
}
	
int32 UserInterface::UserWithdraw(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
    UserWithdrawRecv recv(*packet);
    err = recv.Deserialize();
    if (err < 0)
      break;
    DicValue dic;
    err = user_mysql_->UserWithdrawInsertAndSelect(recv.uid(), recv.money(),
									recv.bankcard_id(), recv.passwd(), &dic);
    if (err < 0)
      break;
    SendMsg(socket, packet, &dic, USER_WITHDRAW_RLY);
  } while (0);
  if (err < 0)
    SendError(socket, packet, err, USER_WITHDRAW_RLY);
  return err;
}

int32 UserInterface::UserWithdrawList(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
    UserWithdrawListRecv recv(*packet);
    err = recv.Deserialize();
    if (err < 0)
      break;
    DicValue dic;
    err = user_mysql_->UserWithdrawListSelect(recv.uid(), recv.status(),
											  recv.start_pos(), recv.count(), &dic);
    if (err < 0)
      break;
    SendMsg(socket, packet, &dic, USER_WITHDRAW_LIST_RLY);
  } while (0);
  if (err < 0)
    SendError(socket, packet, err, USER_WITHDRAW_LIST_RLY);
  return err;
}

	/*int32 UserInterface::UserWithdrawDetail(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
    UserWithdrawDetailRecv recv(*packet);
    err = recv.Deserialize();
    if (err < 0)
      break;
    DicValue dic;
    err = user_mysql_->UserWithdrawDetailSelect(recv.uid(), recv.withdraw_id(), &dic);
    if (err < 0)
      break;
    SendMsg(socket, packet, &dic, USER_WITHDRAW_DETAIL_RLY);
  } while (0);
  if (err < 0)
    SendError(socket, packet, err, USER_WITHDRAW_DETAIL_RLY);
  return err;
  }*/

int32 UserInterface::ObtainVerifyCode(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
  	ObtainVerifyCodeRecv rev(*packet);
  	err = rev.Deserialize();
  	if (err < 0)
  		break;
  	std::stringstream ss;
  	int64 timestamp_ = time(NULL);
  	int64 rand_code_ = util::Random(100000, 999999);

  	DicValue dic;
  	dic.SetBigInteger(L"timestamp", timestamp_);

  	ss << SMS_KEY << timestamp_ << rand_code_ << rev.phone_num();
  	base::MD5Sum md5(ss.str());
  	dic.SetString(L"vToken", md5.GetHash().c_str());
  	LOG(INFO) << "token:" << ss.str();
  	LOG(INFO) << "md5 token:" << md5.GetHash();
  	ss.str("");
  	ss.clear();
  	ss << rev.phone_num() << ":" << rev.verify_type();
  	data_share_mgr_->UpdateSMSToken(ss.str(), md5.GetHash());
  	SendMsg(socket, packet, &dic, OBTAIN_VERIFY_CODE_RLY);

  	ss.str("");
  	ss.clear();
  	ss << SHELL_SMS << " " << rev.phone_num() << " " << rand_code_ << " "
  	   << rev.verify_type();
  	LOG(INFO) << ss.str();
  	system(ss.str().c_str());
  } while (0);
  if (err < 0) {
  	SendError(socket, packet, err, OBTAIN_VERIFY_CODE_RLY);
  }
  return err;
}
	
int32 UserInterface::ChangeUserInfo(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
    ChangeUserInfoRecv rev(*packet);
    err = rev.Deserialize();
    if (err < 0)
      break;
    err = user_mysql_->ChangeUserInfoUpdate(rev.uid(), rev.nickname(),
											rev.head_url(), rev.gender());
    if (err < 0)
      break;
    SendMsg(socket, packet, NULL, CHANGE_USER_INFO_RLY);
  } while (0);
  if (err < 0) {
    SendError(socket, packet, err, CHANGE_USER_INFO_RLY);
  }
  return err;
}
	
int32 UserInterface::WXPlaceOrder(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
    WxPlaceOrderRecv recv(*packet);
    err = recv.Deserialize();
    //记录订单信息
    DicValue recharge_dic;
    err = user_mysql_->RechargeInfoInsertAndSelect(recv.uid(), recv.price(),
                                                   &recharge_dic);
    if (err < 0)
      break;
    std::string recharge_id;
    recharge_dic.GetString(L"rid", &recharge_id);
    std::string ip;
    int port;
    //访问微信下单接口
    WXOrder wx_order;
    if (util::GetIPAddress(socket, &ip, &port))
      wx_order.set_spbill_create_ip(ip);
    wx_order.set_body(recv.title());
    wx_order.set_out_trade_no(recharge_id);
    wx_order.set_total_fee(recv.price() * 100);
    std::string wx_result = wx_order.PlaceOrder();
    base_logic::ValueSerializer* deserializer =
        base_logic::ValueSerializer::Create(base_logic::IMPL_XML, &wx_result);
    std::string err_str;
    int32 err = 0;
    DicValue* dic = (DicValue*) deserializer->Deserialize(&err, &err_str);
    do {
      if (dic != NULL) {
        std::string return_code;
        dic->GetString(L"return_code", &return_code);
        LOG(INFO) << "return_code:" << return_code;
        //下单成功
        if (return_code.find("SUCCESS") != std::string::npos) {
          std::string result_code;
          dic->GetString(L"result_code", &result_code);
          LOG(INFO) << "result_code:" << result_code;
          //业务逻辑成功
          if (result_code.find("SUCCESS") != std::string::npos) {
            std::string prepay_id;
            dic->GetString(L"prepay_id", &prepay_id);
            LOG(INFO) << "prepay_id:" << prepay_id;
            int npos1 = prepay_id.find("<![CDATA[");
            int npos2 = prepay_id.find("]]>");
            prepay_id = prepay_id.substr(npos1 + 9, npos2 - npos1 - 9);
            wx_order.set_prepayid(prepay_id);
            wx_order.PreSign();
            wx_order.PreSerialize(&recharge_dic);
            SendMsg(socket, packet, &recharge_dic, WX_PLACE_ORDER_RLY);
            // todo 下单成功 ，记录微信订单信息

          } else {
            err = WX_PLACE_ORDER_ERR;
            break;
          }
        } else {
          err = WX_PLACE_ORDER_ERR;
          break;
        }
      }
    } while (0);
    base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_XML,
                                                  deserializer);

  } while (0);
  if (err < 0) {
    SendError(socket, packet, err, WX_PLACE_ORDER_RLY);
  }
  return err;
}

int32 UserInterface::WXPayClientResponse(const int32 socket,
                                         PacketHead* packet) {
  int32 err = 0;
  do {
    WXPayClientRecv recv(*packet);
    err = recv.Deserialize();
    if (err < 0)
      break;
    DicValue dic;
    err = user_mysql_->ChangeRechargeStatusAndSelect(recv.recharge_id(),
                                                     recv.pay_result(), &dic);
    if (err < 0)
      break;
    SendMsg(socket, packet, &dic, WXPAY_CLIENT_RLY);
    if (recv.pay_result() == 1) {
      user_mysql_->ChangeRechargeStatusAndSelect(recv.recharge_id(), 1, &dic);
    } else {
      user_mysql_->ChangeRechargeStatusAndSelect(recv.recharge_id(), 2, &dic);
    }
    SendMsg(socket, packet, &dic, WXPAY_SERVER_RLY);
  } while (0);
  if (err < 0) {
    SendError(socket, packet, err, WXPAY_CLIENT_RLY);
  }
  return err;
}

int32 UserInterface::WXPayServerResponse(const int32 socket,
                                         PacketHead* packet) {
  int32 err = 0;
  do {
	LOG(ERROR) << "aaaaaaaa wx pay server";
    WXPayServerRecv recv(*packet);
    err = recv.Deserialize();
    if (err < 0)
		break;
    //支付成功
    DicValue dic;
    if (recv.appid() != APPID && recv.mch_id() != MCH_ID) {
      LOG(ERROR) << "WXPAY SERVER RESULT appid:[" << recv.appid() << "]";
      LOG(ERROR) << "WXPAY SERVER RESULT mch_id:[" << recv.mch_id() << "]";
      break;
    }
    if (recv.pay_result() == 1) {
      user_mysql_->ChangeRechargeStatusAndSelect(recv.recharge_id(), 3, &dic);
    } else {
      user_mysql_->ChangeRechargeStatusAndSelect(recv.recharge_id(), 4, &dic);
    }
    int64 user_id = 0;
    /*dic.GetBigInteger(L"uid_", &user_id);
	UserInfo* user = data_share_mgr_->GetUser(user_id);
    if (user != NULL && user->is_login()) {
      SendMsg(user->socket_fd(), packet, &dic, WXPAY_SERVER_RLY);
	  }*/
  } while (0);
  return err;
}

int32 UserInterface::CloseSocket(const int fd) {
  data_share_mgr_->UserOffline(fd);
  return 0;
}

int32 UserInterface::HeartPacket(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  Heartbeat rev(*packet);
  do {
    err = rev.Deserialize();
    if (err < 0)
      break;
    data_share_mgr_->UserHeart(rev.uid());
  } while (0);
  return err;
}

int32 UserInterface::AlipayServer(const int32 socket, PacketHead* packet) {
  LOG(INFO) << "alipay server req";
  return 0;
}

int32 UserInterface::AlipayClient(const int32 socket, PacketHead* packet) {
  LOG(INFO) << "alipay client req";
  return 0;
}


	/*int32 UserInterface::DeviceToken(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  LOG(INFO) << "DeviceToken";
  do {
    DeviceTokenRecv rev(*packet);
    err = rev.Deserialize();
    LOG(INFO) << "DeviceToken Deserialize err:" << err;
    if (err < 0)
      break;
    int result = data_share_mgr_->AddDeviceToken(rev.uid(), rev.device_token());
    LOG(INFO) << "AddDeviceToken result:" << result;
    if (result >= 0)
      err = user_mysql_->DeviceTokenUpdate(rev.uid(), rev.device_token());
    if (err < 0)
      break;
    SendMsg(socket, packet, NULL, DEVICE_TOKEN_RLY);
  } while (0);
  if (err < 0) {
    LOG(INFO) << "DeviceToken SendError err:" << err;
    SendError(socket, packet, err, DEVICE_TOKEN_RLY);
  }
  return err;
  }*/

	/*int32 UserInterface::CheckSMSCode(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
    CheckSMSCodeRecv rev(*packet);
    err = rev.Deserialize();
    if (err < 0)
      break;
    if (time(NULL) - rev.timestamp() > 15 * 60) {
      err = VERIFY_CODE_OVERDUE;
      break;
    }
    std::stringstream ss;
    ss << SMS_KEY << rev.timestamp() << rev.verify_code() << rev.phone_num();
    base::MD5Sum md5(ss.str());
    if (md5.GetHash() != rev.token()) {
      err = VERIFY_CODE_ERR;
      break;
    }
    ss.str("");
    ss.clear();
    ss << rev.phone_num() << ":" << rev.verify_type();
    if (!data_share_mgr_->CheckSMSToken(ss.str(), rev.token())) {
      err = VERIFY_CODE_NOT_NEW;
      break;
    }
    SendMsg(socket, packet, NULL, CHECK_SMS_CODE_RLY);
  } while (0);
  if (err < 0)
    SendError(socket, packet, err, CHECK_SMS_CODE_RLY);
  return err;
  }*/

void UserInterface::SendPacket(const int socket, PacketHead* packet) {

  char* s = new char[packet->packet_length()];
  LOG(INFO) << "packet body:" << packet->body_str();
  memset(s, 0, packet->packet_length());
  memcpy(s, &packet->head(), HEAD_LENGTH);
  memcpy(s + HEAD_LENGTH, packet->body_str().c_str(),
         packet->body_str().length());
  int total = util::SendFull(socket, s, packet->packet_length());
  delete[] s;
  s = NULL;
  LOG_IF(ERROR, total != packet->packet_length())
      << "send packet wrong:opcode[" << packet->operate_code() << "]"
	  << total << "," << packet->packet_length();
}

void UserInterface::SendError(const int socket, PacketHead* packet, int32 err,
                              int16 opcode) {
  PacketErr p_err;
  p_err.set_head(packet->head());
  p_err.set_type(ERROR_TYPE);
  p_err.set_error(err);
  p_err.Serialize();
  p_err.AdapterLen();
  p_err.set_operate_code(opcode);
  SendPacket(socket, &p_err);
}

void UserInterface::SendMsg(const int socket, PacketHead* packet, DicValue* dic,
                            int16 opcode) {
  PacketHead send;
  send.set_head(packet->head());
  send.Serialize(dic);
  send.AdapterLen();
  send.set_operate_code(opcode);
  SendPacket(socket, &send);
}

}  // namespace user

