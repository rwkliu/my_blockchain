#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "arguments_blockchain.h"

ArgumentsPtr argumentsConstructor(void) {
  ArgumentsPtr args = malloc(sizeof(Arguments));
  argumentsInitialize(args);
  return args;
}

int argumentsDestructor(ArgumentsPtr args) {
  free(args);
  return 0;
}

int argumentsInitialize(ArgumentsPtr args) {
  args->readInput = read_input;
}

int my_getchar() {
  int char_buffer = 0;
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

//main function to test above functions
// int main() {
//   ArgumentsPtr args = argumentsConstructor();

//   if(args != NULL) {
//     printf("Arguments successfully created\n");
//   }
//   else {
//     printf("Arguments creation failed\n");
//   }

//   args->readInput(args->read_buffer);
//   printf("read_buffer: %s\n", args->read_buffer);

//   argumentsDestructor(args);
//   return 0;
// }