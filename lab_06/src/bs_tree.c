#include <stdio.h>
#include <stdlib.h>

#include "bs_tree.h"

tree_node_t *bs_new_node(int number)
{
    tree_node_t *node = malloc(sizeof(tree_node_t));
    node->number = number;
    node->left = NULL;
    node->right = NULL;

    return node;
}

tree_node_t *bs_insert(tree_node_t *tree, int number, int *comparisons)
{
    (*comparisons)++;

    if (tree == NULL)
        return bs_new_node(number);

    if (number == tree->number)
        return tree;

    if (number < tree->number)
        tree->left = bs_insert(tree->left, number, comparisons);

    if (number > tree->number)
        tree->right = bs_insert(tree->right, number, comparisons);

    return tree;
}

tree_node_t *bs_search(tree_node_t *tree, int number)
{
    if (tree == NULL)
        return NULL;

    if (number == tree->number)
        return tree;

    if (number < tree->number)
        return bs_search(tree->left, number);

    if (number > tree->number)
        return bs_search(tree->right, number);

    return NULL;
}

void bs_for_dot(FILE *stream, tree_node_t *tree)
{
    if (tree->left)
        fprintf(stream, "%d -> %d;\n", tree->number, tree->left->number);

    if (tree->right)
        fprintf(stream, "%d -> %d;\n", tree->number, tree->right->number);
}

void bs_pre_order(FILE *stream, tree_node_t *tree)
{
    if (tree)
    {
        bs_for_dot(stream, tree);
        bs_pre_order(stream, tree->left);
        bs_pre_order(stream, tree->right);
    }
}

void bs_export_to_dot(FILE *stream, 
const char *tree_name, tree_node_t *tree)
{
    fprintf(stream, "digraph %s {\n", tree_name);
    bs_pre_order(stream, tree);
    fprintf(stream, "}\n");
}
