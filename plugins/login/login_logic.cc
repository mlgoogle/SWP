// Copyright (c) 2016 The login Authors. All rights reserved.
// login_logic.cc

#include "net/comm_head.h"
#include "pub/comm/comm_head.h"
#include "login/login_logic.h"

#include <assert.h>
#include <dlfcn.h>
#include <openssl/sha.h>
#include <signal.h>
#include <sys/socket.h>
#include <netdb.h>

#include "core/common.h"
#include "core/network.h"
#include "glog/logging.h"
#include "base/logic/base_values.h"
#include "public/http/http_method.h"
#include "glog/logging.h"
//#include "gtpush/IGtPush.h"
#include "public/basic/basictypes.h"
#include "public/config/config.h"
#include "public/basic/native_library.h"
#include "base/logic/base_values.h"
#include "login/login_opcode.h"
#include "pub/share/data_share_mgr.h"
#include "login/login_proto.h"
#include "public/basic/md5sum.h"
#include "logic/logic_unit.h"
#include "net/packet_processing.h"
#include "pub/util/util.h"

#define DEFAULT_CONFIG_PATH "./plugins/login/login_config.xml"

#define SHELL_SMS "./verify_code_sms.sh"
#define SMS_KEY "yd1742653sd"
namespace login {
Loginlogic* Loginlogic::instance_ = NULL;

Loginlogic::Loginlogic() {
  login_mysql_ = NULL;

  if (!Init())
    assert(0);
  
  InitLog();
}

void Loginlogic::InitLog() {
  //初始化日志名
  google::InitGoogleLogging("actuals");

  //初始化info级别日志存储位置以及日志文件开头 ./info/info_20160808-105851.4743
  google::SetLogDestination(google::INFO, "./log/info_");
  google::SetLogDestination(google::WARNING, "./log/waring_");
  google::SetLogDestination(google::ERROR, "./log/error_");

  //配置输出到标准输出的级别 INFO级别及以上输出到标准输出
  google::SetStderrLogging(google::INFO);

  //设置输出到屏幕的日志显示相应颜色
  FLAGS_colorlogtostderr = true;

  //实时输出日志
  FLAGS_logbufsecs = 0;

  //最大日志大小（MB）
  FLAGS_max_log_size = 100;

  //当磁盘被写满时，停止日志输出
  FLAGS_stop_logging_if_full_disk = true;

  //捕捉 core dumped
  google::InstallFailureSignalHandler();

  LOG(INFO)<< "glog has init finished";
}

Loginlogic::~Loginlogic() {
}
	
bool Loginlogic::Init() {
  bool r = false;
  config::FileConfig* config = config::FileConfig::GetFileConfig();
  std::string path = DEFAULT_CONFIG_PATH;
  if (config == NULL) {
    LOG(ERROR) << "Loginlogic config init error";
    return false;
  }
  r = config->LoadConfig(path);
  if (!r) {
    LOG(ERROR) << "login config load error";
    return false;
  }
  login_mysql_ = new LoginMysql(config);
  InitShareData();
  return true;
}

bool Loginlogic::InitShareData() {
  basic::libhandle  handle = NULL;
  handle = basic::load_native_library("./data.so");
  if (handle==NULL){
    LOG(ERROR) << "Can't load path data.so\n";
  }
  LOG(INFO) << "load data.so success";
  share::DataShareMgr* (*pengine) (void);
  pengine = (share::DataShareMgr *(*)(void))basic::get_function_pointer(handle, "GetDataShareMgr");
  if(pengine==NULL){
    LOG(ERROR) << "Can't find GetDataShareMgr\n";
    return false;
  }
  data_share_mgr_ = (*pengine)();
  return false;
}

Loginlogic* Loginlogic::GetInstance() {
  if (instance_ == NULL)
    instance_ = new Loginlogic();
  return instance_;
}

void Loginlogic::FreeInstance() {
  delete instance_;
  instance_ = NULL;
}

bool Loginlogic::OnLoginConnect(struct server *srv, const int socket) {
  LOG(INFO)<< "OnLoginConnect";
  return true;
}

bool Loginlogic::OnLoginMessage(struct server *srv, const int socket,
                                    const void *msg, const int len) {
  if (srv == NULL || socket < 0 || msg == NULL || len < PACKET_HEAD_LENGTH)
    return false;

  LOG_ERROR2("====================login look");
  PacketHead *packet = NULL;
  if (!net::PacketProsess::UnpackStream(msg, len, &packet)) {
    //    LOG_ERROR2("UnpackStream Error socket:%d", socket);
    return false;
  }
  
  LOG(INFO) << "-----------type:" << packet->type << "---opecode:" << packet->operate_code; 
  if (packet->type == LOGIN_TYPE
      && logic::SomeUtils::VerifyToken(packet)) {
    switch (packet->operate_code) {
    case HEARTBEAT_REQ: {
      OnHeartbeat(socket, packet);
      break;
    }
      case REGISTER_ACCOUNT_REQ: {
        OnRegisterAccount(socket, packet);
        break;
      }
      case USER_LOGIN_REQ: {
        OnUserLogin(socket, packet);
        break;
      }
      case CHANGE_PASSWD_REQ: {
        OnChangePasswd(socket, packet);
        break;
      }
	}
    return true;
  }
  return false;
}
	
int32 Loginlogic::OnHeartbeat(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
    net_request::Heartbeat heartbeat;
    struct PacketControl* packet_recv = (struct PacketControl*) (packet);
    heartbeat.set_http_packet(packet_recv->body_);
    data_share_mgr_->Heartbeat(heartbeat.uid());
  } while (0);
  return err;
}

