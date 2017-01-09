// Copyright (c) 2016 The tourism Authors. All rights reserved.
// comm_head.h
// Created on: 2016年8月10日.
// Author: Paco.
#ifndef PUB_COMM_COMM_HEAD_H_
#define PUB_COMM_COMM_HEAD_H_

enum TIME_TASK {
  CONNECT_CKECK = 100,
  SHARE_DATA_INIT = 101,//初始化共享数据
  SHARE_DATA_INIT_TEN = 102,//定时更新共享数据
  ORDER_STATUS_CHECK = 103, //定时监测未支付的订单
};

enum PACKET_TYPE {
  ERROR_TYPE = 0,
  USER_TYPE = 1,
  CHAT_TYPE = 2,
  LOGIN_TYPE = 3
};

enum PACKET_ERROR {
  JSON_FORMAT_ERR = -100,
  PHONE_NUM_ERR = -103,
  PHONE_OR_PASSWD_ERR = -109,
  TOKEN_ERR_OR_NOTEXIST = -110,
  SQL_EXEC_ERR = -111	
};


#endif  // PUB_COMM_COMM_HEAD_H_
