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

int parse_block_args(args_array *args, commands command, int bid, int nid) {
  switch(command) {
    case ADD: {

    }
  }
}

int parse_node_args() {
}

int parse_add_args(args_array *args, commands command, int bid, int nid) {
  if (args->size < 2) {
    return 1;
  } else if (strcmp(args->array[0], "block") == 0 && args->size == 3) {
    //parse_block_args();
  } else if (strcmp(args->array[0], "node") == 0 && args->size == 2) {
    //parse_node_args();
  } else {
    return 1;
  }
  return 0;
}

int parse_rm_args() {
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
  char *bid = NULL;
  char *nid = NULL;

  args_array *args = subarray(argv, 2, argc - 1);
  for (int i = 0; i < argc - 2; i++) {
    printf("#%d: %s\n", i, args->array[i]); 
  }

  if (argc > 1) {
    switch(find_command(argv[1])) {
      case ADD: {
        printf("add command found\n");
        //parse_add_args();
        break;
      }
      case RM: {
        printf("rm command found\n");
        //parse_rm_args();
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
