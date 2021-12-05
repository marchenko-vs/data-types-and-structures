#include <stdio.h>
#include <stdlib.h>

#include "avl_tree.h"

int height(avl_node_t *node)
{
    if (node == NULL)
        return 0;

    return node->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

avl_node_t *avl_new_node(int number)
{
    avl_node_t *node = malloc(sizeof(avl_node_t));
    node->number = number;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

avl_node_t *rightRotate(avl_node_t *y)
{
    avl_node_t *x = y->left;
    avl_node_t *T2 = x->right;
 
    x->right = y;
    y->left = T2;
 
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    return x;
}

avl_node_t *leftRotate(avl_node_t *x)
{
    avl_node_t *y = x->right;
    avl_node_t *T2 = y->left;
 
    y->left = x;
    x->right = T2;
 
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    return y;
}

int getBalance(avl_node_t *node)
{
    if (node == NULL)
        return 0;

    return height(node->left) - height(node->right);
}

avl_node_t *avl_insert(avl_node_t *node, int number)
{
    if (node == NULL)
        return(avl_new_node(number));
 
    if (number < node->number)
        node->left  = avl_insert(node->left, number);
    else if (number > node->number)
        node->right = avl_insert(node->right, number);
    else
        return node;
 
    node->height = 1 + max(height(node->left),
                           height(node->right));
 
    int balance = getBalance(node);
 
    if (balance > 1 && number < node->left->number)
        return rightRotate(node);
 
    if (balance < -1 && number > node->right->number)
        return leftRotate(node);
 
    if (balance > 1 && number > node->left->number)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    if (balance < -1 && number < node->right->number)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    return node;
}

avl_node_t *minValueNode(avl_node_t *node)
{
    avl_node_t *current = node;
 
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

avl_node_t *avl_delete(avl_node_t *root, int number)
{
 
    if (root == NULL)
        return root;
 
    if ( number < root->number )
        root->left = avl_delete(root->left, number);
    else if(number > root->number)
        root->right = avl_delete(root->right, number);
    else
    {
        if( (root->left == NULL) || (root->right == NULL) )
        {
            avl_node_t *temp = root->left ? root->left :
                                             root->right;
 
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;

            free(temp);
        }
        else
        {
            avl_node_t *temp = minValueNode(root->right);
 
            root->number = temp->number;
 
            root->right = avl_delete(root->right, temp->number);
        }
    }
 
    if (root == NULL)
      return root;
 
    root->height = 1 + max(height(root->left),
                           height(root->right));
 
    int balance = getBalance(root);
 
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
 
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
 
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}

// void avl_pre_order(avl_node_t *root)
// {
//     if (root != NULL)
//     {
//         printf("%d ", root->number);
//         avl_pre_order(root->left);
//         avl_pre_order(root->right);
//     }
// }

void avl_for_dot(FILE *stream, avl_node_t *tree)
{
    if (tree->left)
        fprintf(stream, "%d -> %d;\n", tree->number, tree->left->number);

    if (tree->right)
        fprintf(stream, "%d -> %d;\n", tree->number, tree->right->number);
}

void avl_pre(FILE *stream, avl_node_t *tree)
{
    if (tree)
    {
        avl_for_dot(stream, tree);
        avl_pre(stream, tree->left);
        avl_pre(stream, tree->right);
    }
}

void avl_export_to_dot(FILE *stream, 
const char *tree_name, avl_node_t *tree)
{
    fprintf(stream, "digraph %s {\n", tree_name);
    avl_pre(stream, tree);
    fprintf(stream, "}\n");
}
