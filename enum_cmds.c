#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum s_commands {
  ADD, RM, LS, SYNC, QUIT, NA 
} commands;

typedef struct s_args_array {
  int size;
  char **array;
} args_array;

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

//Check if input string is a positive integer number
int isPosNum(char *str) {
  int str_len = strlen(str);

  for (int i = 0; i < str_len; i++) {
    if (str[i] < '0' || str[i] > '9') {
      return 1;
    }
  }
  return 0;
}

//Return args_array that is a subarray of the input string array
args_array *subarray(char **argv, int start_index, int end_index) {
  args_array *subarray = malloc(sizeof(args_array));
  subarray->size = end_index - start_index + 1;
  subarray->array = malloc(subarray->size * sizeof(char *));
  int index = 0;

  for (int i = start_index; i <= end_index; i++) {
    subarray->array[index] = argv[i];
    index++;
  }
  return subarray;
}

//Check subsequent arguments for correct arguments following "block"
int parse_block_args(char **block_args, commands command) {
  int bid_arg = atoi(block_args[0]);
  int nid_arg = atoi(block_args[1]);

  switch(command) {
    case ADD: {
      if (bid_arg != 0 && nid_arg != 0) {
        printf("bid: %d\n", bid_arg); 
        if (nid_arg == '*') {
          printf("nid: *\n");
        } else {
          printf("nid: %d\n", nid_arg); 
        }
      }
      break;
    }
    case RM: {

      break;
    }
    default:
      printf("Invalid block arguments\n");
  }
}

//Check subsequent arguments for correct arguments following "node"
int parse_node_args(char *node_args, commands command) {
  int nid_arg = atoi(node_args);
  switch(command) {
    case ADD: {
      if (isPosNum(node_args) == 0) {
        printf("nid added: %d\n", nid_arg);
      } else {
        printf("invalid node arguments\n"); 
      }
      break;
    }
    case RM: {
      if (isPosNum(node_args) == 0) {
        printf("nid removed: %d\n", nid_arg);
      } else {
        printf("invalid node arguments\n");
      }
      break;
    }
    default:
      printf("Invalid node arguments\n");
  }
}

//if command = ADD, check subsequent arguments for correct arguments
int parse_add_args(args_array *args, commands command) {
  if (args->size < 2) {
    return 1;
  } else if (strcmp(args->array[0], "block") == 0 && args->size == 3) {
    printf("Add parse_block_args entered\n");
    char *block_args[2] = {args->array[1], args->array[2]};
    parse_block_args(block_args, command);
  } else if (strcmp(args->array[0], "node") == 0 && args->size == 2) {
    printf("Add parse_node_args entered\n");
    char *node_args = args->array[1];
    parse_node_args(node_args, command);
  } else {
    printf("Add arguments not recognized or too many arguments are entered\n");
    return 1;
  }
  return 0;
}

//if command = RM, check subsequent arguments for correct arguments
int parse_rm_args(args_array *args, commands command) {
  if (args->size < 2) {
    return 1;
  } else if (strcmp(args->array[0], "block") == 0 && args->size == 2) {
      printf("rm parse_block_args entered\n"); 
      char **block_args = &args->array[1];
      parse_block_args(block_args, command);
  } else if ( strcmp(args->array[0], "node") == 0 && args->size == 2) {
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
int parse_ls_args(args_array *args) {
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

int main(int argc, char **argv) {
  args_array *args = subarray(argv, 2, argc - 1);

  //Print the strings stored in args
  //for (int i = 0; i < argc - 2; i++) {
  //  printf("#%d: %s\n", i, args->array[i]); 
  //}

  if (argc > 1) {
    switch(find_command(argv[1])) {
      case ADD: {
        printf("add command found\n");
        parse_add_args(args, ADD);
        break;
      }
      case RM: {
        printf("rm command found\n");
        parse_rm_args(args, RM);
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
  } else {
    printf("No commands entered\n");
  }

  free(args);
  return 0;
}
