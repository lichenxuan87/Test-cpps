TARGET = shareMemory

SRC = shareMemory.cpp

CXXFLAGS += -std=c++11 -g
LDFLAGS += -lrt -pthread

#OBJS = $(patsubst %.cpp,%.o,$(SRC))
#COBJS = $(patsubst %.c,%.o,$(CSRC))
	
$(TARGET) : $(SRC)
	$(CXX) $(CFLAGS) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

#all :$(TARGET)

#.PHONY: clean
clean:
	rm -rf $(TARGET)