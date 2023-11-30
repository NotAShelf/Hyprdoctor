CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = Hyprdoctor
SRCS = main.cpp src/utils/environment.cpp src/utils/file_parser.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET);

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
run:
	./$(TARGET)

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
