#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "helpers.h"

int get_int_len(int n) {
  int int_len = 1;

  if(n < 0) {
    n = -n;
  }
  
  while(n > 9) {
    int_len++;
    n = n / 10;
  }
  return int_len;
}

char *signed_decimal(int s_int) {
  int n_len = get_int_len(s_int);
  char *decimal = malloc(n_len *sizeof(char));

  if(s_int < 0) {
    s_int = -s_int;
  }
  
  for(int i = n_len -1; i >= 0; i--) {
    decimal[i] = (s_int % 10) + '0';
    s_int = s_int / 10;
  }
  return decimal;
}

void print_prompt(int num_nodes, char sync_status) {
  char *char_num_nodes = signed_decimal(num_nodes);
  int num_digits = get_int_len(num_nodes);
  
  write(1, "[", 1);
  write(1, &sync_status, 1);
  write(1, char_num_nodes, num_digits);
  write(1, "]> ", 3);

  free(char_num_nodes);
}

//split str1 using the separator and return a string array of split strings
string_array *my_split(char *str1, char *separator) {
  int separator_len = strlen(separator);
  string_array *split_str = malloc(sizeof(string_array));
  int num_split_strings = 1;

  str1 = my_strip(str1);
  
  //Return size 0 Null string array if str1 is an empty string
  if(strcmp(str1, "") == 0){
    split_str->size = 0;
    split_str->array = NULL;
    return split_str;
  }

  //Copy str1 to copied_str where the contents can be modified
  char *copied_str = strdup(str1);
  free(str1);
  char *head_copied_str = copied_str;

  //Traverse copied_str and replace the separator characters with \0
  while(*copied_str) {
    if(strncmp(copied_str, separator, separator_len) == 0) {
      for(int i = 0; i < separator_len; i++) {
        copied_str[i] = '\0';
      }
      copied_str += separator_len;
      num_split_strings++;
    }
    copied_str++;
  }
  
  //Allocate memory for the split string pointers and assign the pointers
  //to point to the split substrings
  copied_str = head_copied_str; //Move copied_str pointer to the beginning
  split_str->array = malloc(num_split_strings * sizeof(char *));
  for(int i = 0; i < num_split_strings; i++) {
    split_str->array[i] = copied_str;
    copied_str += strlen(copied_str) + 1;
  }
  split_str->size = num_split_strings;
  return split_str;
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

int last_char_index(char *str) {
  int index = strlen(str);
  char *end = str + index;

  while(end > str) {
    if(*end != ' ' && *end != '\0'){
      return index;
      break;
    }
    end--;
    index--;
  }
  return -1;
}

char *my_strip(char *str) {
  int i = 0;
  int last_char = last_char_index(str);
  char *stripped_str;
  char *last_char_string = strrchr(str, str[last_char]);

  //Return an empty string if input string is empty
  if(strcmp(str, "") == 0) {
    return "";
  }
  
  stripped_str = calloc(strlen(str) + 1 * sizeof(char), sizeof(char));

  while(*str) {
    //Add last char
    if(strcmp(str, last_char_string) == 0) {
      stripped_str[i] = *str;
      break;
    }
    //Add char
    if(*str != ' ') {
      stripped_str[i] = *str;
      i++;
    }
    //Add space if current char is ' ' and the char before is a char
    //Skips all ' ' that come before the first chaR
    else if(stripped_str[0] != 0) {
      if(*str == ' ' && stripped_str[i-1] != ' ') {
        stripped_str[i] = *str;
        i++;
      }
    }
    str++;
  }

  //Reallocate memory by freeing leftover memory
  stripped_str = realloc(stripped_str, strlen(stripped_str) + 1 * sizeof(char));
  return stripped_str;
}