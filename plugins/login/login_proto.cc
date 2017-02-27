// Copyright (c) 2016 The tourism Authors. All rights reserved.
// login_proto.cc

#include "login/login_proto.h"

#include <typeinfo>

#include "glog/logging.h"
#include "base/logic/base_values.h"
#include "public/basic/md5sum.h"

#include "pub/comm/comm_head.h"
//#include "pub/util/util.h"
#include "logic/logic_comm.h"

namespace login {

namespace net_request {

int32 Heartbeat::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 uid;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"id", &uid); if (r)
        set_uid(uid);
      if (!r) LOG_ERROR("Heartbeat::uid_ parse error");
    } else {
      LOG_ERROR("Heartbeat set_http_packet error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
}

int32 RegisterAccount::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  std::string verify_code;
  int64 timestamp;
  std::string verify_token;
  std::string phone_num;
  std::string passwd;
  do {
    if (value != NULL) {
      r = value->GetString(L"vCode", &verify_code);
      if (r)
        set_verify_code(verify_code);
      if (!r) LOG_ERROR("RegisterAccount::verify_code_ parse error");
      r = value->GetBigInteger(L"timestamp", &timestamp);
      if (r)
        set_timestamp(timestamp);
      if (!r) LOG_ERROR("RegisterAccount::timestamp_ parse error");
      r = value->GetString(L"vToken", &verify_token);
      if (r)
        set_verify_token(verify_token);
      if (!r) LOG_ERROR("RegisterAccount::verify_token_ parse error");
      r = value->GetString(L"phone", &phone_num);
      if (r)
        set_phone_num(phone_num);
      if (!r) LOG_ERROR("RegisterAccount::phone parse error");
      r = value->GetString(L"pwd", &passwd);
      if (r)
        set_passwd(passwd);
      if (!r) LOG_ERROR("RegisterAccount::pwd parse error");
    } else {
      LOG_ERROR("RegisterAccount Deserialize error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
}

  /*int32 RegisterAccount::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  std::string verify_code;
  int64 timestamp;
  std::string verify_token;
  std::string phone_num;
  std::string passwd;
  do {
    if (value != NULL) {
      r = value->GetString(L"vCode", &verify_code);
      if (r)
        set_verify_code(verify_code);
      if (!r) LOG_ERROR("RegisterAccount::verify_code_ parse error");
      if (!r) LOG_ERROR("RegisterAccount::verify_code_ parse error");
      r = value->GetBigInteger(L"timestamp", &timestamp);
      if (r)
        set_timestamp(timestamp);
      if (!r) LOG_ERROR("RegisterAccount::timestamp_ parse error");
      if (!r) LOG_ERROR("RegisterAccount::timestamp_ parse error");
      r = value->GetString(L"vToken", &verify_token);
      if (r)
        set_verify_token(verify_token);
      if (!r) LOG_ERROR("RegisterAccount::verify_token_ parse error");
      if (!r) LOG_ERROR("RegisterAccount::verify_token_ parse error");
      r = value->GetString(L"phone", &phone_num);
      if (r)
        set_phone_num(phone_num);
      if (!r) LOG_ERROR("RegisterAccount::phone parse error");
      if (!r) LOG_ERROR("RegisterAccount::phone parse error");
      r = value->GetString(L"pwd", &passwd);
      if (r)
        set_passwd(passwd);
      if (!r) LOG_ERROR("RegisterAccount::pwd parse error");
      if (!r) LOG_ERROR("RegisterAccount::pwd parse error");
    } else {
      LOG_ERROR("RegisterAccount Deserialize error");
      LOG_ERROR("RegisterAccount Deserialize error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
  }*/

int32 UserLogin::set_http_packet(base_logic::DictionaryValue* value) {
  bool r = false;
  int32 err = 0;
  //Value* v = serializer->Deserialize(&err, &err_str);
  //DicValue* value;
  std::string passwd;
  std::string phone_num;
  std::string token;
  do {
    /*if (v != NULL) {
      if (typeid(*v) == typeid(ListValue) {
        LOG_MSG("listvalue:");
        LOG_MSG("listvalue:");
        ((ListValue*)v)->GetDictionary(0, &value);
      } else if (typeid(*v) == typeid(DicValue) {
        LOG_MSG("valuevalue:");
        LOG_MSG("valuevalue:");
        value = (DicValue*) v;
      } else {
        err = JSON_FORMAT_ERR;
        break;
        }*/
      r = value->GetString(L"pwd", &passwd);
      if (r)
        set_passwd(passwd);
      if (!r) LOG_ERROR("Login::passwd parse error");
      /*if (r) {
        base::MD5Sum md5(passwd);
        passwd_ = md5.GetHash();
        }*/
      r = value->GetString(L"phone", &phone_num);
      if (r)
        set_phone_num(phone_num);
      if (!r) LOG_ERROR("Login::phone_num_ parse error");
      if (phone_num.length() < 11) {
        LOG_ERROR("phone is wrong");
        err = PHONE_NUM_ERR;
        break;
      }
      r = value->GetString(L"token", &token);
      if (r)
        set_token(token);
      if (!r) LOG_ERROR("Login::token_ parse error");
      /*} else {
      LOG_ERROR("Login Deserialize error");
      LOG_ERROR("Login Deserialize error");
      err = JSON_FORMAT_ERR;
      }*/
  }while (0);
  return err;
}

	/*SMSCodeLogin::SMSCodeLogin(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
  timestamp_ = 0;
  verify_code_ = 0;
  user_type_ = 0;
}

int32 SMSCodeLogin::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"timestamp_", &timestamp);
      if (!r) LOG_ERROR("SMSCodeLogin::timestamp_ parse error");
      if (!r) LOG_ERROR("SMSCodeLogin::timestamp_ parse error");
      r = value->GetBigInteger(L"verify_code_", &verify_code);
      if (!r) LOG_ERROR("SMSCodeLogin::verify_code_ parse error");
      if (!r) LOG_ERROR("SMSCodeLogin::verify_code_ parse error");
      r = value->GetBigInteger(L"user_type_", &user_type);
      if (!r) LOG_ERROR("SMSCodeLogin::user_type_ parse error");
      if (!r) LOG_ERROR("SMSCodeLogin::user_type_ parse error");
      r = value->GetString(L"phone_num_", &phone_num);
      if (!r) LOG_ERROR("SMSCodeLogin::phone_num_ parse error");
      if (!r) LOG_ERROR("SMSCodeLogin::phone_num_ parse error");
      r = value->GetString(L"token_", &token);
      if (!r) LOG_ERROR("SMSCodeLogin::token_ parse error");
      if (!r) LOG_ERROR("SMSCodeLogin::token_ parse error");
    } else {
      LOG_ERROR("SMSCodeLogin Deserialize error");
      LOG_ERROR("SMSCodeLogin Deserialize error");
      err = SMS_CODE_LOGIN_JSON_ERR;
      break;
    }
  }while (0);
  return err;
  }*/


  /*int32 Heartbeat::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 uid;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"id", &uid);
      if (r)
        set_uid(uid);
      if (!r) LOG_ERROR("Heartbeat::uid_ parse error");
      if (!r) LOG_ERROR("Heartbeat::uid_ parse error");
    } else {
      LOG_ERROR("Heartbeat Deserialize error");
      LOG_ERROR("Heartbeat Deserialize error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
  }*/

int32 ChangePasswd::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 type;
  std::string phone_num;
  std::string verify_code;
  int64 timestamp;
  std::string verify_token;
  std::string passwd;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"type", &type);
      if (r)
        set_type(type);
      if (!r) LOG_ERROR("ChangePasswd::type parse error");
      r = value->GetString(L"phone", &phone_num);
      if (r)
        set_phone_num(phone_num);
      if (!r) LOG_ERROR("ChangePasswd::phone_num_ parse error");
      r = value->GetString(L"vCode", &verify_code);
      if (r)
        set_verify_code(verify_code);
      if (!r) LOG_ERROR("ChangePasswd::verify_code_ parse error");
      r = value->GetBigInteger(L"timestamp", &timestamp);
      if (r)
        set_timestamp(timestamp);
      if (!r) LOG_ERROR("ChangePasswd::timestamp_ parse error");
      r = value->GetString(L"vToken", &verify_token);
      if (r)
        set_verify_token(verify_token);
      if (!r) LOG_ERROR("ChangePasswd::verify_token_ parse error");
      r = value->GetString(L"pwd", &passwd);
      if (r)
        set_passwd(passwd);
      if (!r) LOG_ERROR("ChangePasswd::pwd parse error");
    } else {
      LOG_ERROR("ChangePasswd Deserialize error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
}

int32 ObtainVerifyCode::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  int64 verify_type;
  std::string phone_num;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"verify_type_", &verify_type);
      if (r)
        set_verify_type(verify_type);
      if (!r) LOG_ERROR("ObtainVerifyCode::verify_type_ parse error");
      r = value->GetString(L"phone_num_", &phone_num);
      if (r)
        set_phone_num(phone_num);
      if (!r) LOG_ERROR("ObtainVerifyCode::phone_num_ parse error");
    } else {
      LOG_ERROR("ObtainVerifyCode Deserialize error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
}

  /*int32 ImproveData::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"id", &uid);
      if (r)
        set_uid(uid);
      if (!r) LOG_ERROR("ImproveData::uid_ parse error");
      if (!r) LOG_ERROR("ImproveData::uid_ parse error");
      r = value->GetBigInteger(L"gender_", &gender);
      if (!r) LOG_ERROR("ImproveData::gender_ parse error");
      if (!r) LOG_ERROR("ImproveData::gender_ parse error");
      r = value->GetString(L"nickname_", &nickname);
      if (!r) LOG_ERROR("ImproveData::nickname_ parse error");
      if (!r) LOG_ERROR("ImproveData::nickname_ parse error");
      r = value->GetString(L"head_url_", &head_url);
      if (!r) LOG_ERROR("ImproveData::head_url_ parse error");
      if (!r) LOG_ERROR("ImproveData::head_url_ parse error");
      r = value->GetString(L"address_", &address);
      if (!r) LOG_ERROR("ImproveData::address_ parse error");
      if (!r) LOG_ERROR("ImproveData::address_ parse error");
      r = value->GetReal(L"longitude_", &longitude);
      if (!r) LOG_ERROR("ImproveData::longitude_ parse error");
      if (!r) LOG_ERROR("ImproveData::longitude_ parse error");
      r = value->GetReal(L"latitude_", &latitude);
      if (!r) LOG_ERROR("ImproveData::latitude_ parse error");
      if (!r) LOG_ERROR("ImproveData::latitude_ parse error");
    } else {
      LOG_ERROR("ImproveData Deserialize error");
      LOG_ERROR("ImproveData Deserialize error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
  }*/

  /*int32 UserDetail::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  do {
    if (value != NULL) {
      r = value->GetString(L"uid_str_", &uid_str);
      if (!r) LOG_ERROR("UserDetail::uid_str_ parse error");
      if (!r) LOG_ERROR("UserDetail::uid_str_ parse error");

    } else {
      LOG_ERROR("UserDetail Deserialize error");
      LOG_ERROR("UserDetail Deserialize error");
      err = JSON_FORMAT_ERR;
      break;
    }
  }while (0);
  return err;
  }*/


	/*int32 VerifyPasswd::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"id", &uid);
      if (!r) LOG_ERROR("VerifyPasswd::uid_ parse error");
      if (!r) LOG_ERROR("VerifyPasswd::uid_ parse error");
      r = value->GetBigInteger(L"passwd_type_", &passwd_type);
      if (!r) LOG_ERROR("VerifyPasswd::passwd_type_ parse error");
      if (!r) LOG_ERROR("VerifyPasswd::passwd_type_ parse error");
      r = value->GetString(L"passwd_", &passwd);
      if (r) {
        base::MD5Sum md5(passwd);
        passwd_ = md5.GetHash();
      }
      if (!r) LOG_ERROR("VerifyPasswd::passwd_ parse error");
      if (!r) LOG_ERROR("VerifyPasswd::passwd_ parse error");
    } else {
      LOG_ERROR("VerifyPasswd Deserialize error");
      LOG_ERROR("VerifyPasswd Deserialize error");
      err = REQUEST_JSON_ERR;
      break;
    }
  }while (0);
  return err;
  }*/

	/*ChangePayPasswd::ChangePayPasswd(PacketHead packet) {
  head_ = packet.head();
  body_str_ = packet.body_str();
  uid_ = 0;
  change_type_ = 0;
  passwd_type_ = 0;
}

int32 ChangePayPasswd::set_http_packet(base_logic::DictionaryValue* value) {
  int32 err = 0;
  bool r = false;
  do {
    if (value != NULL) {
      r = value->GetBigInteger(L"id", &uid);
      if (!r) LOG_ERROR("ChangePayPasswd::uid_ parse error");
      if (!r) LOG_ERROR("ChangePayPasswd::uid_ parse error");
      r = value->GetBigInteger(L"change_type_", &change_type);
      if (!r) LOG_ERROR("ChangePayPasswd::change_type_ parse error");
      if (!r) LOG_ERROR("ChangePayPasswd::change_type_ parse error");
      r = value->GetBigInteger(L"passwd_type_", &passwd_type);
      if (!r) LOG_ERROR("ChangePayPasswd::passwd_type_ parse error");
      if (!r) LOG_ERROR("ChangePayPasswd::passwd_type_ parse error");
      r = value->GetString(L"new_passwd_", &new_passwd);
      if (r) {
        base::MD5Sum md5(new_passwd);
        new_passwd_ = md5.GetHash();
      }
      if (!r) LOG_ERROR("ChangePayPasswd::new_passwd_ parse error");
      if (!r) LOG_ERROR("ChangePayPasswd::new_passwd_ parse error");
      r = value->GetString(L"old_passwd_", &old_passwd);
      if (r) {
        base::MD5Sum md5(old_passwd);
        old_passwd_ = md5.GetHash();
      }
      if (!r) LOG_ERROR("ChangePayPasswd::old_passwd_ parse error");
      if (!r) LOG_ERROR("ChangePayPasswd::old_passwd_ parse error");
    } else {
      LOG_ERROR("ChangePayPasswd Deserialize error");
      LOG_ERROR("ChangePayPasswd Deserialize error");
      err = REQUEST_JSON_ERR;
      break;
    }
  }while (0);
  return err;
  }*/
  
} // namespace net_request

}  // namespace login

