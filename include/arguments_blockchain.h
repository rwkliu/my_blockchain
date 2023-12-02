#ifndef ARGUMENTS_BLOCKCHAIN_H
#define ARGUMENTS_BLOCKCHAIN_H
#include "helpers.h"

#define READ_BUFFER_SIZE 21

#ifndef ENUM_S_COMMANDS
#define ENUM_S_COMMANDS
typedef enum s_commands {
  ADD, RM, LS, SYNC, QUIT, NA 
} commands;
#endif

#ifndef STRUCT_BLOCKCHAIN_ARGS
#define STRUCT_BLOCKCHAIN_ARGS
typedef struct s_arguments {
  char read_buffer[READ_BUFFER_SIZE];
  string_array *split_read_buffer;

  string_array *(*splitInput)(char *, char *);
  int (*clearBuffers)(struct s_arguments *);
} Arguments;
#endif

typedef Arguments *ArgumentsPtr;

//Allocate memory for Arguments struct
ArgumentsPtr argumentsConstructor(ArgumentsPtr args);

//Free allocated memory for Arguments struct
int argumentsDestructor(ArgumentsPtr args);

//Initialize Arguments members
int argumentsInitialize(ArgumentsPtr args);

int clearBuffers(ArgumentsPtr);

//Return enum corresponding to arg
commands find_command(char *arg);

//Return string_array that is a subarray of the input string array
string_array *subarray(char **argv, int start_index, int end_index);

int is_not_quit(ArgumentsPtr args);
#endif