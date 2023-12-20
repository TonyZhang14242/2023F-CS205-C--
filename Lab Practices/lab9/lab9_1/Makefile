SRC = $(wildcard ./*.cpp)
TARGET = test1
OBJ = $(patsubst %.cpp, %.o, $(SRC))

CXX = g++
$(TARGET): $(OBJ)
	$(CXX) -o $@ $(OBJ)
%.o: %.cpp
	$(CXX) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o $(TARGET)