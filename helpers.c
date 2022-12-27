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

int my_getchar() {
  int char_buffer;
  read(0, &char_buffer, 1);
  return char_buffer;
}

char *read_input(char *read_buffer) {
  int ch;
  int index = 0;

  while((ch = my_getchar()) != '\n' && ch != EOF) {
    if(index == READ_BUFFER_SIZE) {
      continue;
    }
    read_buffer[index] = ch;
    index++;
  }
  return read_buffer;
}
