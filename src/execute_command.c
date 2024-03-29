#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"
#include "helpers.h"
#include "status.h"

int is_remove(char *prev_cmd) {
  return strcmp(prev_cmd, "remove");
}

int is_add(char *prev_cmd) {
  return strcmp(prev_cmd, "add");
}

int is_block(char *component) {
  return strcmp(component, "block");
}

int is_node(char *component) {
  return strcmp(component, "node");
}

void nid(BlockchainPtr blockchain, char *prev_cmd, char *component, char *bid, char *nid) {
  int int_nid = atoi(nid);
  
  if (is_add(prev_cmd) == 0 && is_node(component) == 0) {
    blockchain->addNode(blockchain, &(blockchain->blockchain_head), int_nid);
  } else if (is_add(prev_cmd) == 0 && is_block(component) == 0) {
    blockchain->addBlock(blockchain, &(blockchain->blockchain_head), bid, int_nid);
  } else if (is_remove(prev_cmd) == 0 && is_node(component) == 0) {
    blockchain->removeNode(blockchain, &(blockchain->blockchain_head), int_nid);
  } else if (is_remove(prev_cmd) == 0 && is_block(component) == 0) {
    blockchain->removeBlock(blockchain, &(blockchain->blockchain_head), bid, int_nid);
  } else {
    printf(NO_COMMAND_FOUND);
  }
}

void bid(BlockchainPtr blockchain, string_array *split_read_buffer, char *prev_cmd, char *component, char *bid) {
  void (*args)(BlockchainPtr, char *, char *, char *, char *) = nid;
  char *char_nid = split_read_buffer->array[3];


  if (char_nid != NULL) {
    (*args)(blockchain, prev_cmd, component, bid, char_nid);
  } else {
    printf(NO_COMMAND_FOUND);
  }
}

void block(BlockchainPtr blockchain, string_array *split_read_buffer, char *prev_cmd) {
  void (*args)(BlockchainPtr, string_array *, char *, char *, char *) = bid;
  char *char_nid = split_read_buffer->array[3];
  char *char_bid = split_read_buffer->array[2];

  if (char_nid != NULL) {
    (*args)(blockchain, split_read_buffer, prev_cmd, "block", char_bid);
  } else {
    printf(NO_COMMAND_FOUND);
  }
}

void node(BlockchainPtr blockchain, string_array *split_read_buffer, char *prev_cmd) {
  void (*args)(BlockchainPtr, char *, char *, char *, char *) = nid;
  char *char_nid = split_read_buffer->array[2];

  if (char_nid != NULL) {
    (*args)(blockchain, prev_cmd, "node", "", char_nid);
  } else {
    printf(NO_COMMAND_FOUND);
  }
}

void add(BlockchainPtr blockchain, string_array *split_read_buffer) {
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
    printf("a\n");
    printf(NO_COMMAND_FOUND);
  }
}

void remove_(BlockchainPtr blockchain, string_array *split_read_buffer) {
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
  if (lflag != NULL && strncmp(lflag, "-l", 2) == 0 ) {
    blockchain->ls(&(blockchain->blockchain_head), PRINT_BID);
  } else {
    blockchain->ls(&(blockchain->blockchain_head), NO_BID);
  }
}

void sync(BlockchainPtr blockchain, string_array *split_read_buffer) {
  synchronize_nodes(blockchain, &(blockchain->blockchain_head));
  if (split_read_buffer->array[0] == NULL) {
    printf(NO_COMMAND_FOUND);
  }
}

void quit(BlockchainPtr blockchain, string_array *split_read_buffer) {
  save_blockchain(&(blockchain->blockchain_head));
  if (split_read_buffer->array[0] == NULL) {
    printf(NO_COMMAND_FOUND);
  }
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
