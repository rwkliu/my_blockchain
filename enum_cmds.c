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

commands find_command(char *argv) {
  if (strcmp(argv, "add") == 0) {
    return ADD;
  } 
  else if (strcmp(argv, "rm") == 0) {
    return RM;
  }
  else if (strcmp(argv, "ls") == 0) {
    return LS;
  }
  else if (strcmp(argv, "sync") == 0) {
    return SYNC;
  }
  else if (strcmp(argv, "quit") == 0) {
    return QUIT;
  }
  else {
    return NA;
  }
}

char **subarray(char **argv, int start_index, int end_index) {
  char **subarray = malloc(end_index - start_index + 1* sizeof(char *));
  int index = 0;

  for (int i = start_index; i <= end_index; i++) {
    subarray[index] = argv[i];
    index++;
  }
  return subarray;
}

int main(int argc, char **argv) {
  char *bid = NULL;
  char *nid = NULL;

  char **sub_args = subarray(argv, 2, argc - 1);
  //for (int i = 0; i < argc - 2; i++) {
  //  printf("#%d: %s\n", i, sub_args[i]);
  //}

  free(sub_args);

  if (argc > 1) {
    //printf("if statement entered here\n");
    switch(find_command(argv[1])) {
      case ADD: {
        printf("add command found\n");
        break;
      }
      case RM: {
        printf("rm command found\n");
        break;
      }
      case LS: {
        printf("ls command found\n");
        break;
      }
      case SYNC: {
        printf("sync command found\n");
        break;
      }
      case QUIT: {
        printf("quit command found\n");
        break;
      }
      default:
        printf("Command not found\n");
        break;
    }
  } else {
    printf("No commands entered\n");
  }
  return 0;
}
