#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "helpers.h"
#include "blockchain.h"
#include "node.h"
#include "block.h"
#include "arguments_blockchain.h"
#include "execute_command.h"
#include "my_readline.h"

int main() {
  Blockchain blockchain;
  Arguments args;
  char *read_str = NULL;
  
  blockchainConstructor(&blockchain);
  argumentsConstructor(&args);
  print_prompt(blockchain.num_nodes, blockchain.sync_state);
  
  while ((read_str = my_readline(0)) != NULL) {
    strncpy(args.read_buffer, read_str, strlen(read_str));
    if (args.read_buffer[0] == '\0') {
      free(read_str);
      continue;
    }
    args.split_read_buffer = args.splitInput(args.read_buffer, " ");
    execute_command(&blockchain, args.split_read_buffer);
    args.clearBuffers(&args);
    print_prompt(blockchain.num_nodes, blockchain.sync_state);
    free(read_str);
  }

  free_blockchain(&blockchain);
  argumentsDestructor(&args);
  return 0;
}
