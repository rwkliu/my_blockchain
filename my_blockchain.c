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
    args->clearBuffers(args);
    print_prompt(blockchain.num_nodes, blockchain.sync_state);
    args->readInput(args->read_buffer);
    // if(args->read_buffer[0] != '\0') {
    //   printf("Input read into buffer: %s\n", args->read_buffer);
    // }

    args->split_read_buffer = args->splitInput(args->read_buffer, " ");
    // for (int i = 0; i < args->split_read_buffer->size; i++) {
    //   printf("split string #%d: %s\n", i, args->split_read_buffer->array[i]);
    // }

    // args->parseArguments(args->split_read_buffer);
    execute_command(&blockchain, args->split_read_buffer);
  }

  free_blockchain(&blockchain);
  argumentsDestructor(args);
  return 0;
}
