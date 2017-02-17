
#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <iostream>
#include <sstream>

// #include "client/linux/handler/exception_handler.h"

#if defined (FCGI_STD)
#include <fcgi_stdio.h>
#elif defined(FCGI_PLUS)
#include <fcgio.h>
#include <fcgi_config.h>
#endif

#include "log/mig_log.h"
#include "../pub/net/comm_head.h"
#include "../plugins/quotations/operator_code.h"
#include "fcgimodule/fcgimodule.h"
// 设置请求类型
//#define API_TYPE            george_logic::VIP_TYPE
//#define LOG_TYPE            log_trace::TRACE_API_LOG

int main(int agrc, char* argv[]) {
  fcgi_module::FcgiModule fcgi_client;
  std::string core_sock_file = "/var/www/tmp/swpcorefile";
  fcgi_client.Init("61.147.114.87",16001,QUOTATIONS_TYPE,
                   R_KCHART_TIME_LINE_DATA,1);

  //fcgi_client.Init(core_sock_file,HISTORY_TYPE,
                  // R_HISTORY_TRADES,1);
  fcgi_client.Run();
  fcgi_client.Close();
  return 0;
}
