#ifndef _LIST_STACK_H_
#define _LIST_STACK_H_

#define ERR_MEMORY_ALLOC -3
#define ERR_INPUT_STRING -4

struct node
{
    char value;
    struct node *prev_elem;
};

void init_free_area(void);
struct node *push_list(struct node *last_elem, char value);
struct node *pop_list(struct node *last_elem, int fl_an);
void print_list(struct node *last_elem);
int list_check_brackets(size_t size);

#endif // _LIST_STACK_H_
