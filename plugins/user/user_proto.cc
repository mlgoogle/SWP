// Copyright (c) 2016 The tourism Authors. All rights reserved.
// user_proto.cc
// Created on: 2016年8月12日.
// Author: Paco.

#include "user/user_proto.h"

#include <typeinfo>

#include "glog/logging.h"
#include "base/logic/base_values.h"
#include "public/basic/md5sum.h"

#include "pub/comm/comm_head.h"
#include "pub/util/util.h"

namespace user {
UserInfoRecv::UserInfoRecv(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
}

int32 UserInfoRecv::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      					      base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
    if (dic != NULL) {
      r = dic->GetString(L"uidStr", &uid_str_);
      LOG_IF(ERROR, !r) << "UserInfoRecv::uid_str_ parse error";
    } else {
      LOG(ERROR)<< "UserInfoRecv Deserialize error";
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
      									  serializer);
  return err;
}

AccountInfoRecv::AccountInfoRecv(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
  uid_ = 0;
}

int32 AccountInfoRecv::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
    if (dic != NULL) {
      r = dic->GetBigInteger(L"uid", &uid_);
      LOG_IF(ERROR, !r) << "AccountInfoRecv::uid_ parse error";
    } else {
      LOG(ERROR)<< "AccountInfoRecv Deserialize error";
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
                                                serializer);
  return err;
}
	
OrderListRecv::OrderListRecv(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
  uid_ = 0;
}

int32 OrderListRecv::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
    if (dic != NULL) {
      r = dic->GetBigInteger(L"uid", &uid_);
      LOG_IF(ERROR, !r) << "OrderListRecv::uid_ parse error";
      r = dic->GetString(L"flowType", &flow_type_);
      LOG_IF(ERROR, !r) << "OrderDetailRecv::flow_type_ parse error";
      r = dic->GetInteger(L"startPos", &start_pos_);
      LOG_IF(ERROR, !r) << "OrderDetailRecv::start_pos_ parse error";
      r = dic->GetInteger(L"count", &count_);
      LOG_IF(ERROR, !r) << "OrderDetailRecv::count_ parse error";
    } else {
      LOG(ERROR)<< "OrderDetailRecv Deserialize error";
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
                                                serializer);
  return err;
}
	
OrderDetailRecv::OrderDetailRecv(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
  uid_ = 0;
  flow_id_ = 0;
}

int32 OrderDetailRecv::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
    if (dic != NULL) {
      r = dic->GetBigInteger(L"uid", &uid_);
      LOG_IF(ERROR, !r) << "OrderDetailRecv::uid_ parse error";
      r = dic->GetBigInteger(L"flowId", &flow_id_);
      LOG_IF(ERROR, !r) << "OrderDetailRecv::flow_id_ parse error";
      r = dic->GetInteger(L"flowType", &flow_type_);
      LOG_IF(ERROR, !r) << "OrderDetailRecv::flow_type_ parse error";
    } else {
      LOG(ERROR)<< "OrderDetailRecv Deserialize error";
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
                                                serializer);
  return err;
}
	
BankcardListRecv::BankcardListRecv(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
  uid_ = 0;
}

int32 BankcardListRecv::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
    if (dic != NULL) {
      r = dic->GetBigInteger(L"uid", &uid_);
      LOG_IF(ERROR, !r) << "BankcardListRecv::uid_ parse error";
    } else {
      LOG(ERROR)<< "BankcardListRecv Deserialize error";
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
                                                serializer);
  return err;
}
	
BindBankcardRecv::BindBankcardRecv(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
  uid_ = 0;
}

int32 BindBankcardRecv::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
    if (dic != NULL) {
      r = dic->GetBigInteger(L"uid", &uid_);
      LOG_IF(ERROR, !r) << "BindBankcardRecv::uid_ parse error";
      r = dic->GetBigInteger(L"bankId", &bank_id_);
      LOG_IF(ERROR, !r) << "BindBankcardRecv::bank_id_ parse error";
      r = dic->GetString(L"branchBank", &branch_bank_);
      LOG_IF(ERROR, !r) << "BindBankcardRecv::branch_bank_ parse error";
      r = dic->GetString(L"cardNo", &bankcard_num_);
      LOG_IF(ERROR, !r) << "BindBankcardRecv::bankcard_num_ parse error";
      r = dic->GetString(L"name", &bank_username_);
      LOG_IF(ERROR, !r) << "BindBankcardRecv::bank_username_ parse error";
    } else {
      LOG(ERROR)<< "BindBankcardRecv Deserialize error";
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
                                                serializer);
  return err;
}
	
