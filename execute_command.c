#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"
#include "helpers.h"
#include "status.h"

void add(BlockchainPtr blockchain, string_array *split_read_buffer) {
  printf("add\n");
}

void remove_(BlockchainPtr blockchain, string_array *split_read_buffer) {
  printf("remove\n");
}

void list(BlockchainPtr blockchain, string_array *split_read_buffer) {
  printf("list\n");
}

void sync(BlockchainPtr blockchain, string_array *split_read_buffer) {
  printf("sync\n");
}

void quit(BlockchainPtr blockchain, string_array *split_read_buffer) {
  printf("quit\n");
}

void execute_command(BlockchainPtr blockchain, string_array *split_read_buffer) {
  void (*command[])(BlockchainPtr blockchain, string_array *split_read_buffer) 
    = {add, remove_, list, sync, quit};
  char *command_strings[] = {"add", "rm", "ls", "sync", "quit"};
  int i = 0;

  while (i < 5) {
    if (strcmp(command_strings[i], split_read_buffer->array[0]) == 0) {
      (*command[i])(blockchain, split_read_buffer);
      break;
    }
    i++;
  }
  
  if (i == 5) {
    printf(NO_COMMAND_FOUND);
  }
}
