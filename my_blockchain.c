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

int main() {
  Blockchain blockchain;
  blockchainConstructor(&blockchain);
  ArgumentsPtr args = argumentsConstructor();

  while (is_not_quit(args)) {
    argumentsDestructor(args);
    ArgumentsPtr args = argumentsConstructor();
    print_prompt(blockchain.num_nodes, blockchain.sync_state);
    args->readInput(args->read_buffer);
    args->split_read_buffer = args->splitInput(args->read_buffer, " ");
    execute_command(&blockchain, args->split_read_buffer);
  }

  free_blockchain(&blockchain);
  argumentsDestructor(args);
  return 0;
}
