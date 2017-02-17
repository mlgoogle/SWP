
###############################################################################
## 编译器
COMPILER = g++
COMPILERC = gcc

## 编译选项
## for debug -DROOM_DEBUG_MCACHE
CPP_FLAG = -g -Wall -w -fPIC -c -D_LINUX -DDEBUG -D_DEBUG -D_REENTRANT -D_GNU_SOURCE -D__DEBUG_CORE__ -DFCGI_STD  #-DCHECK_HEADER-DTEST
RCPP_FLAG = -g -Wall -w -fPIC -c -D_LINUX -DDEBUG -D_DEBUG -D_REENTRANT -D_GNU_SOURCE -DFCGI_STD #-DTEST
## for release
##CPP_FLAG = -O3 -Wall -s -w -fPIC -c -D_LINUX -DNDEBUG -D_REENTRANT -D_GNU_SOURCE -DFCGI_STD

## 链接选项
## for debug
LINK_FLAGS = -g  -fPIC
## for release
## LINK_FLAGS = -s -O3 -shared -fPIC

LIB_DIR = ../../library
BASE_DIR = ./../pub
PLUGIN_DIR = ../plugins
CUSTOM_THIRD_PATH = $(LIB_DIR)/mylib/third_party
## 头文件
INCLUDE_PATHS = -I$(LIB_DIR)/mylib/public/\
		-I$(LIB_DIR)/mylib/base\
		-I/usr/local/lib\
		-I$(BASE_DIR)/\
		-I$(PLUGIN_DIR)\
		-I$(LIB_DIR)/third_party/breakpad/src\
		-I$(CUSTOM_THIRD_PATH)\
		

## 库
LINK_PATHS =  -L./
LINK_LIBRARYS = -lrt -lpthread -lfcgi++ \


# 编译
COMPILE = $(COMPILER) $(CPP_FLAG) $(INCLUDE_PATHS) -o $@
RCOMPILE = $(COMPILER) $(RCPP_FLAG) $(INCLUDE_PATHS) -o $@

# 链接
LINK = $(COMPILER) $(LINK_FLAGS) $(LINK_PATHS) $? -o $(OUTPUT_FILE) $(LINK_LIBRARYS)
LINKALL = $(COMPILER) $(LINK_FLAGS) $(LINK_PATHS) $?  $(LINK_LIBRARYS)

POBJ =  mig_log.o core_interface.o http_formate.o fcgimodule.o  packet_processing.o\
	$(LIB_DIR)/mylib/third_party/dmg_fp/lib/dmg_fp.a\
	$(LIB_DIR)/mylib/base/lib/mybase.a
OUTPUT_FILE = /var/www/cgi-bin/swp
#############################################################################################################################
all: clean proc delete-temp-file

proc: historyproc quotationsproc tradesproc

######################historyproc###############################################
HISTORYNAME = history_
HISTORYPROC_PATH = /history
HISTORY_OBJECT_PATH = ./obj$(NEWSPROC_PATH)
OTJERPROC_VERSION = /v1
historyproc:$(HISTORYPROC_PATH)/his_position_list.fcgi

$(HISTORYPROC_PATH)/his_position_list.fcgi: $(HISTORY_OBJECT_PATH)/$(HISTORYNAME)his_position_list.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(HISTORYPROC_PATH)$(OTJERPROC_VERSION)/his_position_list.fcgi
	
### 编译
$(HISTORY_OBJECT_PATH)/$(HISTORYNAME)his_position_list.o:
	$(COMPILE) .$(HISTORYPROC_PATH)$(OTJERPROC_VERSION)/his_position_list/his_position_list.cc
	

######################quotationsproc###############################################
QUOTATIONSNAME = quotations_
QUOTATIONSPROC_PATH = /quotations
QUOTATIONS_OBJECT_PATH = ./obj$(NEWSPROC_PATH)
OTJERPROC_VERSION = /v1
quotationsproc:$(QUOTATIONSPROC_PATH)/kchart.fcgi $(QUOTATIONSPROC_PATH)/realtime.fcgi $(QUOTATIONSPROC_PATH)/timeline.fcgi

$(QUOTATIONSPROC_PATH)/kchart.fcgi: $(QUOTATIONS_OBJECT_PATH)/$(QUOTATIONSNAME)kchart.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(QUOTATIONSPROC_PATH)$(OTJERPROC_VERSION)/kchart.fcgi

$(QUOTATIONSPROC_PATH)/realtime.fcgi: $(QUOTATIONS_OBJECT_PATH)/$(QUOTATIONSNAME)realtime.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(QUOTATIONSPROC_PATH)$(OTJERPROC_VERSION)/realtime.fcgi

