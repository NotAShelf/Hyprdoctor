CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = Hyprdoctor
SRCS = main.cpp src/utils/environment.cpp src/utils/file_parser.cpp src/utils/json_parser.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lboost_program_options

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run:
	./$(TARGET)

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
