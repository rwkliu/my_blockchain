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

  char *(*readInput)(char *);
  string_array *(*splitInput)(char *, char *);
  int (*parseArguments)(string_array *);
} Arguments;
#endif

typedef Arguments *ArgumentsPtr;

//Read one char from stdin
int my_getchar();

//Read from stdin
char *read_input(char *read_buffer);

//Allocate memory for Arguments struct
ArgumentsPtr argumentsConstructor(void);

//Free allocated memory for Arguments struct
int argumentsDestructor(ArgumentsPtr args);

//Initialize Arguments members
int argumentsInitialize(ArgumentsPtr args);

//Return pointer to read_buffer
char *getReadBuffer(ArgumentsPtr args);

//Return enum corresponding to arg
commands find_command(char *arg);

//Return string_array that is a subarray of the input string array
string_array *subarray(char **argv, int start_index, int end_index);

int isAddBlock(string_array *args, commands command);

int isAddNode(string_array *args, commands command);

int isRmBlock(string_array *args, commands command);

int isRmNode(string_array *args, commands command);

//Check subsequent arguments for correct arguments following "block"
int parse_block_args(char **block_args, commands command);

//Check subsequent arguments for correct arguments following "node"
int parse_node_args(char *node_args, commands command);

//if command = ADD or RM, check subsequent arguments for correct arguments
int parse_add_rm_args(string_array *args, commands command);

//If command = LS, check subsequent arguments for no arguments or -l option
int parse_ls_args(string_array *args);

//Parse arguments read from stdin
int parse_arguments(string_array *split_strings_array);
