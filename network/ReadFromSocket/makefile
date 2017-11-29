#This is cross platform make file. 
# To build on arm platform, please run "source env.sh" first.

CLIENT = client
SERVER = server

CLIENT_SRC = client.cpp
SERVER_SRC = server.cpp

CFLAGS +=  $(INC) -Wall -g
CXXFLAGS += $(CFLAGS) -std=c++11
LDFLAGS = -L$(SYSTEM_ROOT)/usr/lib/x86_64-linux-gnu -L$(SYSTEM_ROOT)/usr/lib \
			-Wl,-rpath-link,$(SYSTEM_ROOT)/usr/lib,-rpath-link,$(SYSTEM_ROOT)/lib

SERVER_OBJ = $(patsubst %.cpp,%.o,$(SERVER_SRC))
CLIENT_OBJ = $(patsubst %.cpp,%.o,$(CLIENT_SRC))

DBUS_GEN_OBJ = $(patsubst %.c,%.o,$(DBUS_GEN_SRC))

all : $(CLIENT) $(SERVER)
	

$(CLIENT) :  $(CLIENT_OBJ)  
	$(CXX) $^ $(LDFLAGS)  -o $@ 

$(SERVER) :  $(SERVER_OBJ)  
	$(CXX) $^ $(LDFLAGS)  -o $@ 

#.PHONY: clean
clean:
	rm -rf  $(CLIENT)
	rm -rf  $(CLIENT_OBJ)