UnbindBankcardRecv::UnbindBankcardRecv(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
}

int32 UnbindBankcardRecv::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
    if (dic != NULL) {
      r = dic->GetString(L"phone", &phone_num_);
      LOG_IF(ERROR, !r) << "UnbindBankcardRecv::phone_num_ parse error";
      r = dic->GetBigInteger(L"bid", &bankcard_id_);
      LOG_IF(ERROR, !r) << "UnbindBankcardRecv::bankcard_id_ parse error";
      r = dic->GetString(L"vCode", &verify_code_);
      LOG_IF(ERROR, !r) << "UnbindBankcardRecv::verify_code_ parse error";
      r = dic->GetBigInteger(L"timestamp", &timestamp_);
      LOG_IF(ERROR, !r) << "UnbindBankcardRecv::timestamp_ parse error";
      r = dic->GetString(L"vToken", &verify_token_);
      LOG_IF(ERROR, !r) << "UnbindBankcardRecv::verify_token_ parse error";
    } else {
      LOG(ERROR)<< "UnbindBankcardRecv Deserialize error";
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
                                                serializer);
  return err;
}
	
ChangeDefaultBankcardRecv::ChangeDefaultBankcardRecv(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
  uid_ = 0;
}

int32 ChangeDefaultBankcardRecv::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
    if (dic != NULL) {
      r = dic->GetBigInteger(L"uid", &uid_);
      LOG_IF(ERROR, !r) << "ChangeDefaultBankcardRecv::uid_ parse error";
      r = dic->GetBigInteger(L"bid", &bankcard_id_);
      LOG_IF(ERROR, !r) << "ChangeDefaultBankcardRecv::bankcard_id_ parse error";
    } else {
      LOG(ERROR)<< "ChangeDefaultBankcardRecv Deserialize error";
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
                                                serializer);
  return err;
}
	
BankAccountInfoRecv::BankAccountInfoRecv(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
}

int32 BankAccountInfoRecv::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
  							base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
  	if (dic != NULL) {
  		r = dic->GetString(L"cardNo", &bankcard_num_);
  		LOG_IF(ERROR, !r) << "BankAccountInfoRecv::bankcard_num_ parse error";
  	} else {
  		LOG(ERROR)<< "BankAccountInfoRecv Deserialize error";
  		err = JSON_FORMAT_ERR;
  		break;
  	}
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
  											  serializer);
  return err;
}
	
CreditListRecv::CreditListRecv(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
  uid_ = 0;
}

int32 CreditListRecv::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
    if (dic != NULL) {
      r = dic->GetBigInteger(L"uid", &uid_);
      LOG_IF(ERROR, !r) << "CreditListRecv::uid_ parse error";
      r = dic->GetString(L"status", &status_);
      LOG_IF(ERROR, !r) << "CreditListRecv::status_ parse error";
      r = dic->GetBigInteger(L"startPos", &start_pos_);
      LOG_IF(ERROR, !r) << "CreditListRecv::start_pos_ parse error";
      r = dic->GetBigInteger(L"count", &count_);
      LOG_IF(ERROR, !r) << "CreditListRecv::count_ parse error";
    } else {
      LOG(ERROR)<< "CreditListRecv Deserialize error";
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
                                                serializer);
  return err;
}
	
CreditDetailRecv::CreditDetailRecv(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
  uid_ = 0;
}

int32 CreditDetailRecv::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
    if (dic != NULL) {
      r = dic->GetBigInteger(L"uid", &uid_);
      LOG_IF(ERROR, !r) << "CreditDetailRecv::uid_ parse error";
      r = dic->GetBigInteger(L"rid", &recharge_id_);
      LOG_IF(ERROR, !r) << "CreditDetailRecv::recharge_id_ parse error";
    } else {
      LOG(ERROR)<< "CreditDetailRecv Deserialize error";
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
                                                serializer);
  return err;
}
	
