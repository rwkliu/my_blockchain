#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define RESULT_SIZE 100000

int READLINE_READ_SIZE = 20;
char *readline = NULL;

char *calloc_string(int size) {
  char *new_calloc_string = malloc(size * sizeof(char));

  for(int i = 0; i < size; i++) {
    new_calloc_string[i] = '\0';
  }
  
  return new_calloc_string;
}

void init_my_readline() {
  if(readline != NULL) {
    free(readline);
  }
  readline = calloc_string(READLINE_READ_SIZE + 1);
}

int my_string_index(char* param_1, char param_2){
  int index = 0;

  while (*param_1) {
    if(*param_1 == param_2) {
        return index;
    }
    index++;
    param_1++;
  }
  return -1;
}

//Return a pointer to the second string in str 
char *find_second_string(char *str) {
  int index = 0;

 if ((index = my_string_index(str, '\\')) != -1) {
    if (str[index + 1] == 'n') {
      str += index + 2;
    }
  }
  else if((index = my_string_index(str, '\n')) != -1) {
    str += index + 1;
  }
  return str;
}

//Allocate more memory to readline
void extend_readline() {
  char *temp = calloc_string(strlen(readline) + 1 + READLINE_READ_SIZE);
  strncpy(temp, readline, strlen(readline));
  free(readline);
  readline = temp;
}

int find_new_line(char *str) {
  int index = 0;

  if ((index = my_string_index(str, '\\')) != -1) {
    if (str[index + 1] == 'n') {
      return index;
    }
  } else if ((index = my_string_index(str, '\n')) != -1) {
    return index;
  } 
  return -1;
}

char *my_readline(int fd) {
  char *result_string = NULL;
  int ln_index = -1;
  int readline_index = 0;

  result_string = calloc_string(RESULT_SIZE);

  //If readline != NULL, copy all text except first string into result
  //Then free and malloc readline
  if(readline != NULL) {
    char *second_string = find_second_string(readline);
    // printf("second_string: %s\n", second_string);
    result_string = strcpy(result_string, second_string);
  }
  init_my_readline();

  //Copy result string into readline
  if(strlen(result_string) > 0) {
    if(strlen(readline) < strlen(result_string)) {
      free(readline);
      readline = calloc_string(strlen(result_string) + 1);
    }
    strncpy(readline, result_string, strlen(result_string));
  }

  read(fd, &readline[readline_index], READLINE_READ_SIZE);

  //Find the index of the first newline character
  ln_index = find_new_line(readline);
  // printf("ln_index: %d\n", ln_index);
  if(ln_index == -1) {
    free(result_string);
    return NULL;
  }

  //Copy to result_string until newline is reached
  strncpy(result_string, readline, ln_index);
  result_string[ln_index] = '\0';

  return result_string;
}
