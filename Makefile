TARGET_EXEC := my_blockchain
BUILD_DIR := ./build
SRC_DIRS := ./src
INCLUDE_DIR := ./include
CC = gcc
CFLAGS += -I $(INCLUDE_DIR)

# Find all the C files we want to compile
SRCS := $(wildcard $(SRC_DIRS)/*.c)

# Prepends BUILD_DIR and appends .o to every src file
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# The final build step.
$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)
