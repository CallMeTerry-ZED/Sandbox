# /*
#  * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
#  */

# Build directory
BUILD_DIR := build
CMAKE_DIR := cmake

# Default build type
BUILD_TYPE ?= Release

.PHONY: config build run clean debug debug-build debug-run

config:
	@echo "Configuring CMake..."
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) ../$(CMAKE_DIR)

build: config
	@echo "Building project..."
	@cd $(BUILD_DIR) && cmake --build . --config $(BUILD_TYPE)

run: build
	@echo "Running Sandbox..."
	@./$(BUILD_DIR)/bin/Sandbox

debug-build:
	@echo "Configuring and building Debug..."
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Debug ../$(CMAKE_DIR)
	@cd $(BUILD_DIR) && cmake --build . --config Debug

debug-run: debug-build
	@echo "Running Sandbox (Debug)..."
	@./$(BUILD_DIR)/bin/Sandbox

clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)

