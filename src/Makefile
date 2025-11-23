CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
TARGET = out
SOURCE = nes.cpp

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean
