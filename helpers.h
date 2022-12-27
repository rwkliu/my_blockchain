#define READ_BUFFER_SIZE 20

//Get number of digits in n
int get_int_len(int n);

//Return string form of s_int
char *signed_decimal(int s_int);

//Read one char from stdin
int my_getchar();

//Read from stdin
char *read_input(char *read_buffer);

//Print my_blockchain prompt
void print_prompt(int num_nodes, char sync_status); 
