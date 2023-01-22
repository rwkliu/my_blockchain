#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"
#include "helpers.h"
#include "status.h"

void block(BlockchainPtr blockchain, string_array *split_read_buffer, char *arg) {
  printf("block function reached\n");
}

void node(BlockchainPtr blockchain, string_array *split_read_buffer, char *arg) {
  printf("node function reached\n");
}

void add(BlockchainPtr blockchain, string_array *split_read_buffer) {
  printf("add\n");
  void (*args[])(BlockchainPtr, string_array *, char *) = {block, node};
  char *arg_strings[] = {"block", "node"};
  char *add_arg = split_read_buffer->array[1];
  int i = 0;

  while (i < 2) {
    if (add_arg != NULL && strcmp(arg_strings[i], add_arg) == 0) {
      (*args[i])(blockchain, split_read_buffer, "add"); 
      break;
    }
    i++;
  }
  if (i == 2) {
    printf(NO_COMMAND_FOUND);
  }
}

void remove_(BlockchainPtr blockchain, string_array *split_read_buffer) {
  printf("remove\n");
  void (*args[])(BlockchainPtr, string_array *, char *) = {block, node};
  char *arg_strings[] = {"block", "node"};
  char *add_arg = split_read_buffer->array[1];
  int i = 0;

  while (i < 2) {
    if (add_arg != NULL && strcmp(arg_strings[i], add_arg) == 0) {
      (*args[i])(blockchain, split_read_buffer, "remove"); 
      break;
    }
    i++;
  }
  if (i == 2) {
    printf(NO_COMMAND_FOUND);
  }
}

void list(BlockchainPtr blockchain, string_array *split_read_buffer) {
  char *lflag = split_read_buffer->array[1];
  char *subsequent_args = split_read_buffer->array[2];

  if (split_read_buffer->array[2] != NULL) {
    printf(NO_COMMAND_FOUND);
  } else if (lflag != NULL && strncmp(lflag, "-l", 2) == 0 && subsequent_args == NULL) {
    blockchain->ls(&(blockchain->blockchain_head), PRINT_BID);
  } else if (lflag == NULL) {
    blockchain->ls(&(blockchain->blockchain_head), NO_BID);
  }
}

void sync(BlockchainPtr blockchain, string_array *split_read_buffer) {
  printf("sync\n");
}

void quit(BlockchainPtr blockchain, string_array *split_read_buffer) {
  printf("quit\n");
}

void execute_command(BlockchainPtr blockchain, string_array *split_read_buffer) {
  void (*command[])(BlockchainPtr, string_array *) 
    = {add, remove_, list, sync, quit};
  char *command_strings[] = {"add", "rm", "ls", "sync", "quit"};
  char *command_arg = split_read_buffer->array[0];
  int i = 0;

  while (i < 5) {
    if (strcmp(command_strings[i], command_arg) == 0) {
      (*command[i])(blockchain, split_read_buffer);
      break;
    }
    i++;
  }

  if (i == 5) {
    printf(NO_COMMAND_FOUND);
  }
}
