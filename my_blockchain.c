#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "helpers.h"
#include "blockchain.h"
#include "arguments_blockchain.h"

int main() {
  BlockchainPtr blockchain = blockchainConstructor();
  ArgumentsPtr args = argumentsConstructor();

  print_prompt(blockchain->getNumNodes(blockchain), blockchain->getSyncState(blockchain));
  args->readInput(args->read_buffer);

  if(args->read_buffer[0] != '\0') {
    printf("Input read into buffer: %s\n", args->read_buffer);
  }

  blockchainDestructor(blockchain);
  argumentsDestructor(args);
  return 0;
}
