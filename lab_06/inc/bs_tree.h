#ifndef _BS_TREE_H_
#define _BS_TREE_H_

typedef struct tree_node tree_node_t;

typedef struct tree_node
{
    int number;
    tree_node_t *left;
    tree_node_t *right;
} tree_node_t;

tree_node_t *bs_new_node(int number);
tree_node_t *bs_insert(tree_node_t *tree, int number, int *comparisons);
tree_node_t *bs_search(tree_node_t *tree, int number);
void bs_for_dot(FILE *stream, tree_node_t *tree);
void bs_pre_order(FILE *stream, tree_node_t *tree);
void bs_export_to_dot(FILE *stream, 
const char *tree_name, tree_node_t *tree);

#endif // _BS_TREE_H_
