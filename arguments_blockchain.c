#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "arguments_blockchain.h"
#include "helpers.h"
#include "status.h"

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
