#This is cross platform make file. 
# To build on arm platform, please run "source env.sh" first.

CLIENT = aliDbus


CLIENT_SRC = aliDbus.cpp

PACKAGES += base

ifndef TARGET_ARC
	PKG_CONFIG = pkg-config
endif


INC = -I$(SYSTEM_ROOT)/usr/include -I$(SYSTEM_ROOT)/usr/include/base

LB_INC = -L$(SYSTEM_ROOT)/usr/lib


CFLAGS += `$(PKG_CONFIG) --cflags $(PACKAGES)` $(INC)
CXXFLAGS += $(CFLAGS) 
LDFLAGS += `$(PKG_CONFIG) --libs $(PACKAGES)` \
             $(LB_INC) \
            -Wl,-rpath-link,$(SYSTEM_ROOT)/usr/lib,-rpath-link,$(SYSTEM_ROOT)/lib

#OBJS = $(patsubst %.cpp,%.o,$(SRC))
#COBJS = $(patsubst %.c,%.o,$(CSRC))

all :$(CLIENT)
	
$(CLIENT) : $(CLIENT_SRC)



#.PHONY: clean
clean:
	rm -rf $(CLIENT)

