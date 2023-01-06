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
  free(args->split_read_buffer->array[0]);
  free(args->split_read_buffer->array);
  free(args->split_read_buffer);
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
  args->parseArguments = parse_arguments;

  for(int i = 0; i < READ_BUFFER_SIZE; i++) {
    args->read_buffer[i] = '\0';
  }
  return 0;
}

char *getReadBuffer(ArgumentsPtr args) {
  return args->read_buffer;
}

commands find_command(char *arg) {
  if (strcmp(arg, "add") == 0) {
    return ADD;
  } else if (strcmp(arg, "rm") == 0) {
    return RM;
  } else if (strcmp(arg, "ls") == 0) {
    return LS;
  } else if (strcmp(arg, "sync") == 0) {
    return SYNC;
  } else if (strcmp(arg, "quit") == 0) {
    return QUIT;
  } else {
    return NA;
  }
}

//Return string_array that is a subarray of the input string array
string_array *subarray(char **argv, int start_index, int end_index) {
  string_array *subarray = malloc(sizeof(string_array));
  subarray->size = end_index - start_index + 1;
  subarray->array = malloc(subarray->size * sizeof(char *));
  int index = 0;

  for (int i = start_index; i <= end_index; i++) {
    subarray->array[index] = argv[i];
    index++;
  }
  return subarray;
}

int isAddBlock(string_array *args, commands command) {
  if (strcmp(args->array[0], "block") == 0 && args->size == 3 && command == ADD) {
    return 1;
  }
  return 0;
}

int isAddNode(string_array *args, commands command) {
  if (strcmp(args->array[0], "node") == 0 && args->size == 2 && command == ADD) {
    return 1;
  }
  return 0;
}

int isRmBlock(string_array *args, commands command) {
  if (strcmp(args->array[0], "block") == 0 && args->size == 2 && command == RM) {
    return 1;
  }
  return 0;
}

int isRmNode(string_array *args, commands command) {
  if (strcmp(args->array[0], "node") == 0 && args->size == 2 && command == RM) {
    return 1;
  }
  return 0;
}

//Check subsequent arguments for correct arguments following "block"
int parse_block_args(char **block_args, commands command) {
  int nid_arg = atoi(block_args[1]);

  switch(command) {
    case ADD: {
      if (nid_arg != 0) {
        printf("Add block bid: %s\n", block_args[0]); 
        if (nid_arg == '*') {
          printf("Add node nid: *\n");
        } else {
          printf("Add node nid: %d\n", nid_arg); 
        }
      } else {
        printf("Invalid bid and nid arguments\n");
      }
      break;
    }
    case RM: {
      printf("Remove block bid: %s\n", block_args[0]); 
      break;
    }
    default:
      printf("Invalid block arguments\n");
  }
  return 0;
}

//Check subsequent arguments for correct arguments following "node"
int parse_node_args(char *node_args, commands command) {
  int nid_arg = atoi(node_args);
  switch(command) {
    case ADD: {
      if (isPosNum(node_args) == 0) {
        printf("nid added: %d\n", nid_arg);
      } else {
        printf("invalid add nid argument\n"); 
      }
      break;
    }
    case RM: {
      if (isPosNum(node_args) == 0) {
        printf("nid removed: %d\n", nid_arg);
      } else {
        printf("invalid rm nid argument\n");
      }
      break;
    }
    default:
      printf("Invalid node arguments\n");
  }
  return 0;
}

//if command = ADD or RM, check subsequent arguments for correct arguments
int parse_add_rm_args(string_array *args, commands command) {
  if (args->size < 2) {
    printf("Not enough arguments\n");
    return 1;
  } else if (isAddBlock(args, command)) {
    printf("Add parse_block_args entered\n");
    char *block_args[2] = {args->array[1], args->array[2]};
    parse_block_args(block_args, command);
  } else if (isAddNode(args, command)) {
    printf("Add parse_node_args entered\n");
    char *node_args = args->array[1];
    parse_node_args(node_args, command);
  } else if (isRmBlock(args, command)) {
    printf("rm parse_block_args entered\n"); 
    char *block_args = args->array[1];
    parse_block_args(&block_args, command);
  } else if (isRmNode(args, command)) {
    printf("rm parse_node_args entered\n"); 
    char *node_args = args->array[1];
    parse_node_args(node_args, command);
  } else {
    printf("Add arguments not recognized or too many arguments are entered\n");
    return 1;
  }
  return 0;
}

//If command = LS, check subsequent arguments for no arguments or -l option
int parse_ls_args(string_array *args) {
  if (args->size == 0) {
    printf("List all nodes by their nid\n");
  } else if (strcmp(args->array[0], "-l") == 0) {
    printf("List all nodes' nid and bid\n");
  } else {
    printf("ls arguments not recognized\n");
    return 1;
  }
  return 0;
}

//Parse arguments read from stdin
int parse_arguments(string_array *split_strings_array) {
  if (split_strings_array->size > 1) {
    string_array *args = subarray(split_strings_array->array, 2, split_strings_array->size - 1);
    switch(find_command(split_strings_array->array[0])) {
      case ADD: {
        printf("add command found\n");
        parse_add_rm_args(args, ADD);
        break;
      }
      case RM: {
        printf("rm command found\n");
        parse_add_rm_args(args, RM);
        break;
      }
      case LS: {
        printf("ls command found\n");
        parse_ls_args(args);
        break;
      }
      case SYNC: {
        printf("sync command found\n");
        printf("Execute sync routine\n");
        break;
      }
      case QUIT: {
        printf("quit command found\n");
        printf("Execute quit routine\n");
        break;
      }
      default:
        printf("Command not found\n");
        break;
    }
    printf("free entered\n");
    free(args->array);
    free(args);
  } else {
    printf("No commands entered\n");
    return 1;
  }
  return 0;
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
//   argumentsDestructor(args);
//   return 0;
// }
