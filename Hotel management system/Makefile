CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

TARGET = hotel_system
SRCS = main.cpp Person.cpp Guest.cpp Employee.cpp Room.cpp Service.cpp Booking.cpp Bill.cpp Hotel.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = Person.h Guest.h Employee.h Room.h Service.h Booking.h Bill.h Hotel.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "✓ Build successful! Run with: ./$(TARGET)"

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	@echo "✓ Cleaned build files"

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
