#This is cross platform make file. 
# To build on arm platform, please run "source env.sh" first.

TARGET = main

TARGET_SRC = main.cpp

INC = -I/usr/local/include \
      -I.


CFLAGS +=  $(INC) -Wall -g
CXXFLAGS += $(CFLAGS) -std=c++14

#LDFLAGS += $(shell pkg-config --libs --static opencv)
LDFLAGS += -L/usr/local/lib -L/usr/lib \
		   -L/usr/lib/x86_64-linux-gnu \
            -lglut -lGL -lGLU -lrt -pthread \
            -Wl,-rpath-link,/usr/lib,-rpath-link,/usr/local/lib,-rpath-link,/usr/lib/x86_64-linux-gnu

TARGET_OBJ = $(patsubst %.cpp,build/%.o,$(TARGET_SRC))

all :$(TARGET)
    
$(TARGET) : $(TARGET_OBJ)  
	$(CXX) $^ $(LDFLAGS)  -o $@ 

build/%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

#.PHONY: clean
clean:
	rm -rf $(TARGET)
	rm -rf $(TARGET_OBJ)