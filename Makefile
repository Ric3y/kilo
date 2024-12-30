# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99

# Source and build directories
SRC = kilo.c
BUILD_DIR = build
TARGET = $(BUILD_DIR)/kilo

# Default rule
all: $(TARGET)

# Build rule
$(TARGET): $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean rule to remove build artifacts
clean:
	rm -rf $(BUILD_DIR)

