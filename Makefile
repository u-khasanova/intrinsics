CXX = g++
CXXFLAGS = -mavx2 -O3 -Wall -Wextra -std=c++17
TARGET = demo_avx
STUDENT_NUMBER = 61
SRC_DIR = src
BUILD_DIR = build
SOURCE = $(SRC_DIR)/demo_mm256_div_ps.cpp

$(shell mkdir -p $(BUILD_DIR))

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(SOURCE)
	@echo "Student $(STUDENT_NUMBER)"
	@echo "Using instruction: _mm256_div_ps"
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(BUILD_DIR)/$(TARGET)
	@echo "Build complete: $(BUILD_DIR)/$(TARGET)"
	@echo ""

run: $(BUILD_DIR)/$(TARGET)
	./$(BUILD_DIR)/$(TARGET)

clean:
	@echo "Cleaning build directory..."
	rm -rf $(BUILD_DIR)

help:
	@echo "make all      - Build the project"
	@echo "make run      - Build and run the demo"
	@echo "make clean    - Clean build directory"
	@echo "make help     - Show this help message"

.PHONY: all run info clean help