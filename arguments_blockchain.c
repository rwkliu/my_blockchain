#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "arguments_blockchain.h"
#include "helpers.h"
#include "status.h"

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

ArgumentsPtr argumentsConstructor(ArgumentsPtr args) {
  argumentsInitialize(args);
  return args;
}

int argumentsDestructor(ArgumentsPtr args) {
  if (args->split_read_buffer == NULL) {
    return 1;
  }
  if (args->split_read_buffer->array != NULL) {
    free(args->split_read_buffer->array[0]);
    free(args->split_read_buffer->array);
  }
  free(args->split_read_buffer);
  return 0;
}

int argumentsInitialize(ArgumentsPtr args) {
  args->readInput = read_input;
  args->splitInput = my_split;
  args->clearBuffers = clearBuffers;
  args->split_read_buffer = NULL;

  for(int i = 0; i < READ_BUFFER_SIZE; i++) {
    args->read_buffer[i] = '\0';
  }
  return 0;
}

int clearBuffers(ArgumentsPtr args) {
  if (args->split_read_buffer != NULL) {
    free(args->split_read_buffer->array[0]);
    free(args->split_read_buffer->array);
  }
  for(int i = 0; i < READ_BUFFER_SIZE; i++) {
    args->read_buffer[i] = '\0';
  }
  free(args->split_read_buffer);
  args->split_read_buffer = NULL;
  return 0;
}

int is_not_quit(ArgumentsPtr args) {
  if (strncmp(args->read_buffer, "quit", 4) != 0) {
    return 1;
  }
  return 0;
}
