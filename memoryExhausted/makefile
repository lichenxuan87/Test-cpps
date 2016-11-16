#This is cross platform make file. 
# To build on arm platform, please run "source env.sh" first.

CLIENT = memoryExhausted


CLIENT_SRC = memoryExhausted.cpp

PACKAGES += base glib-2.0

ifndef TARGET_ARC
	PKG_CONFIG = pkg-config
endif


INC = -I$(SYSTEM_ROOT)/usr/include \
		-I$(SYSTEM_ROOT)/usr/include/base \
        -I$(SYSTEM_ROOT)/usr/include/glib-2.0 \
        -I$(SYSTEM_ROOT)/usr/lib/glib-2.0/include

LB_INC = -L$(SYSTEM_ROOT)/usr/lib


CFLAGS += `$(PKG_CONFIG) --cflags $(PACKAGES)` $(INC) -Wall -Wextra -g
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

