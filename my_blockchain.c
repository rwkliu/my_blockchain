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

  while (is_not_quit(&args)) {
    args.clearBuffers(&args);
    print_prompt(blockchain.num_nodes, blockchain.sync_state);
    char *readline = my_readline(0);
    if (readline == NULL || readline[0] == '\0') {
      free(readline);
      break;
    }
    strncpy(args.read_buffer, readline, 20);
    free(readline);
    printf("%s\n", args.read_buffer);
    args.split_read_buffer = args.splitInput(args.read_buffer, " ");
    execute_command(&blockchain, args.split_read_buffer);
  }

  free_blockchain(&blockchain);
  argumentsDestructor(&args);
  return 0;
}
