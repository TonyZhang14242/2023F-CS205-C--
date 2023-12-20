OBJS = $(patsubst %.cpp, %.o, $(wildcard ./*.cpp))
TARGET = test3
CXX = g++

LDFLAGE = -L./libso
LIB = -ldynamic

$(TARGET):$(OBJS)
	$(CXX) $^ $(LIB) $(LDFLAGE) -o $@

%.o:%.cpp
	$(CXX) -c $< -o $@

clean:
	rm -f *.o $(TARGET)