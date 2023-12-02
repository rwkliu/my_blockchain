#ifndef STRUCT_STRING_ARRAY
#define STRUCT_STRING_ARRAY
typedef struct s_string_array {
  int size;
  char **array;
} string_array;
#endif

//Get number of digits in n
int get_int_len(int n);

//Return string form of s_int
char *signed_decimal(int s_int);

//Print my_blockchain prompt
void print_prompt(int num_nodes, char sync_status); 

//split str1 using the separator and return a string array of split strings
string_array *my_split(char *str1, char *separator);

//Check if input string is a positive integer number
int isPosNum(char *str);

int last_char_index(char *str);

char *my_strip(char *str);