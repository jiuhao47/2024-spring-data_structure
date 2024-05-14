#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef int EleType;
typedef struct Treenode
{
    EleType val;
    struct Treenode *left;
    struct Treenode *right;
} Treenode;

void Tree_print_max(Treenode *root, int x);
Treenode *Treenode_build(EleType val);
bool Treeinit(Treenode **root, EleType val);
void Tree_print_max(Treenode *root, int x)
{
    if (root)
    {
        Tree_print_max(root->right, x);
        if (root->val >= x)
        {
            printf("%d ", root->val);
        }
        Tree_print_max(root->left, x);
    }
    else
    {
        return;
    }
}

bool Treeinit(Treenode **root, EleType val)
{
    if (*root)
    {
        return false;
        // Tree already init
    }
    else
    {
        *root = Treenode_build(val);
        return true;
    }
}
Treenode *Treenode_build(EleType val)
{
    Treenode *p = (Treenode *)malloc(sizeof(Treenode));
    p->left = p->right = NULL;
    p->val = val;
    return p;
}

int main()
{
    Treenode *root = NULL;
    int i = 0;
    Treeinit(&root, 4);
    root->left = Treenode_build(2);
    root->right = Treenode_build(6);
    root->left->left = Treenode_build(1);
    root->left->right = Treenode_build(3);
    root->right->left = Treenode_build(5);
    root->right->right = Treenode_build(7);

    /*
    while (i < 10)
    {
        Treenode *p = Treenode_build(i);
        Treenode_insert(&root, p);
        ++i;
    }
    */
    int x;
    printf("Input the x:");
    scanf("%d", &x);
    Tree_print_max(root, x);
    printf("\n");
}