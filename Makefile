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
	rm my_blockchain
	rm test_blockchain

re: all clean

debug: $(TARGET)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

test_blockchain: test_blockchain.o blockchain.o node.o block.o helpers.o arguments_blockchain.o 
	gcc -o test_blockchain test_blockchain.o blockchain.o node.o block.o helpers.o arguments_blockchain.o $(CFLAGS) $(LDFLAGS)
