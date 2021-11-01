#ifndef _LIST_STACK_H_
#define _LIST_STACK_H_

#define ERR_MEMORY_ALLOC -1
#define ERR_INPUT_STRING -2

#define MAX_LIST_SIZE 3000

struct node
{
    char value;
    struct node *prev_elem;
};

void init_area(void);
void free_area(void);
struct node *push_list(struct node *last_elem, char value);
struct node *pop_list(struct node *last_elem, int option);
void print_list(struct node *last_elem);
int list_check_brackets(size_t size);

#endif // _LIST_STACK_H_
