#include <stdio.h>
#include <string.h>

int isPosNum(char *str) {
  int str_len = strlen(str);

  for (int i = 0; i < str_len; i++) {
    if (str[i] < '0' || str[i] > '9') {
      return 1;
    }
  }
  return 0;
}

int main () {
  printf("%i\n", isPosNum("12"));   // 0
  printf("%i\n", isPosNum("033"));  // 0
  printf("%i\n", isPosNum("0"));    // 0
  printf("%i\n", isPosNum(""));     // 0
  printf("%i\n", isPosNum("node")); // 1
  printf("%i\n", isPosNum("I"));    // 1
  printf("%i\n", isPosNum("aaa"));  // 1
  printf("%i\n", isPosNum("\n"));   // 1
  printf("%i\n", isPosNum("a0\n")); // 1

  return 0;
}
