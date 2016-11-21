#This is cross platform make file. 
# To build on arm platform, please run "source env.sh" first.

CLIENT = kDbusClient

SERVER = kDbusServer

all : $(CLIENT) $(SERVER)

CLIENT_SRC = client/clientMain.cpp \
			 client/CProxyExample.cpp \
			 client/DbusClientExample.cpp
			 
SERVER_SRC = server/serverMain.cpp \
			 server/CAdaptorExample.cpp \
			 server/DbusServerExample.cpp

INC = -I$(SYSTEM_ROOT)/usr/include \
	  -I$(SYSTEM_ROOT)/usr/include/base \
	  -I. 

LB_INC = -L$(SYSTEM_ROOT)/usr/lib

CFLAGS +=  $(INC)
CXXFLAGS += $(CFLAGS) 
LDFLAGS += -lbase \
             $(LB_INC) \
            -Wl,-rpath-link,$(SYSTEM_ROOT)/usr/lib,-rpath-link,$(SYSTEM_ROOT)/lib

CLIENT_OBJS = $(patsubst %.cpp,%.o,$(CLIENT_SRC))
SERVER_OBJS = $(patsubst %.cpp,%.o,$(SERVER_SRC))

	
$(CLIENT) : $(CLIENT_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

$(SERVER) : $(SERVER_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@


#.PHONY: clean
clean:
	rm -rf $(CLIENT) $(SERVER) $(CLIENT_OBJS) $(SERVER_OBJS)