UserWithdrawRecv::UserWithdrawRecv(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
  uid_ = 0;
}  

int32 UserWithdrawRecv::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
    if (dic != NULL) {
      r = dic->GetBigInteger(L"uid", &uid_);
      LOG_IF(ERROR, !r) << "UserWithdrawRecv::uid_ parse error";
      r = dic->GetReal(L"money", &money_);
      LOG_IF(ERROR, !r) << "UserWithdrawRecv::money_ parse error";
      r = dic->GetBigInteger(L"bid", &bankcard_id_);
      LOG_IF(ERROR, !r) << "UserWithdrawRecv::bankcard_id_ parse error";
      r = dic->GetString(L"pwd", &passwd_);
      LOG_IF(ERROR, !r) << "UserWithdrawRecv::passwd_ parse error";
    } else {
      LOG(ERROR)<< "UserWithdrawRecv Deserialize error";
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
                                                serializer);
  return err;
}

UserWithdrawListRecv::UserWithdrawListRecv(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
  uid_ = 0;
  start_pos_ = 0;
  count_ = 10;
  status_ = "1,2,3";
}  

int32 UserWithdrawListRecv::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
    if (dic != NULL) {
      r = dic->GetBigInteger(L"uid", &uid_);
      LOG_IF(ERROR, !r) << "UserWithdrawListRecv::uid_ parse error";
      r = dic->GetString(L"status", &status_);
      LOG_IF(ERROR, !r) << "UserWithdrawListRecv::status_ parse error";
      r = dic->GetBigInteger(L"startPos", &start_pos_);
      LOG_IF(ERROR, !r) << "UserWithdrawListRecv::start_pos_ parse error";
      r = dic->GetBigInteger(L"count", &count_);
      LOG_IF(ERROR, !r) << "UserWithdrawListRecv::count_ parse error";
    } else {
      LOG(ERROR)<< "UserWithdrawListRecv Deserialize error";
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
                                                serializer);
  return err;
}

ObtainVerifyCodeRecv::ObtainVerifyCodeRecv(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
  verify_type_ = 0;
}

int32 ObtainVerifyCodeRecv::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
    if (dic != NULL) {
      r = dic->GetBigInteger(L"verifyType", &verify_type_);
      LOG_IF(ERROR, !r) << "ObtainVerifyCodeRecv::verify_type_ parse error";
      r = dic->GetString(L"phone", &phone_num_);
      LOG_IF(ERROR, !r) << "ObtainVerifyCodeRecv::phone_num_ parse error";
    } else {
      LOG(ERROR)<< "ObtainVerifyCodeRecv Deserialize error";
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
                                                serializer);
  return err;
}
	
ChangeUserInfoRecv::ChangeUserInfoRecv(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
  uid_ = 0;
  gender_ = 0;
}

int32 ChangeUserInfoRecv::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      											base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
    if (dic != NULL) {
      r = dic->GetBigInteger(L"uid", &uid_);
      LOG_IF(ERROR, !r) << "ChangeUserInfoRecv::uid_ parse error";
      r = dic->GetString(L"screenName", &nickname_);
      LOG_IF(ERROR, !r) << "ChangeUserInfoRecv::nickname_ parse error";
      r = dic->GetBigInteger(L"gender", &gender_);
      LOG_IF(ERROR, !r) << "ChangeUserInfoRecv::gender_ parse error";
      r = dic->GetString(L"avatarLarge", &head_url_);
      LOG_IF(ERROR, !r) << "ChangeUserInfoRecv::head_url_ parse error";
    } else {
      LOG(ERROR)<< "ChangeUserInfoRecv Deserialize error";
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
      									  serializer);
  return err;
}

WxPlaceOrderRecv::WxPlaceOrderRecv(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
  uid_ = 0;
  price_ = 0;  // 订单总价  单位 分
}

