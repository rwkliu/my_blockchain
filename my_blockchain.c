#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "helpers.h"
#include "blockchain.h"

void print_prompt(int num_nodes, char sync_status) {
  char *char_num_nodes = signed_decimal(num_nodes);
  int num_digits = get_int_len(num_nodes);
  
  write(1, "[", 1);
  write(1, &sync_status, 1);
  write(1, char_num_nodes, num_digits);
  write(1, "]> ", 3);

  free(char_num_nodes);
}

int main() {
  int num_nodes = 0;
  char sync_status = 's';
  char read_buffer[READ_BUFFER_SIZE] = {0};

  print_prompt(num_nodes, sync_status);
  read_input(read_buffer);
  printf("Input read into buffer: %s\n", read_buffer);
  return 0;
}
