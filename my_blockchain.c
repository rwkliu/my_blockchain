#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "helpers.h"
#include "blockchain.h"

int main() {
  int num_nodes = 0;
  char sync_status = 's';
  char read_buffer[READ_BUFFER_SIZE] = {0};

  print_prompt(num_nodes, sync_status);
  read_input(read_buffer);
  printf("Input read into buffer: %s\n", read_buffer);
  return 0;
}