int32 Loginlogic::OnRegisterAccount(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
    net_request::RegisterAccount register_account;
    struct PacketControl* packet_recv = (struct PacketControl*) (packet);
    register_account.set_http_packet(packet_recv->body_);
    if (time(NULL) - register_account.timestamp() > 15000 * 60) {
      err = VERIFY_CODE_OVERDUE;
      break;
    }
    std::stringstream ss;
    ss << SMS_KEY << register_account.timestamp() << register_account.verify_code() << register_account.phone_num();
    base::MD5Sum md5(ss.str());
    if (md5.GetHash() != register_account.verify_token()) {
      err = VERIFY_CODE_ERR;
      break;
    }
    //DicValue dic;
    //err = login_mysql_->RegisterInsertAndSelect(register_account.phone_num(), register_account.passwd(), &dic);
    //if (err < 0)
    // break;
    //    ////SendMsg(socket, packet, &dic, REGISTER_ACCOUNT_RLY, err);
    //dic.SetString("phone", register_account.phone_num());
    //dic.SetString("pwd", register_account.passwd());
    packet->reserved = socket;
    LOG(INFO) << "recv socket:" << packet->reserved;
    send_message(server_fd_, packet);
  } while (0);
  if (err < 0) {
    send_error(socket, LOGIN_TYPE, REGISTER_ACCOUNT_RLY, err);
  }
  return err;
}

int32 Loginlogic::OnUserLogin(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
    //net_request::UserLogin user_login;
    //struct PacketControl* packet_recv = (struct PacketControl*) (packet);
    //user_login.set_http_packet(packet_recv->body_);
    //if (UserIsLogin(rev.phone_num())) {
      // todo
    //}
    packet->reserved = socket;
    send_message(server_fd_, packet);
  } while (0);
  if (err < 0) {
    send_error(socket, LOGIN_TYPE, USER_LOGIN_RLY, err);
  }
  LOG(INFO) << "UserLogin finish err:" << err;
  return err;
}

int32 Loginlogic::OnChangePasswd(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
    net_request::ChangePasswd change_passwd;
    struct PacketControl* packet_recv = (struct PacketControl*) (packet);
    change_passwd.set_http_packet(packet_recv->body_);
    if (time(NULL) - change_passwd.timestamp() > 1500 * 60) {
      err = VERIFY_CODE_OVERDUE;
      break;
    }
    std::stringstream ss;
    ss << SMS_KEY << change_passwd.timestamp() << change_passwd.verify_code() << change_passwd.phone_num();
    base::MD5Sum md5(ss.str());
    if (md5.GetHash() != change_passwd.verify_token()) {
      err = VERIFY_CODE_ERR;
      break;
	}
    /*UserInfo* p = data_share_mgr_->GetUser(change_passwd.uid());
    if (p == NULL || !p->is_login()) {
      err = USER_NOT_IN_CACHE;
      break;
	  }
    LOG(INFO) << "pwd:" << p->passwd();
    if (p->passwd() != change_passwd.old_passwd()) {
      err = CHANGE_OLD_PWD_ERR;
      break;
	  } else */{
	  int32 type = change_passwd.type();
    if (type == net_request::ChangePasswd::PASSWD_LOGIN) {
      packet->reserved = socket; 
      send_message(server_fd_, packet);
    } else if (type == net_request::ChangePasswd::PASSWD_TRADE) {
        err = login_mysql_->ChangePasswdUpdate(change_passwd.phone_num(), change_passwd.passwd());
        if (err < 0)
          break;
        struct PacketControl packet_control;
        MAKE_HEAD(packet_control, CHANGE_PASSWD_RLY, LOGIN_TYPE, 0, 0, 0);
        send_message(socket, &packet_control);
      }
      //p->set_passwd(change_passwd.new_passwd());
      ////SendMsg(socket, packet, NULL, CHANGE_PASSWD_RLY, err);
    }
  } while (0);
  if (err < 0) {
    send_error(socket, LOGIN_TYPE, CHANGE_PASSWD_RLY, err);
  }
  return err;
}

