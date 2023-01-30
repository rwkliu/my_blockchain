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
  blockchainConstructor(&blockchain);
  Arguments args;
  argumentsConstructor(&args);
  char *read_str = NULL;
  print_prompt(blockchain.num_nodes, blockchain.sync_state);
  while ((read_str = my_readline(0)) != NULL) {
    strncpy(args.read_buffer, read_str, strlen(read_str));
    // printf("%s\n", args.read_buffer);
    // printf("args buffer: %s\n", args.read_buffer);
    if (args.read_buffer[0] == '\0') {
      continue;
    }
    args.split_read_buffer = args.splitInput(args.read_buffer, " ");
    execute_command(&blockchain, args.split_read_buffer);
    // printf("after execution\n");
    args.clearBuffers(&args);
    print_prompt(blockchain.num_nodes, blockchain.sync_state);
  }

  free_blockchain(&blockchain);
  argumentsDestructor(&args);
  return 0;
}
