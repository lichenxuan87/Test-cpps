#This is cross platform make file. 
# To build on arm platform, please run "source env.sh" first.

CLIENT = verifyCTL

CLIENT_SRC = main.cpp

INC = -I/usr/include -I/usr/include/c++/5.4.0

LB_INC = -L/usr/lib  -lssl -lcrypto -ljsoncpp


CFLAGS +=  $(INC) -Wall -g
CXXFLAGS += $(CFLAGS) 
LDFLAGS +=  $(LB_INC) \
            -Wl,-rpath-link,/usr/lib

#OBJS = $(patsubst %.cpp,%.o,$(SRC))
CLIENT_COBJS = $(patsubst %.cpp,%.o,$(CLIENT_SRC))

all :$(CLIENT)
	
$(CLIENT) : $(CLIENT_COBJS)
	$(CXX) $^ $(LDFLAGS)  -o $@ 


#.PHONY: clean
clean:
	rm -rf $(CLIENT)
	rm -rf $(CLIENT_COBJS)
