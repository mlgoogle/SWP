OUT_PUT = ${SO_DIR}/login/login.so 

SRC_DIR = ../../
LIB_DIR = ./../../../baselib
THIRD_PATH = $(LIB_DIR)/third_party
SRC_PLUGINS = ${SRC_DIR}/plugins
SO_DIR = ${SRC_DIR}/bin/plugins
SRC_PUB = ${SRC_DIR}/pub
SRC_PUB_NET = ${SRC_PUB}/net
SRC_PUB_UTIL = ${SRC_PUB}/util
SRC_PUB_STORAGE = ${SRC_PUB}/storage
SRC_PUB_SHARE = ${SRC_PUB}/share
SRC_PUB_COMM = ${SRC_PUB}/comm
SRC_PUB_PAY = ${SRC_PUB}/pay
SO_DIR = ${SRC_DIR}bin/plugins
SRC_PUB_NET = ${SRC_DIR}pub/net
SRC_PUB_UTIL = ${SRC_DIR}pub/util
SRC_PUB_STORAGE = ${SRC_DIR}pub/storage
SRC_PUB_SHARE = ${SRC_DIR}pub/share
SRC_PUB_COMM = ${SRC_DIR}pub/comm

LINK_DYNAMIC = -Wl,-Bdynamic -lpthread
LINK_STATIC = -Wl,-Bstatic -L${LIB_DIR}/third_party/glog/lib/libglog.a
LINK_PATH = -L/usr/lib64/mysql

CXXFLAGS += -g -Wextra -w -shared -fPIC 

INCLUDE_PATHS = -I${LIB_DIR} \
		-I${SRC_PLUGINS} \
		-I${SRC_DIR} \
		-I${SRC_PUB} \
		-I${LIB_DIR}/public \
		-I${LIB_DIR}/base \
    -I$(THIRD_PATH) \
		-I$(THIRD_PATH)/glog/include \
		-I$(THIRD_PATH)/gtpush/include \
		-I${LIB_DIR}/public \
		-I${LIB_DIR}/base \
		-I${LIB_DIR}/third_party/glog/include

all : ${OUT_PUT} del-temp-files

del-temp-files:
	rm -rf *.o
	
clean :
	rm -f ${OUT_PUT}  del-temp-files
	
login_init.o : ./login_init.cc  ./login_init.h
	${CXX} ${CXXFLAGS} -c ./login_init.cc ${INCLUDE_PATHS}

login_logic.o : ./login_logic.cc  ./login_logic.h
	${CXX} ${CXXFLAGS} -c ./login_logic.cc ${INCLUDE_PATHS}

#proto_buf.o : ./proto_buf.cc  ./proto_buf.h
#	${CXX} ${CXXFLAGS} -c ./proto_buf.cc ${INCLUDE_PATHS}

login_mysql.o : ./login_mysql.cc  ./login_mysql.h
	${CXX} ${CXXFLAGS} -c ./login_mysql.cc ${INCLUDE_PATHS}

login_proto.o : ./login_proto.cc  #./login_proto.h
	${CXX} ${CXXFLAGS} -c ./login_proto.cc ${INCLUDE_PATHS}

util.o : ${SRC_PUB_UTIL}/util.cc  ${SRC_PUB_UTIL}/util.h
	${CXX} ${CXXFLAGS} -c ${SRC_PUB_UTIL}/util.cc ${INCLUDE_PATHS}

logic_unit.o :  $(SRC_PUB)/logic/logic_unit.cc $(SRC_PUB)/logic/logic_unit.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(SRC_PUB)/logic/logic_unit.cc $(INCLUDE_PATHS)

packet_processing.o :  $(SRC_PUB)/net/packet_processing.cc $(SRC_PUB)/net/packet_processing.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(SRC_PUB)/net/packet_processing.cc $(INCLUDE_PATHS)

data_engine.o : ${SRC_PUB_STORAGE}/data_engine.cc  ${SRC_PUB_STORAGE}/data_engine.h
	${CXX} ${CXXFLAGS} -c ${SRC_PUB_STORAGE}/data_engine.cc ${INCLUDE_PATHS}

mysql_pool.o : ${SRC_PUB_STORAGE}/mysql_pool.cc  ${SRC_PUB_STORAGE}/mysql_pool.h
	${CXX} ${CXXFLAGS} -c ${SRC_PUB_STORAGE}/mysql_pool.cc ${INCLUDE_PATHS}

data_mysql_engine.o : ${SRC_PUB_STORAGE}/data_mysql_engine.cc  ${SRC_PUB_STORAGE}/data_mysql_engine.h
	${CXX} ${CXXFLAGS} -c ${SRC_PUB_STORAGE}/data_mysql_engine.cc ${INCLUDE_PATHS}

data_redis_engine.o :  $(SRC_PUB_STORAGE)/data_redis_engine.cc $(SRC_PUB_STORAGE)/data_redis_engine.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(SRC_PUB_STORAGE)/data_redis_engine.cc $(INCLUDE_PATHS)

user_info.o : ${SRC_PUB_COMM}/user_info.cc  ${SRC_PUB_COMM}/user_info.h 
	${CXX} ${CXXFLAGS} -c ${SRC_PUB_COMM}/user_info.cc ${INCLUDE_PATHS}

data_share_mgr.o : ${SRC_PUB_SHARE}/data_share_mgr.cc  ${SRC_PUB_SHARE}/data_share_mgr.h 
	${CXX} ${CXXFLAGS} -c ${SRC_PUB_SHARE}/data_share_mgr.cc ${INCLUDE_PATHS}

#${OUT_PUT} : login_init.o login_logic.o login_mysql.o login_proto.o util.o\
#		logic_unit.o packet_processing.o data_engine.o mysql_pool.o data_mysql_engine.o data_redis_engine.o

data_mysql_engine.o : ${SRC_PUB_STORAGE}/data_mysql_engine.cc  ${SRC_PUB_STORAGE}/data_mysql_engine.h
	${CXX} ${CXXFLAGS} -c ${SRC_PUB_STORAGE}/data_mysql_engine.cc ${INCLUDE_PATHS}

#${OUT_PUT} : login_init.o login_logic.o proto_buf.o login_mysql.o login_proto.o\
		data_mysql_engine.o

${OUT_PUT} : login_init.o login_logic.o login_mysql.o login_proto.o util.o\
		logic_unit.o packet_processing.o data_engine.o mysql_pool.o data_mysql_engine.o \
		data_redis_engine.o user_info.o data_share_mgr.o 
	${CXX} ${CXXFLAGS} $^ -o ${OUT_PUT} ${LINK_PATH} -lpthread -lmysqlclient -lcurl \
		${LIB_DIR}/third_party/glog/lib/libglog.a ${LIB_DIR}/base/lib/mybase.a \
		${LIB_DIR}/third_party/dmg_fp/lib/dmg_fp.a -lexpat
