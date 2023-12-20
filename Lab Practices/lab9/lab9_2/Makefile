SRC = $(wildcard ./*.cpp)
TARGET = test2
OBJ = $(patsubst %.cpp, %.o, $(SRC))
LIB = libfunctions.a
CXX = g++
.PHONY: liba testliba clean
liba: $(LIB)
$(LIB): $(OBJ)
	ar cr $@ $^

%.o: %.cpp
	$(CXX) -c $<

testliba: $(TARGET)
$(TARGET): test.cpp
	g++ $^ -L. -lfunctions -o $@

clean:
	rm -f *.o $(TARGET) $(LIB)

