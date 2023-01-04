#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "helpers.h"
#include "blockchain.h"
#include "arguments_blockchain.h"

int main() {
  int num_nodes = 0;
  char sync_status = 's';
  ArgumentsPtr args = argumentsConstructor();

  print_prompt(num_nodes, sync_status);
  args->readInput(args->read_buffer);
  printf("Input read into buffer: %s\n", args->read_buffer);

  argumentsDestructor(args);
  return 0;
}
