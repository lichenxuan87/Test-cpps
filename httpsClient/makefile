#This is cross platform make file. 
# To build on arm platform, please run "source env.sh" first.

CLIENT = httpsClient

CLIENT_SRC = httpsClient.cpp

INC = -I$(SYSTEM_ROOT)/usr/include -I/usr/local/include  -I$(SYSTEM_ROOT)/usr/include/base 

LB_INC = -L$(SYSTEM_ROOT)/usr/lib -L$(SYSTEM_ROOT)/lib -L/usr/local/lib  -lPocoNet -lPocoFoundation -lPocoNetSSL -lcrypto -lssl


CFLAGS +=  $(INC) -Wall -Werror
CXXFLAGS += $(CFLAGS) 
LDFLAGS +=  $(LB_INC) \
            -Wl,-rpath-link,/usr/local/lib \
            -Wl,-rpath-link,$(SYSTEM_ROOT)/usr/lib \
            -Wl,-rpath-link,$(SYSTEM_ROOT)/lib 

#OBJS = $(patsubst %.cpp,%.o,$(SRC))
#COBJS = $(patsubst %.c,%.o,$(CSRC))

all :$(CLIENT)
	
$(CLIENT) : $(CLIENT_SRC)



#.PHONY: clean
clean:
	rm -rf $(CLIENT)