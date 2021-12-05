#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

typedef struct avl_node avl_node_t;

typedef struct avl_node
{
    int number;
    avl_node_t *left;
    avl_node_t *right;
    int height;
} avl_node_t;

avl_node_t *avl_insert(avl_node_t *node, int number);
avl_node_t *avl_delete(avl_node_t *root, int number);
void avl_pre_order(avl_node_t *root);
void avl_export_to_dot(FILE *stream, 
const char *tree_name, avl_node_t *tree);

#endif // _AVL_TREE_H_
