// Copyright (c) 2016 The tourism Authors. All rights reserved.
// user_proto.h
// Created on: 2016年8月12日.
// Author: Paco.
#ifndef PLUGINS_USER_USER_PROTO_H_
#define PLUGINS_USER_USER_PROTO_H_

#include "pub/net/proto_buf.h"
namespace user {
class UserInfoRecv : public PacketHead {
 public:
  UserInfoRecv(PacketHead packet);
  int32 Deserialize();

  inline std::string uid_str() { return uid_str_; }
 private:
  std::string uid_str_; // "1,2,3,4"
};
	
class AccountInfoRecv : public PacketHead {
 public:
  AccountInfoRecv(PacketHead packet);
  int32 Deserialize();

  inline int64 uid() { return uid_; }
 private:
  int64 uid_;
};

class OrderListRecv : public PacketHead {
 public:
  OrderListRecv(PacketHead packet);
  int32 Deserialize();

  inline int64 uid() { return uid_; }
  inline std::string flow_type() { return flow_type_; }
  inline int32 start_pos() { return start_pos_; }
  inline int32 count() { return count_; }
  
 private:
  int64 uid_;
  std::string flow_type_;
  int32 start_pos_;
  int32 count_;
};

class OrderDetailRecv : public PacketHead {
 public:
  OrderDetailRecv(PacketHead packet);
  int32 Deserialize();

  inline int64 uid() { return uid_; }
  inline int64 flow_id() { return flow_id_; }
  inline int32 flow_type() { return flow_type_; }
 private:
  int64 uid_;
  int64 flow_id_;
  int32 flow_type_;
};

class BankcardListRecv : public PacketHead {
 public:
  BankcardListRecv(PacketHead packet);
  int32 Deserialize();

  inline int64 uid() { return uid_; }
  
 private:
  int64 uid_;
};

class BindBankcardRecv : public PacketHead {
 public:
  BindBankcardRecv(PacketHead packet);
  int32 Deserialize();

  inline int64 uid() { return uid_; }
  inline int64 bank_id() { return bank_id_; }
  inline std::string branch_bank() { return branch_bank_; }
  inline std::string bankcard_num() { return bankcard_num_; }
  inline std::string bank_username() { return bank_username_; }
  
 private:
  int64 uid_;
  int64 bank_id_;
  std::string branch_bank_;
  std::string bankcard_num_;
  std::string bank_username_;
};

class UnbindBankcardRecv : public PacketHead {
 public:
  UnbindBankcardRecv(PacketHead packet);
  int32 Deserialize();

  inline std::string phone_num() { return phone_num_; }
  inline int64 bankcard_id() { return bankcard_id_; }
  inline std::string verify_code() { return verify_code_; }
  inline int64 timestamp() { return timestamp_; }
  inline std::string verify_token() { return verify_token_; }
  
 private:
  std::string phone_num_;
  int64 bankcard_id_;
  std::string verify_code_;
  int64 timestamp_;
  std::string verify_token_;
};

class ChangeDefaultBankcardRecv : public PacketHead {
 public:
  ChangeDefaultBankcardRecv(PacketHead packet);
  int32 Deserialize();

  inline int64 uid() { return uid_; }
  inline int64 bankcard_id() { return bankcard_id_; }
  
 private:
  int64 uid_;
  int64 bankcard_id_;
};
	
class BankAccountInfoRecv : public PacketHead {
 public:
  BankAccountInfoRecv(PacketHead packet);
  int32 Deserialize();

  inline std::string bankcard_num() { return bankcard_num_; }
	
 private:
  std::string bankcard_num_;
};

class CreditListRecv : public PacketHead {
 public:
  CreditListRecv(PacketHead packet);
  int32 Deserialize();

  inline int64 uid() { return uid_; }
  inline std::string status() { return status_; }
  inline int64 start_pos() { return start_pos_; }
  inline int64 count() { return count_; }
  
 private:
  int64 uid_;
  std::string status_;
  int64 start_pos_;
  int64 count_;
};

class CreditDetailRecv : public PacketHead {
 public:
  CreditDetailRecv(PacketHead packet);
  int32 Deserialize();

  inline int64 uid() { return uid_; }
  inline int64 recharge_id() { return recharge_id_; }
  
 private:
  int64 uid_;
  int64 recharge_id_;
};

class UserWithdrawRecv : public PacketHead {
 public:
  UserWithdrawRecv(PacketHead packet);
  int32 Deserialize();

  inline int64 uid() { return uid_; }
  inline double money() { return money_; }
  inline int64 bankcard_id() { return bankcard_id_; }
  inline std::string passwd() { return passwd_; }
  
