#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "avl_tree.h"
#include "bs_tree.h"

int main(int argc, char **argv)
{
    if (argc < 2)
        return EXIT_FAILURE;

    tree_node_t *root = NULL;

    FILE *f1 = fopen(argv[1], "r");

    size_t i, max;

    fscanf(f1, "%zu", &max);

    for (i = 0; i < max; i++)
    {
        int number;
        fscanf(f1, "%d", &number);

        root = bs_insert(root, number);
    }

    FILE *f = fopen("bs_tree.gv", "w");
    bs_export_to_dot(f, "BS_tree", root);
    fclose(f);

    system("dot -Tpng bs_tree.gv -o bs_tree.png");
    system("start bs_tree.png");

    avl_node_t *new_root = NULL;

    rewind(f1);

    fscanf(f1, "%zu", &max);

    for (i = 0; i < max; i++)
    {
        int number;
        fscanf(f1, "%d", &number);

        new_root = avl_insert(new_root, number);
    }

    FILE *f2 = fopen("avl_tree.gv", "w");
    avl_export_to_dot(f2, "AVL_tree", new_root);
    fclose(f2);

    system("dot -Tpng avl_tree.gv -o avl_tree.png");
    system("start avl_tree.png");

    fclose(f1);
    return 0;
}
