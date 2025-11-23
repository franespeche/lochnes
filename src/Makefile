CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -I.
TARGET = out

SOURCES = main.cpp \
          core/ram.cpp core/rom.cpp core/bus.cpp core/cpu6502.cpp core/clock.cpp \
          system/system.cpp \
          utils/utils.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = common/types.h \
          core/ram.h core/rom.h core/bus.h core/cpu6502.h core/clock.h \
          system/system.h \
          utils/utils.h

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: run clean
