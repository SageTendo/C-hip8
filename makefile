# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -g $(shell pkg-config --cflags raylib)
LDFLAGS = $(shell pkg-config --libs raylib)

# Directories
SRC_DIR = src
BUILD_DIR = build

# Files
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/chip8.c $(SRC_DIR)/debug.c $(SRC_DIR)/instructions.c $(SRC_DIR)/screen.c $(SRC_DIR)/keypad.c $(SRC_DIR)/logger.c
OBJS = $(SRCS:.c=.o)
EXEC = $(BUILD_DIR)/chip8

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

# Build Target
build: $(EXEC)

# Run Emulator with ROM file
run: $(EXEC)
	@echo "Running CHIP-8 emulator with ROM file: $(ROM_FILE)"
	./$(EXEC) $(ROM_FILE)

# Build Object Files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean run