bool Loginlogic::UserIsLogin(std::string u) {
  return false;
}

bool Loginlogic::OnLoginClose(struct server *srv, const int socket) {
  return true;
}

bool Loginlogic::OnBroadcastConnect(struct server *srv, const int socket,
                                      const void *msg, const int len) {
  server_fd_ = socket;
  
  LOG(INFO)<< "OnBroadcastConnect";
  return true;
}

bool Loginlogic::OnBroadcastMessage(struct server *srv, const int socket,
                                      const void *msg, const int len) {
  if (srv == NULL || socket < 0 || msg == NULL || len < PACKET_HEAD_LENGTH)
    return false;

  PacketHead *packet = NULL;
  if (!net::PacketProsess::UnpackStream(msg, len, &packet)) {
    //    LOG_ERROR2("UnpackStream Error socket:%d", socket);
    return false;
  }
  
  if (packet->type == LOGIN_TYPE) {
	switch (packet->operate_code) {
  case REGISTER_ACCOUNT_RLY: {
		OnRegisterAccountReply(socket, packet);
		break;
	  }
      case USER_LOGIN_RLY: {
        OnUserLoginReply(socket, packet);
        break;
      }
  case CHANGE_PASSWD_RLY: {
    send_message(packet->reserved, packet);
    break;
  }
	}
  return true;
  }
  return false;
}

int32 Loginlogic::OnRegisterAccountReply(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
    net_request::RegisterAccount register_account;
    struct PacketControl* packet_recv = (struct PacketControl*) (packet);
    register_account.set_http_packet(packet_recv->body_);
    if (err < 0)
      break;
    /*if (time(NULL) - rev.timestamp() > 15 * 60) {
      err = VERIFY_CODE_OVERDUE;
      break;
    }
    std::stringstream ss;
    ss << SMS_KEY << rev.timestamp() << rev.verify_code() << rev.phone_num();
	base::MD5Sum md5(ss.str());
    if (md5.GetHash() != rev.token()) {
      err = VERIFY_CODE_ERR;
      break;
	  }*/
  	if (register_account.phone_num() != "") {
      DicValue dic;
      err = login_mysql_->RegisterInsertAndSelect(register_account.phone_num(), register_account.passwd(), &dic);
      if (err < 0)
  	  break;
      struct PacketControl packet_control;
      MAKE_HEAD(packet_control, REGISTER_ACCOUNT_RLY, LOGIN_TYPE, 0, 0, 0);
      packet_control.body_ = &dic;
      send_message(packet->reserved, &packet_control);
  	  //SendMsg(packet->reserved, packet, &dic, REGISTER_ACCOUNT_RLY, err);
    } else {
      send_message(packet->reserved, packet);
    }
  } while (0);
  if (err < 0) {
    send_error(socket, LOGIN_TYPE, REGISTER_ACCOUNT_RLY, err);
  }
  return err;
}
	
int32 Loginlogic::OnUserLoginReply(const int32 socket, PacketHead* packet) {
  int32 err = 0;
  do {
    net_request::UserLogin user_login;
    struct PacketControl* packet_recv = (struct PacketControl*) (packet);
    user_login.set_http_packet(packet_recv->body_);
    if (UserIsLogin(user_login.phone_num())) {
      // todo
    }
    if (user_login.phone_num() != "") {
      ////////////CHANGE
      std::string client_ip;
      util::GetIPAddress(packet->reserved, &client_ip, NULL);
    DicValue dic;
    err = login_mysql_->UserLoginSelect(user_login.phone_num(), client_ip, &dic);
    if (err < 0)
      break;
    LOG(INFO) << "packet->reserved:" << packet->reserved;
	  if (user_login.token() != "")
	    dic.SetString("token", user_login.token());
    struct PacketControl packet_control;
    MAKE_HEAD(packet_control, USER_LOGIN_RLY, LOGIN_TYPE, 0, 0, 0);
    packet_control.body_ = &dic;
    send_message(packet->reserved, &packet_control);
    //SendMsg(packet->reserved, packet, &dic, USER_LOGIN_RLY, err);
    AddUser(packet->reserved, &dic, user_login.token());
    } else {
      LOG(INFO)<< "token err here";
      send_message(packet->reserved, packet);
      return -1;
    }
		//SendError(packet->reserved, packet, PHONE_OR_PASSWD_ERR, USER_LOGIN_RLY, err);
  } while (0);
  if (err < 0) {
    send_error(packet->reserved, LOGIN_TYPE, USER_LOGIN_RLY, err);
  }
  LOG(INFO)<< "UserLoginReply finish err:" << err;
  return err;
}
  
