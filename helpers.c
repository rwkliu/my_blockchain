#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "helpers.h"

int get_int_len(int n) {
  int int_len = 1;

  if(n < 0) {
    n = -n;
  }
  
  while(n > 9) {
    int_len++;
    n = n / 10;
  }
  return int_len;
}

char *signed_decimal(int s_int) {
  int n_len = get_int_len(s_int);
  char *decimal = malloc(n_len *sizeof(char));

  if(s_int < 0) {
    s_int = -s_int;
  }
  
  for(int i = n_len -1; i >= 0; i--) {
    decimal[i] = (s_int % 10) + '0';
    s_int = s_int / 10;
  }
  return decimal;
}

void print_prompt(int num_nodes, char sync_status) {
  char *char_num_nodes = signed_decimal(num_nodes);
  int num_digits = get_int_len(num_nodes);
  
  write(1, "[", 1);
  write(1, &sync_status, 1);
  write(1, char_num_nodes, num_digits);
  write(1, "]> ", 3);

  free(char_num_nodes);
}
