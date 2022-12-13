CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -g3 -fsanitize=address
SRCS := $(wildcard *.c)
SRCS := $(filter-out test_blockchain.c, $(SRCS))
BINS := $(SRCS:%.c=%)
OBJFILES := $(BINS:%=%.o)
TARGET = my_blockchain

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -rvf $(OBJFILES)

fclean: clean
	rm -f my_blockchain
	rm -f test_blockchain

re: all clean