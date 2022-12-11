#include <stdlib.h>

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

//Return string version of signed decimal
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