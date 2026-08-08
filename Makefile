BUILD_DIR := build
TARGET := Screenwriter

.PHONY: all configure build run clean rebuild

all: run

configure:
	cmake -S . -B $(BUILD_DIR)

$(BUILD_DIR)/Makefile:
	cmake -S . -B $(BUILD_DIR)

build: $(BUILD_DIR)/Makefile
	cmake --build $(BUILD_DIR)

run: build
	./$(BUILD_DIR)/$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean run
