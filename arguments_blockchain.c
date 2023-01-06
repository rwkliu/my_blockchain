#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "arguments_blockchain.h"
#include "helpers.h"

int my_getchar() {
  int char_buffer = 0;
  read(0, &char_buffer, 1);
  return char_buffer;
}

char *read_input(char *read_buffer) {
  int ch;
  int index = 0;

  while((ch = my_getchar()) != '\n' && ch != EOF) {
    if(ch == 0) {
      read_buffer[0] = '\0';
      return read_buffer;
    }
    if(index == READ_BUFFER_SIZE - 1) {
      continue;
    }
    read_buffer[index] = ch;
    index++;
  }
  return read_buffer;
}

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
  args->commands[0] = "add";
  args->commands[1] = "rm";
  args->commands[2] = "ls";
  args->commands[3] = "sync";
  args->commands[4] = "quit";
  args->readInput = read_input;
  args->getReadBuffer = getReadBuffer;
  args->splitInput = my_split;

  for(int i = 0; i < READ_BUFFER_SIZE; i++) {
    args->read_buffer[i] = '\0';
  }
  return 0;
}

char *getReadBuffer(ArgumentsPtr args) {
  return args->read_buffer;
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

//   //Read stdin and print read_buffer
//   args->readInput(args->read_buffer);
//   printf("read_buffer: %s\n", args->read_buffer);

//   //Print the contents of command array
//   for(int i = 0; i < 5; i++) {
//     printf("command #%d: %s\n", i, args->commands[i]);
//   }

//   argumentsDestructor(args);
//   return 0;
// }
