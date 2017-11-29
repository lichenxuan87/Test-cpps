#This is cross platform make file. 
# To build on arm platform, please run "source env.sh" first.

CLIENT = dumpKey

CLIENT_SRC = main.c

INC = -I$(SYSTEM_ROOT)/usr/include  

LB_INC = -L$(SYSTEM_ROOT)/usr/lib -L$(SYSTEM_ROOT)/lib -lssl -lcrypto


C_FLAGS_64 := -DBIT_64

CFLAGS += $(C_FLAGS_$(ARCH)) $(INC) -Wall -g
CXXFLAGS += $(CFLAGS) 
LDFLAGS +=  $(LB_INC) \
            -Wl,-rpath-link,$(SYSTEM_ROOT)/usr/lib

#OBJS = $(patsubst %.cpp,%.o,$(SRC))
CLIENT_COBJS = $(patsubst %.c,%.o,$(CLIENT_SRC))

all :$(CLIENT)
	
$(CLIENT) : $(CLIENT_COBJS)
	$(CXX) $^ $(LDFLAGS)  -o $@ 


#.PHONY: clean
clean:
	rm -rf $(CLIENT)
	rm -rf $(CLIENT_COBJS)
