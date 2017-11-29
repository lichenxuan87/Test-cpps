#This is cross platform make file. 
# To build on arm platform, please run "source env.sh" first.

SERVER = test
CLIENT = testClient


SERVER_SRC = test.cpp
CLIENT_SRC = testClient.cpp

DBUS_GEN_SRC =	com.saic.ivi.test.xml.c
DBUS_GEN_HEADER = com.saic.ivi.test.xml.h

XML = com.saic.ivi.test.xml

ifeq ($(TARGET_ARC), arm)
	CFLAGS += -DARM
endif

INC = -I$(SYSTEM_ROOT)/usr/include \
	-I$(SYSTEM_ROOT)/usr/include/glib-2.0 \
	-I$(SYSTEM_ROOT)/usr/lib/glib-2.0/include \
	-I$(SYSTEM_ROOT)/usr/lib/x86_64-linux-gnu/glib-2.0/include \
	-I$(SYSTEM_ROOT)/usr/include/gio-unix-2.0 


CFLAGS +=  $(INC) -Wall -g
CXXFLAGS += $(CFLAGS) -std=c++11
LDFLAGS = -L$(SYSTEM_ROOT)/usr/lib/x86_64-linux-gnu -L$(SYSTEM_ROOT)/usr/lib \
			-lglib-2.0 -lgio-2.0 -lgobject-2.0 -lrt -pthread \
			-Wl,-rpath-link,$(SYSTEM_ROOT)/usr/lib,-rpath-link,$(SYSTEM_ROOT)/lib

SERVER_OBJ = $(patsubst %.cpp,%.o,$(SERVER_SRC))
CLIENT_OBJ = $(patsubst %.cpp,%.o,$(CLIENT_SRC))

DBUS_GEN_OBJ = $(patsubst %.c,%.o,$(DBUS_GEN_SRC))

all :$(SERVER) $(CLIENT)
	
$(SERVER) : $(DBUS_GEN_OBJ) $(SERVER_OBJ)  
	$(CXX) $^ $(LDFLAGS)  -o $@ 

$(CLIENT) : $(DBUS_GEN_OBJ) $(CLIENT_OBJ)  
	$(CXX) $^ $(LDFLAGS)  -o $@ 

$(DBUS_GEN_SRC) : $(XML)
	gdbus-codegen --generate-c-code $(XML) $(XML)
	
$(DBUS_GEN_OBJ) : $(DBUS_GEN_SRC) 


#.PHONY: clean
clean:
	rm -rf $(SERVER) $(CLIENT)
	rm -rf $(DBUS_GEN_SRC) $(DBUS_GEN_HEADER) $(DBUS_GEN_OBJ)
	rm -rf $(SERVER_OBJ) $(CLIENT_OBJ)
