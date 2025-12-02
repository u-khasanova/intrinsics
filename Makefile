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
	@echo "Номер в группе $(STUDENT_NUMBER)"
	@echo "Используемая инструкция: _mm256_div_ps"
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(BUILD_DIR)/$(TARGET)
	@echo "Сборка завершена: $(BUILD_DIR)/$(TARGET)"
	@echo ""

run: $(BUILD_DIR)/$(TARGET)
	./$(BUILD_DIR)/$(TARGET)

clean:
	@echo "Очистка директории сборки..."
	rm -rf $(BUILD_DIR)

help:
	@echo "make all      - Собрать проект"
	@echo "make run      - Собрать и запустить демонстрацию"
	@echo "make clean    - Очистить директорию сборки"
	@echo "make help     - Показать это справочное сообщение"

.PHONY: all run info clean help