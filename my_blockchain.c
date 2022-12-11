#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "helpers.h"

#ifndef BLOCKCHAIN
#define BLOCKCHAIN
typedef struct s_blockchain {
  int num_nodes;
  char sync_status;
} Blockchain;
#endif

#ifndef BLOCK
#define BLOCK
typedef struct s_block {
  int nid;
  char *bid;
  
} block;
#endif

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
  int num_nodes = 15;
  char sync_status = 's';
  char read_buffer[20];
  print_prompt(num_nodes, sync_status);
  int bytes_read = read(0, &read_buffer, 20);

  if(bytes_read > 20) {
    printf("Input too long. Try again\n");
    bytes_read = read(0, &read_buffer, 20);
  }
  read_buffer[bytes_read] = '\0';

  printf("Input read into buffer: %s\n", read_buffer);
  return 0;
}