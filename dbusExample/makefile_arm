#This is cross platform make file. 
# To build on arm platform, please run "source env.sh" first.

CLIENT = test


CLIENT_SRC = test.cpp



INC = -I$(SYSTEM_ROOT)/usr/include -I$(SYSTEM_ROOT)/usr/include/base \
	-I$(SYSTEM_ROOT)/usr/include/glib-2.0 \
	-I$(SYSTEM_ROOT)/usr/lib/glib-2.0/include 

LB_INC = -L$(SYSTEM_ROOT)/usr/lib -lgio-2.0 -lglib-2.0 -lgobject-2.0


CFLAGS +=  $(INC) -Wall -Werror -std=c++11
CXXFLAGS += $(CFLAGS) 
LDFLAGS +=  $(LB_INC) \
            -Wl,-rpath-link,$(SYSTEM_ROOT)/usr/lib,-rpath-link,$(SYSTEM_ROOT)/lib

#OBJS = $(patsubst %.cpp,%.o,$(SRC))
#COBJS = $(patsubst %.c,%.o,$(CSRC))

all :$(CLIENT)
	
$(CLIENT) : $(CLIENT_SRC)



#.PHONY: clean
clean:
	rm -rf $(CLIENT)