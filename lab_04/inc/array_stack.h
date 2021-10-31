#ifndef _ARRAY_STACK_H_
#define _ARRAY_STACK_H_

#define ERR_STACK_OVERFLOW -1
#define ERR_EMPTY_STACK -2
#define ERR_MEMORY_ALLOC -3
#define ERR_INPUT_STRING -4

int push_array(char **ptr_curr, char *ptr_end, char value);
int pop_array(char **ptr_curr, char *ptr_beg);
void print_array(char *ptr_beg, char *ptr_curr);
int array_check_brackets(size_t size);

#endif // _ARRAY_STACK_H_
