CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -pedantic-errors \
         -Wformat -Wformat-security -Wuninitialized -Wshadow \
         -Wsign-compare -Wmissing-field-initializers -Iinclude

SRC_DIR = src
BUILD_DIR = build
DATA_DIR = data
APP_DIR = $(SRC_DIR)/app
DB_DIR = $(SRC_DIR)/database

SRCS = $(APP_DIR)/app.c $(APP_DIR)/utilities.c $(DB_DIR)/db.c $(SRC_DIR)/main.c
OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRCS)))

TARGET = $(BUILD_DIR)/phonebook

all: setup $(TARGET)

setup:
	@mkdir -p $(BUILD_DIR) $(DATA_DIR)

$(BUILD_DIR)/%.o: $(APP_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(DB_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

run: all
	@$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(DATA_DIR)

.PHONY: all setup run clean

# CC = gcc
# CFLAGS = -Wall -Werror -Wextra -Wpedantic -pedantic-errors \
#          -Wformat -Wformat-security -Wuninitialized -Wshadow \
#          -Wsign-compare  -Wmissing-field-initializers

# # Directories
# SRC_DIR = src
# BUILD_DIR = build
# DATA_DIR = data
# APP_DIR = $(SRC_DIR)/app
# DB_DIR = $(SRC_DIR)/database

# # Source and object files
# SRCS = $(APP_DIR)/app.c $(APP_DIR)/utilities.c $(DB_DIR)/db.c $(SRC_DIR)/main.c
# OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRCS)))

# # Target executable
# TARGET = $(BUILD_DIR)/phonebook

# # Default rule
# all: setup $(TARGET)

# # Create necessary directories
# setup:
# 	@mkdir -p $(BUILD_DIR) $(DATA_DIR)

# # Build object files
# $(BUILD_DIR)/%.o: $(APP_DIR)/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(BUILD_DIR)/%.o: $(DB_DIR)/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(BUILD_DIR)/main.o: $(SRC_DIR)/main.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# # Link the target executable
# $(TARGET): $(OBJS)
# 	$(CC) $(OBJS) -o $(TARGET)

# # Clean up build and data folders
# clean:
# 	rm -rf $(BUILD_DIR) $(DATA_DIR)

# # Phony targets
# .PHONY: all setup run clean
