//  Copyright (c) 2017-2018 The quotations Authors. All rights reserved.
//  Created on: 2017年1月8日 Author: kerry

#ifndef SWP_KAFKA_SCHDULER_H_
#define SWP_KAFKA_SCHDULER_H_


namespace kafka_logic {

class SchdulerEngine {

};

class SchdulerEngineImpl : public SchdulerEngine {

};

__attribute__((visibility("default")))
class KafkaSchdulerManager {
 public:
  KafkaSchdulerManager();
  virtual ~KafkaSchdulerManager();
 public:
 private:
  void Init();
};

class KafkaSchdulerEngine {
 private:
  static KafkaSchdulerEngine* schduler_engine_;
  static KafkaSchdulerManager* schduler_mgr_;
 public:

  __attribute__((visibility("default")))
   static KafkaSchdulerManager* GetSchdulerManager() {
    if (schduler_mgr_)
      schduler_mgr_ = new KafkaSchdulerManager();
    return schduler_mgr_;
  }

  __attribute__((visibility("default")))
  static KafkaSchdulerEngine* GetSchdulerEngine() {
    if(schduler_engine_ == NULL)
      schduler_engine_ = new  KafkaSchdulerEngine();
    return schduler_engine_;
  }

};

}

#ifdef __cplusplus
extern "C" {
#endif

kafka_logic::SchdulerEngine* GetKafkaSchdulerEngin(void);

#ifdef __cplusplus
}
#endif

#endif
