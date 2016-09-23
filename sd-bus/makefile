#This is cross platform make file. 
# To build on arm platform, please run "source env.sh" first.

CLIENT = basicSdbus
SERVER = dbusServer

CLIENT_SRC = basicSdbus.cpp
SERVER_SRC = dbusServer.c

PACKAGES += libsystemd

ifndef $(TARGET_ARCH)
	PKG_CONFIG = pkg-config
endif


INC = -I$(SYSTEM_ROOT)/usr/include

LB_INC = -L$(SYSTEM_ROOT)/usr/lib


CFLAGS += `$(PKG_CONFIG) --cflags $(PACKAGES)` $(INC)
CXXFLAGS += $(CFLAGS) 
LDFLAGS += `$(PKG_CONFIG) --libs $(PACKAGES)` \
             $(LB_INC) \
            -Wl,-rpath-link,$(SYSTEM_ROOT)/usr/lib,-rpath-link,$(SYSTEM_ROOT)/lib

#OBJS = $(patsubst %.cpp,%.o,$(SRC))
#COBJS = $(patsubst %.c,%.o,$(CSRC))

all :$(CLIENT) $(SERVER)
	
$(CLIENT) : $(CLIENT_SRC)
$(SERVER) : $(SERVER_SRC)



#.PHONY: clean
clean:
	rm -rf $(CLIENT) $(SERVER)

