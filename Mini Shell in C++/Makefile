CXX     := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
LDFLAGS  := -lreadline

TARGET  := mysh
SRCS    := main.cpp shell.cpp executor.cpp parser.cpp managers.cpp
OBJS    := $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp shell.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
