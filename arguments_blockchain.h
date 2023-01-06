#define READ_BUFFER_SIZE 21

#ifndef STRUCT_BLOCKCHAIN_ARGS
#define STRUCT_BLOCKCHAIN_ARGS
typedef struct s_arguments {
  char *commands[5];
  char read_buffer[READ_BUFFER_SIZE];
  struct s_string_array *split_read_buffer;

  char *(*readInput)(char *);
  struct s_string_array *(*splitInput)(char *, char *);
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