int32 WxPlaceOrderRecv::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
    if (dic != NULL) {
      r = dic->GetBigInteger(L"uid", &uid_);
      LOG_IF(ERROR, !r) << "WxPlaceOrderRecv::uid_ parse error";
      r = dic->GetString(L"title", &title_);
      LOG_IF(ERROR, !r) << "WxPlaceOrderRecv::title_ parse error";
      r = dic->GetReal(L"price", &price_);
      LOG_IF(ERROR, !r) << "WxPlaceOrderRecv::price_ parse error";
    } else {
      LOG(ERROR)<< "WxPlaceOrderRecv Deserialize error";
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
                                                serializer);
  return err;
}

WXPayClientRecv::WXPayClientRecv(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
  uid_ = 0;
  recharge_id_ = 0;
  pay_result_ = 0;
}

int32 WXPayClientRecv::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
    if (dic != NULL) {
      r = dic->GetBigInteger(L"uid", &uid_);
      LOG_IF(ERROR, !r) << "WXPayClientRecv::uid_ parse error";
      r = dic->GetBigInteger(L"rid", &recharge_id_);
      LOG_IF(ERROR, !r) << "WXPayClientRecv::recharge_id_ parse error";
      r = dic->GetBigInteger(L"payResult", &pay_result_);
      LOG_IF(ERROR, !r) << "WXPayClientRecv::pay_result_ parse error";
    } else {
      LOG(ERROR)<< "WxPlaceOrderRecv Deserialize error";
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
                                                serializer);
  return err;
}

WXPayServerRecv::WXPayServerRecv(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
  recharge_id_ = 0;
  pay_result_ = 0;
  total_fee_ = 0;
}

int32 WXPayServerRecv::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
    if (dic != NULL) {
      r = dic->GetString(L"wxpay_result_", &xml_str_);
      LOG_IF(ERROR, !r) << "WXPayServerRecv::xml_str_ parse error";
      LOG(INFO)<< "WXPAY SERVER RESULT***" << xml_str_ << "***";
      if (r && xml_str_.length() > 5) {
        base_logic::ValueSerializer* deserializer =
            base_logic::ValueSerializer::Create(base_logic::IMPL_XML,
                                                &xml_str_);
        std::string err_str;
        int32 err = 0;
        DicValue* dic = (DicValue*) deserializer->Deserialize(&err, &err_str);
        if (dic != NULL) {
          dic->GetString(L"appid", &appid_);
          dic->GetString(L"mch_id", &mch_id_);
          appid_ = util::GetWxpayXmlValue(appid_);
          mch_id_ = util::GetWxpayXmlValue(mch_id_);
          std::string return_code;
          dic->GetString(L"return_code", &return_code);
          //通信成功标识
          if (return_code.find("SUCCESS") != std::string::npos) {
            std::string result_code;
            dic->GetString(L"result_code", &result_code);

            //订单总金额
            dic->GetBigInteger(L"total_fee", &total_fee_);
            //支付总金额
            dic->GetString(L"transaction_id", &transaction_id_);
            transaction_id_ = util::GetWxpayXmlValue(transaction_id_);
            //本平台订单号
            std::string out_trade_no;
            dic->GetString(L"out_trade_no", &out_trade_no);
            int npos1 = out_trade_no.find("<![CDATA[");
            int npos2 = out_trade_no.find("]]>");
            out_trade_no = out_trade_no.substr(npos1 + 9,
                                               npos2 - npos1 - 9 - 6);
            recharge_id_ = atol(out_trade_no.c_str());
            //支付成功标识
            if (result_code.find("SUCCESS") != std::string::npos) {
              pay_result_ = 1;
            } else {
              pay_result_ = -1;
            }
          }
        } else {
          LOG(ERROR)<< "WxPlaceOrderRecv xml  Deserialize error";
        }
        base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_XML,
                                                      deserializer);
      }

    } else {
      LOG(ERROR)<< "WxPlaceOrderRecv json Deserialize error";
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
                                                serializer);
  return err;
}

SMSCodeLoginRecv::SMSCodeLoginRecv(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
  timestamp_ = 0;
  verify_code_ = 0;
  user_type_ = 0;
}