void Loginlogic::AddUser(int32 fd, DicValue* v, std::string token) {
    UserInfo* user = NULL;
    //游客
    user = new UserInfo();
    base_logic::DictionaryValue* dic;
    v->GetDictionary(L"userinfo", &dic);
    user->Serialization(dic);
    //    delete dic;
    user->set_is_login(true);
    user->set_socket_fd(fd);
    user->set_token(token);
    LOG(INFO) << "add user id:" << user->uid() << " fd:" << fd;
    data_share_mgr_->AddUser(user);
  }

bool Loginlogic::OnBroadcastClose(struct server *srv, const int socket) {
  server_fd_ = -1;
  
  pthread_t tid;
  if (pthread_create(&tid, 0, Loginlogic::AutoReconnectToServer, (void*)srv) != 0)
	LOG(ERROR) << "can not create thread AutoReconnectToserver";
  pthread_detach(tid);
  
  return true;
}

bool Loginlogic::OnInitTimer(struct server *srv) {
  srv->add_time_task(srv, "login", CONNECT_CKECK, 15, -1);
  return true;
}

bool Loginlogic::OnTimeout(struct server *srv, char *id, int opcode,
                             int time) {
  switch (opcode) {
    case CONNECT_CKECK: {
      data_share_mgr_->CheckHeartLoss();
      break;
    }
  }
  return true;
}

void* Loginlogic::AutoReconnectToServer(void* arg) {
  struct server* srv = (struct server*)arg;
  int ret = 0;
  
  do {
	ret = srv->create_reconnects(srv);
	sleep(1);
  } while (ret < 0);
  LOG(INFO) << "try reconnect remote server:" << ret;
}

int Loginlogic::SendFull(int socket, const char *buffer, size_t nbytes) {
  ssize_t amt = 0;
  ssize_t total = 0;
  const char *buf = buffer;

  do {
    amt = nbytes;
    amt = send(socket, buf, amt, 0);
    buf = buf + amt;
    nbytes -= amt;
    total += amt;
  } while (amt != -1 && nbytes > 0);

  LOG(INFO) << "SendFull:" << total;
  return (int) (amt == -1 ? amt : total);
}

void Loginlogic::SendPacket(const int socket, PacketHead* packet) {

  int packet_length = packet->packet_length;
  LOG(INFO) << "SendPacket packet_length:" << packet_length << ", head:" << HEAD_LENGTH;
  LOG(INFO) << (char*)(packet + HEAD_LENGTH + 5);
  char* s = new char[packet_length + 1];
  //LOG(INFO)<< "packet body:" << packet->body_str();
  //memset(s, 0, packet->packet_length);
  memcpy(s, &packet, packet_length);
  s[packet_length] = '\0';
  //memcpy(s + HEAD_LENGTH, packet->body_str().c_str(),
  //      packet->body_str().length());
  int total = SendFull(socket, s, packet_length);
  delete[] s;
  s = NULL;
  LOG_IF(ERROR, total != packet_length) << "send packet wrong";
}

  /*int Loginlogic::SendFull(int socket, const char *buffer, size_t nbytes) {
  ssize_t amt = 0;
  ssize_t total = 0;
  const char *buf = buffer;

  do {
    amt = nbytes;
    amt = send(socket, buf, amt, 0);
    buf = buf + amt;
    nbytes -= amt;
    total += amt;
  } while (amt != -1 && nbytes > 0);

  return (int) (amt == -1 ? amt : total);
}

void Loginlogic::SendPacket(const int socket, PacketHead* packet) {

  char* s = new char[packet->packet_length()];
  LOG(INFO)<< "packet body:" << packet->body_str();
  memset(s, 0, packet->packet_length());
  memcpy(s, &packet->head(), HEAD_LENGTH);
  memcpy(s + HEAD_LENGTH, packet->body_str().c_str(),
         packet->body_str().length());
  int total = SendFull(socket, s, packet->packet_length());
  delete[] s;
  s = NULL;
  LOG_IF(ERROR, total != packet->packet_length()) << "send packet wrong";
}

void Loginlogic::SendError(const int socket, PacketHead* packet, int32 err,
                             int16 opcode) {
  PacketErr p_err;
  p_err.set_head(packet->head());
  p_err.set_type(3);
  p_err.set_error(err);
  p_err.Serialize();
  p_err.AdapterLen();
  p_err.set_operate_code(opcode);
  SendPacket(socket, &p_err);
}

void Loginlogic::SendMsg(const int socket, PacketHead* packet, DicValue* dic,
                           int16 opcode) {
  PacketHead send;
  send.set_head(packet->head());
  send.Serialize(dic);
  send.AdapterLen();
  send.set_operate_code(opcode);
  SendPacket(socket, &send);
  }*/

}  // namespace bigv

