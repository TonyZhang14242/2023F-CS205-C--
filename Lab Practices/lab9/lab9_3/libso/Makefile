OBJS = $(patsubst %.cpp, %.o, $(wildcard ./*.cpp))
TARGET = libdynamic.so
CXX = g++
DYN = -shared -fPIC

$(TARGET):$(OBJS)
	$(CXX) $(DYN) $^ -o $@

	sudo cp $(TARGET) /usr/lib/

%.o:%.cpp
	$(CXX) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
	sudo rm -f /usr/lib/$(TARGET)

