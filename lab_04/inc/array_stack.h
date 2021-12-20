#ifndef _ARRAY_STACK_H_
#define _ARRAY_STACK_H_

#define ERR_MEMORY_ALLOC -1
#define ERR_INPUT_STRING -2
#define ERR_EMPTY_STRING -3
#define ERR_BUFFER_OVERFLOW -4
#define ERR_STACK_OVERFLOW -5
#define ERR_EMPTY_STACK -6

#define MAX_ARRAY_SIZE 1000

typedef struct
{
	char *stack;
	char *last_elem;
    char *curr_elem;
} array_stack_t;

int push_array(char **ptr_curr, char *ptr_end, char value);
int pop_array(char **ptr_curr, char *ptr_beg);
void print_array(char *ptr_beg, char *ptr_curr);
int array_check_brackets(size_t size);

#endif // _ARRAY_STACK_H_
