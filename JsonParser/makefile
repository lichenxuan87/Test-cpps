#This is cross platform make file. 
# To build on arm platform, please run "source env.sh" first.

CLIENT = jsonParser

CLIENT_SRC = main.cpp

CFLAGS +=  $(INC) -Wall -g
CXXFLAGS += $(CFLAGS) -std=c++11
LDFLAGS = -L$(SYSTEM_ROOT)/usr/lib/x86_64-linux-gnu -L$(SYSTEM_ROOT)/usr/lib \
			-Wl,-rpath-link,$(SYSTEM_ROOT)/usr/lib,-rpath-link,$(SYSTEM_ROOT)/lib -ljsoncpp

CLIENT_OBJ = $(patsubst %.cpp,%.o,$(CLIENT_SRC))


all : $(CLIENT)
	

$(CLIENT) :  $(CLIENT_OBJ)  
	$(CXX) $^ $(LDFLAGS)  -o $@ 


#.PHONY: clean
clean:
	rm -rf  $(CLIENT)
	rm -rf  $(CLIENT_OBJ)
