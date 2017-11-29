#This is cross platform make file. 
# To build on arm platform, please run "source env.sh" first.

CLIENT = vehicleProperty

CLIENT_SRC = main.c

CFLAGS +=  $(INC) -Wall -g
CXXFLAGS += $(CFLAGS)
LDFLAGS = -L$(SYSTEM_ROOT)/usr/lib/x86_64-linux-gnu -L$(SYSTEM_ROOT)/usr/lib \
			-Wl,-rpath-link,$(SYSTEM_ROOT)/usr/lib,-rpath-link,$(SYSTEM_ROOT)/lib

SERVER_OBJ = $(patsubst %.c,%.o,$(SERVER_SRC))
CLIENT_OBJ = $(patsubst %.c,%.o,$(CLIENT_SRC))

DBUS_GEN_OBJ = $(patsubst %.c,%.o,$(DBUS_GEN_SRC))

all : $(CLIENT)
	

$(CLIENT) :  $(CLIENT_OBJ)  
	$(CC) $^ $(LDFLAGS)  -o $@ 


#.PHONY: clean
clean:
	rm -rf  $(CLIENT)
	rm -rf  $(CLIENT_OBJ)
