// Copyright (c) 2016 The tourism Authors. All rights reserved.
// user_mysql.h
// Created on: 2016年8月16日.
// Author: Paco.
#ifndef PLUGINS_USER_USER_MYSQL_H_
#define PLUGINS_USER_USER_MYSQL_H_

#include "public/config/config.h"
#include "public/basic/basictypes.h"

#include "pub/storage/data_engine.h"

#include "pub/net/typedef.h"

namespace user {
	
enum FlowType {
  DEPOSIT = 1, //入金
  WITHDRAW, //出金
  OPEN_POSITION, //建仓
  CLOSE_POSITION //平仓
};
 
class UserMysql {
 public:
  UserMysql(config::FileConfig* config);
  ~UserMysql();

 public:
  int32 AccountInfoSelect(int64 uid, DicValue* dic);
  int32 OrderListSelect(int64 uid, std::string flow_type, int32 start_pos,
										int32 count, DicValue* dic);
  int32 OrderDetailSelect(int64 uid, int64 flow_id, int32 flow_type,
										DicValue* dic);
  int32 BankcardListSelect(int64 uid, DicValue* dic);
  int32 BindBankcardInsertAndSelect(int64 uid, int64 bank_id, std::string branch_bank,
					std::string card_no, std::string bank_username, DicValue* dic);
  int32 UnbindBankcardDelete(int64 uid, int32 bank_id);
  int32 ChangeDefaultBankcard(int64 uid, int32 bank_id);
  int32 BankAccountInfoSelect(std::string account, DicValue* dic);
  int32 CreditListSelect(int64 uid, int32 status, int32 start_pos, int32 count, DicValue* dic);
  int32 CreditDetailSelect(int64 uid, int64 recharge_id, DicValue* dic);
  int32 UserWithdrawInsertAndSelect(int64 uid, double money,
						int64 bankcard_id, std::string passwd, DicValue* dic);
  int32 UserWithdrawListSelect(int64 uid, int32 status,
								int32 startPos, int32 count, DicValue* dic);
  //  int32 UserWithdrawDetailSelect(int64 uid, int64 withdraw_id, DicValue* dic);
  int32 DeviceTokenUpdate(int64 uid, std::string dt);

  static void CallAccountInfoSelect(void* param, Value* value);
  static void CallOrderListSelect(void* param, Value* value);
  static void CallOrderDetailSelect(void* param, Value* value);
  // static void CallBankCardListSelect(void* param, Value* value);
  static void CallBindBankcardInsertAndSelect(void* param, Value* value);
  static void CallBankAccountInfoSelect(void* param, Value* value);
  static void CallCreditListSelect(void* param, Value* value);
  static void CallCreditDetailSelect(void* param, Value* value);
  static void CallBankcardListSelect(void* param, Value* value);
  static void CallUserWithdrawInsertAndSelect(void* param, Value* value);
  static void CallUserWithdrawListSelect(void* param, Value* value);
  
 private:
  base_logic::DataEngine* mysql_engine_;
};

}  // namespace user

#endif  // PLUGINS_USER_USER_MYSQL_H_