int32 SMSCodeLoginRecv::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
    if (dic != NULL) {
      r = dic->GetBigInteger(L"timestamp_", &timestamp_);
      LOG_IF(ERROR, !r) << "SMSCodeLoginRecv::timestamp_ parse error";
      r = dic->GetBigInteger(L"verify_code_", &verify_code_);
      LOG_IF(ERROR, !r) << "SMSCodeLoginRecv::verify_code_ parse error";
      r = dic->GetBigInteger(L"user_type_", &user_type_);
      LOG_IF(ERROR, !r) << "SMSCodeLoginRecv::user_type_ parse error";
      r = dic->GetString(L"phone_num_", &phone_num_);
      LOG_IF(ERROR, !r) << "SMSCodeLoginRecv::phone_num_ parse error";
      r = dic->GetString(L"token_", &token_);
      LOG_IF(ERROR, !r) << "SMSCodeLoginRecv::token_ parse error";
    } else {
      LOG(ERROR)<< "SMSCodeLoginRecv Deserialize error";
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
                                                serializer);
  return err;
}

Heartbeat::Heartbeat(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
  uid_ = -1;
}

int32 Heartbeat::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
    if (dic != NULL) {
      r = dic->GetBigInteger(L"uid_", &uid_);
      LOG_IF(ERROR, !r) << "Heartbeat::uid_ parse error";
    } else {
      LOG(ERROR)<< "Heartbeat Deserialize error";
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
                                                serializer);
  return err;
}

DeviceTokenRecv::DeviceTokenRecv(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
  uid_ = 0;
}

int32 DeviceTokenRecv::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
    if (dic != NULL) {
      r = dic->GetBigInteger(L"uid_", &uid_);
      LOG_IF(ERROR, !r) << "DeviceTokenRecv::uid_ parse error";
      r = dic->GetString(L"device_token_", &device_token_);
      LOG_IF(ERROR, !r) << "DeviceTokenRecv::device_token_ parse error";
    } else {
      LOG(ERROR)<< "DeviceTokenRecv Deserialize error";
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
                                                serializer);
  return err;
}

UserCashRecv::UserCashRecv(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
  uid_ = 0;
}

int32 UserCashRecv::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
    if (dic != NULL) {
      r = dic->GetBigInteger(L"uid_", &uid_);
      LOG_IF(ERROR, !r) << "UserCashRecv::uid_ parse error";
    } else {
      LOG(ERROR)<< "UserCashRecv Deserialize error";
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
                                                serializer);
  return err;
}

CheckSMSCodeRecv::CheckSMSCodeRecv(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
  verify_code_ = 0;
  verify_type_ = 0;  //0-注册 1-登录 2-更新服务
  timestamp_ = 0;  //时间戳
}

int32 CheckSMSCodeRecv::Deserialize() {
  int32 err = 0;
  bool r = false;
  base_logic::ValueSerializer* serializer = base_logic::ValueSerializer::Create(
      base_logic::IMPL_JSON, &body_str_, false);
  std::string err_str;
  DicValue* dic = (DicValue*) serializer->Deserialize(&err, &err_str);
  do {
    if (dic != NULL) {
      r = dic->GetBigInteger(L"timestamp_", &timestamp_);
      LOG_IF(ERROR, !r) << "CheckSMSCodeRecv::timestamp_ parse error";
      r = dic->GetBigInteger(L"verify_code_", &verify_code_);
      LOG_IF(ERROR, !r) << "CheckSMSCodeRecv::verify_code_ parse error";
      r = dic->GetBigInteger(L"verify_type_", &verify_type_);
      LOG_IF(ERROR, !r) << "CheckSMSCodeRecv::verify_type_ parse error";
      r = dic->GetString(L"phone_num_", &phone_num_);
      LOG_IF(ERROR, !r) << "CheckSMSCodeRecv::phone_num_ parse error";
      r = dic->GetString(L"token_", &token_);
      LOG_IF(ERROR, !r) << "CheckSMSCodeRecv::token_ parse error";
    } else {
      LOG(ERROR)<< "CheckSMSCodeRecv Deserialize error";
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  base_logic::ValueSerializer::DeleteSerializer(base_logic::IMPL_JSON,
                                                serializer);
  return err;
}

}  // namespace user

