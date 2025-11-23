CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
TARGET = out

SOURCES = main.cpp ram.cpp rom.cpp bus.cpp cpu6502.cpp clock.cpp system.cpp utils/utils.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = types.h ram.h rom.h bus.h cpu6502.h clock.h system.h

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: run clean
