#include <stdio.h>
#include <stdlib.h>
int diameter = 0;
int main()
{
    int tree_len;
    scanf("%d", &tree_len);
    int tree[tree_len + 1];
    int far_to_root[tree_len + 1];
    int far_from_root[tree_len + 1];
    int temp_distance = 0;
    int j = 0;
    tree[0] = -1;
    tree[1] = 0;
    for (int i = 2; i < tree_len + 1; i++)
    {
        scanf("%d", &tree[i]);
    }

    for (int i = 1; i < tree_len + 1; i++)
    {
        j = i;
        while (tree[j] != 0)
        {
            // printf("j=%d\n", j);
            j = tree[j];
            temp_distance = temp_distance + 1;
            // printf("Enter\n");
        }
        far_to_root[i] = temp_distance;
        temp_distance = 0;
    }
    for (int i = 0; i < tree_len + 1; i++)
    {
        printf("%d ", tree[i]);
    }
    printf("\n");
    for (int i = 0; i < tree_len + 1; i++)
    {
        printf("%d ", far_to_root[i]);
    }
    printf("\n");
}

void build_from_root(int *tree, int *far_from_root, int i, int tree_len)
{
    for (int j = 0; j < tree_len; j++)
    {
        if (tree[j] == i)
        {
            build_from_root(tree, far_from_root, j, tree_len);
        }
    }
}