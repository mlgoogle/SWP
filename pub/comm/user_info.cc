// Copyright (c) 2016 The tourism Authors. All rights reserved.
// user.cc
// Created on: 2016年8月19日.
// Author: Paco.

#include "pub/comm/user_info.h"
#include "glog/logging.h"

UserInfo::UserInfo() {
  data_ = new UserData();
}

UserInfo::UserInfo(const UserInfo& user) : data_(user.data_) {
  if (data_ != NULL)
    data_->AddRef();
}

UserInfo::~UserInfo() {
  //LOG(INFO) << "delete ~UserInfo()";
  if (data_ != NULL) {
    data_->DelRef();
  }
}

UserInfo& UserInfo::operator=(const UserInfo& user) {
  if (data_ == user.data_)
    return *this;
  if (data_ != NULL)
    data_->DelRef();
  if (user.data_ != NULL)
    user.data_->AddRef();
  data_ = user.data_;
  return *this;
}

void UserInfo::Serialization(DicValue* dic) {
  dic->GetBigInteger(L"id", &data_->uid_);
  dic->GetString(L"phone", &data_->phone_num_);
  dic->GetString(L"screenName", &data_->nickname_);
  dic->GetString(L"avatarLarge", &data_->head_url_);
  dic->GetBigInteger(L"balance",&data_->gender_);
}
