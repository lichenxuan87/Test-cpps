#This is cross platform make file. 
# To build on arm platform, please run "source env.sh" first.

CLIENT = verifyCert

CLIENT_SRC = main.c

INC = -I/usr/include  

LB_INC = -L/usr/lib  -lssl -lcrypto


CFLAGS +=  $(INC) -Wall
CXXFLAGS += $(CFLAGS) 
LDFLAGS +=  $(LB_INC) \
            -Wl,-rpath-link,/usr/lib

#OBJS = $(patsubst %.cpp,%.o,$(SRC))
CLIENT_COBJS = $(patsubst %.c,%.o,$(CLIENT_SRC))

all :$(CLIENT)
	
$(CLIENT) : $(CLIENT_COBJS)
	$(CC) $^ $(LDFLAGS)  -o $@ 


#.PHONY: clean
clean:
	rm -rf $(CLIENT)
	rm -rf $(CLIENT_COBJS)