 private:
  int64 uid_;
  double money_;
  int64 bankcard_id_;
  std::string passwd_;
};

class UserWithdrawListRecv : public PacketHead {
 public:
  UserWithdrawListRecv(PacketHead packet);
  int32 Deserialize();

  inline int64 uid() { return uid_; }
  inline std::string status() { return status_; }
  inline int64 start_pos() { return start_pos_; }
  inline int64 count() { return count_; }
  
 private:
  int64 uid_;
  std::string status_;
  int64 start_pos_;
  int64 count_;
};
	
class ChangeUserInfoRecv : public PacketHead {
 public:
  ChangeUserInfoRecv(PacketHead packet);
  int32 Deserialize();

  inline int64 uid() { return uid_; }
  inline std::string nickname() { return nickname_; }
  inline int64 gender() { return gender_; }
  inline std::string head_url() { return head_url_; }

 private:
  int64 uid_;
  std::string nickname_;
  int64 gender_;
  std::string head_url_;
};

class WxPlaceOrderRecv : public PacketHead {
 public:
  WxPlaceOrderRecv(PacketHead packet);
  int32 Deserialize();
  inline int64 uid() { return uid_; }
  inline double price() { return price_; }
  inline std::string title() { return title_; }
 private:
  int64 uid_;
  std::string title_; //应用名-商品名 eg.V领队-高级服务
  double price_; // 订单总价  单位 分
};

class WXPayClientRecv : public PacketHead {
 public:
  WXPayClientRecv(PacketHead packet);
  int32 Deserialize();
  inline int64 uid() { return uid_; }
  inline int64 recharge_id() { return recharge_id_; }
  inline int64 pay_result() { return pay_result_; }
 private:
  int64 uid_;
  int64 recharge_id_;
  int64 pay_result_; //1-成功 2-取消
};

class WXPayServerRecv : public PacketHead {
 public:
  WXPayServerRecv(PacketHead packet);
  int32 Deserialize();
  inline int64 total_fee() { return total_fee_; }
  inline int64 recharge_id() { return recharge_id_; }
  inline int64 pay_result() { return pay_result_; }
  inline std::string appid() { return appid_; }
  inline std::string mch_id() { return mch_id_; }
 private:
  std::string appid_;
  std::string mch_id_;
  std::string xml_str_;
  int64 recharge_id_;
  int64 pay_result_; //1 - 支付成功
  int64 total_fee_;
  std::string transaction_id_;
  std::string time_end_;
};

class SMSCodeLoginRecv : public PacketHead {
 public:
  SMSCodeLoginRecv(PacketHead packet);
  int32 Deserialize();
  inline int64 timestamp() { return timestamp_; }
  inline int64 verify_code() { return verify_code_; }
  inline std::string phone_num() { return phone_num_; }
  inline std::string token() { return token_; }
  inline int64 user_type() { return user_type_; }
 private:
  int64 timestamp_;
  int64 verify_code_;
  int64 user_type_;
  std::string phone_num_;
  std::string token_;
};

class Heartbeat:public PacketHead {
 public:
  Heartbeat(PacketHead packet);
  int32 Deserialize();

  inline int64 uid() { return uid_; }
 private:
  int64 uid_;
};

class ObtainVerifyCodeRecv : public PacketHead {
 public:
  ObtainVerifyCodeRecv(PacketHead packet);
  int32 Deserialize();
  inline int64 verify_type() { return verify_type_; }
  inline std::string phone_num() { return phone_num_; }
 private:
  int64 verify_type_;
  std::string phone_num_;
};

class DeviceTokenRecv : public PacketHead {
 public:
  DeviceTokenRecv(PacketHead packet);
  int32 Deserialize();

  inline int64 uid() { return uid_; }
  inline std::string device_token() { return device_token_; }
 private:
  int64 uid_;
  std::string device_token_;
};

class UserCashRecv : public PacketHead {
 public:
  UserCashRecv(PacketHead packet);
  int32 Deserialize();

  inline int64 uid() { return uid_; }
 private:
  int64 uid_;
};
//send


class CheckSMSCodeRecv : public PacketHead {
 public:
  CheckSMSCodeRecv (PacketHead packet);
  int32 Deserialize();

  inline int64 verify_code() { return verify_code_; }
  inline int64 verify_type() { return verify_type_; }
  inline int64 timestamp() { return timestamp_; }
  inline std::string phone_num() { return phone_num_; }
  inline std::string token() { return token_; }
 private:
  int64 verify_code_;
  int64 verify_type_; //0-注册 1-登录 2-更新服务
  int64 timestamp_; //时间戳
  std::string phone_num_;
  std::string token_;
};

struct PhotoUrl {
  std::string photo_url_;
  std::string thumbnail_url_;
};

}  // namespace user

#endif  // PLUGINS_USER_USER_PROTO_H_
