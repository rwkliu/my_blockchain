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

  //Print the prompt, get stdin input, and print the read_buffer
  print_prompt(blockchain->getNumNodes(blockchain), blockchain->getSyncState(blockchain));
  args->readInput(args->getReadBuffer(args));
  // if(args->read_buffer[0] != '\0') {
  //   printf("Input read into buffer: %s\n", args->read_buffer);
  // }

  //Print the split strings in the split_read_buffer array
  args->split_read_buffer = args->splitInput(args->getReadBuffer(args), " ");
  // for (int i = 0; i < args->split_read_buffer->size; i++) {
  //   printf("split string #%d: %s\n", i, args->split_read_buffer->array[i]);
  // }
  
  //Parse the split string arguments
  args->parseArguments(args->split_read_buffer);
  
  blockchainDestructor(blockchain);
  argumentsDestructor(args);
  return 0;
}