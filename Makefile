# compiler settings
CXX = g++
CXXFLAGS = -Wall -std=c++11

# general variables
TARGET = main
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)

# Default target
all: $(TARGET)

# compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# cleanup
.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)

