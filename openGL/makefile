#This is cross platform make file. 
# To build on arm platform, please run "source env.sh" first.

CLIENT = texturedCube

SRC = texturedCube.cpp \
	   common/shader.cpp \
	   common/texture.cpp

INC = -I/usr/include \
	  -I/usr/local/include \
	  -I.

LB_INC = -L$(SYSTEM_ROOT)/usr/lib -L/usr/lib/x86_64-linux-gnu/ -L/usr/local/lib  -lglut -lGL -lGLEW -lglfw


CFLAGS +=  $(INC) -Wall 
CXXFLAGS += $(CFLAGS) 
LDFLAGS +=  $(LB_INC) \
            -Wl,-rpath-link,/usr/local/lib \
            -Wl,-rpath-link,$(SYSTEM_ROOT)/usr/lib \
            -Wl,-rpath-link,$(SYSTEM_ROOT)/lib 

OBJS = $(patsubst %.cpp,%.o,$(SRC))
#COBJS = $(patsubst %.cc,%.o,$(CSRC))

all :$(CLIENT)
	
$(CLIENT) : $(OBJS)
	$(CXX) $^ $(LDFLAGS)  -o $@

%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

#.PHONY: clean
clean:
	rm -rf $(CLIENT)
	rm -rf $(OBJS)