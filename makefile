# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -g $(shell pkg-config --cflags raylib)
LDFLAGS = $(shell pkg-config --libs raylib)

# Directories
SRC_DIR = src
BUILD_DIR = build
TEST_DIR = test

# Files
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/chip8.c $(SRC_DIR)/debug.c $(SRC_DIR)/instructions.c $(SRC_DIR)/screen.c $(SRC_DIR)/keypad.c $(SRC_DIR)/logger.c
OBJS = $(SRCS:.c=.o)
EXEC = $(BUILD_DIR)/chip8

# Test Files
TEST_SRCS = $(TEST_DIR)/test_chip8.c
TEST_EXEC = $(BUILD_DIR)/test_chip8

# Default Target
all: $(EXEC)

# Build Executable
$(EXEC): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	# Remove .o files after building
	rm -f $(OBJS)

# Clean Build Artifacts
clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(OBJS)

# Run Test
test: $(TEST_EXEC)
	./$(TEST_EXEC)
	echo
	rm -rf $(OBJS)	

# Build Test Executable
$(TEST_EXEC): $(TEST_SRCS) $(SRC_DIR)/chip8.o $(SRC_DIR)/debug.o $(SRC_DIR)/instructions.o $(SRC_DIR)/keypad.o $(SRC_DIR)/logger.o
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Build Target
build: $(EXEC)

# Build Object Files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean run test