$(QUOTATIONSPROC_PATH)/timeline.fcgi: $(QUOTATIONS_OBJECT_PATH)/$(QUOTATIONSNAME)timeline.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(QUOTATIONSPROC_PATH)$(OTJERPROC_VERSION)/timeline.fcgi
		
### 编译
$(QUOTATIONS_OBJECT_PATH)/$(QUOTATIONSNAME)kchart.o:
	$(COMPILE) .$(QUOTATIONSPROC_PATH)$(OTJERPROC_VERSION)/kchart/kchart.cc

$(QUOTATIONS_OBJECT_PATH)/$(QUOTATIONSNAME)realtime.o:
	$(COMPILE) .$(QUOTATIONSPROC_PATH)$(OTJERPROC_VERSION)/realtime/realtime.cc
	
$(QUOTATIONS_OBJECT_PATH)/$(QUOTATIONSNAME)timeline.o:
	$(COMPILE) .$(QUOTATIONSPROC_PATH)$(OTJERPROC_VERSION)/timeline/timeline.cc
	

######################tradesproc###############################################
TRADESNAME = trades_
TRADESPROC_PATH = /trades
TRADES_OBJECT_PATH = ./obj$(NEWSPROC_PATH)
OTJERPROC_VERSION = /v1
tradesproc:$(TRADESPROC_PATH)/cur_position_list.fcgi $(TRADESPROC_PATH)/open_position.fcgi $(TRADESPROC_PATH)/goods.fcgi

$(TRADESPROC_PATH)/cur_position_list.fcgi: $(TRADES_OBJECT_PATH)/$(TRADESNAME)cur_position_list.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(TRADESPROC_PATH)$(OTJERPROC_VERSION)/cur_position_list.fcgi

$(TRADESPROC_PATH)/open_position.fcgi: $(TRADES_OBJECT_PATH)/$(TRADESNAME)open_position.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(TRADESPROC_PATH)$(OTJERPROC_VERSION)/open_position.fcgi

$(TRADESPROC_PATH)/goods.fcgi: $(TRADES_OBJECT_PATH)/$(TRADESNAME)goods.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(TRADESPROC_PATH)$(OTJERPROC_VERSION)/goods.fcgi
		
### 编译
$(TRADES_OBJECT_PATH)/$(TRADESNAME)cur_position_list.o:
	$(COMPILE) .$(TRADESPROC_PATH)$(OTJERPROC_VERSION)/cur_position_list/cur_position_list.cc

$(TRADES_OBJECT_PATH)/$(TRADESNAME)open_position.o:
	$(COMPILE) .$(TRADESPROC_PATH)$(OTJERPROC_VERSION)/open_position/open_position.cc
	
$(TRADES_OBJECT_PATH)/$(TRADESNAME)goods.o:
	$(COMPILE) .$(TRADESPROC_PATH)$(OTJERPROC_VERSION)/goods/goods.cc



clean:
	-rm -f *.o
	-rm -f $(OUTPUT_FILE)./*.fcgi

delete-temp-file:
	-rm -f *.o

############public###############################



packet_processing.o :
	$(COMPILE) $(BASE_DIR)/net/packet_processing.cc

base_values.o:
	$(COMPILE) $(LIB_DIR)/mylib/base/logic/base_values.cc

http_serializer.o:
	$(COMPILE) $(LIB_DIR)/mylib/base/logic/http_serializer.cc
	
json_serializer.o:
	$(COMPILE) $(LIB_DIR)/mylib/base/logic/json_serializer.cc
	
jsonp_serializer.o:
	$(COMPILE) $(LIB_DIR)/mylib/base/logic/jsonp_serializer.cc
		
logic_comm.o:
	$(COMPILE) $(LIB_DIR)/mylib/base/logic/logic_comm.cc
	
mig_log.o:
	$(COMPILE) $(LIB_DIR)/mylib/public/log/mig_log.cc

basic_util.o:
	$(COMPILE) $(LIB_DIR)/mylib/public/basic/basic_util.cc
	
core_interface.o:
	$(COMPILE) $(LIB_DIR)/mylib/public/comm/core_interface.cc
	
http_formate.o:
	$(COMPILE) $(LIB_DIR)/mylib/public/http/http_formate.cc
	
data_packet.o:
	$(COMPILE) $(LIB_DIR)/mylib/public/protocol/data_packet.cc

fcgimodule.o:
	$(COMPILE) $(BASE_DIR)/fcgimodule/fcgimodule.cc
