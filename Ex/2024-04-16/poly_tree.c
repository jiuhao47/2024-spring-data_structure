#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef char EleType;
typedef struct Treenode
{
    EleType val;
    struct Treenode *left;
    struct Treenode *right;
} Treenode;

Treenode *root;
bool Treeinit(Treenode **root, EleType val);
bool Treenode_insert(Treenode **root, Treenode *newnode);
bool Tree_print(Treenode **root, int mode);
Treenode *Treenode_build(EleType val);
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
/*
bool Treenode_insert(Treenode **root, Treenode *newnode)
{
    if ((*root))
    {
        if (newnode->val <= (*root)->val)
        {
            Treenode_insert(&((*root)->left), newnode);
        }
        else
        {
            Treenode_insert(&((*root)->right), newnode);
        }
    }
    else
    {
        (*root) = newnode;
    }
    return true;
}
*/
bool Treenode_insert(Treenode **root, Treenode *newnode)
{
    if ((*root))
    {
        if (newnode->val <= (*root)->val)
        {
            Treenode_insert(&((*root)->left), newnode);
        }
        else
        {
            Treenode_insert(&((*root)->right), newnode);
        }
    }
    else
    {
        (*root) = newnode;
    }
    return true;
}

bool Tree_print(Treenode **root, int mode)
{
    // 0 1 2
    switch (mode)
    {
    case 0:
        if ((*root))
        {
            printf(" %c", (*root)->val);
            Tree_print(&((*root)->left), mode);
            Tree_print(&((*root)->right), mode);
        }
        break;
    case 1:
        if ((*root))
        {
            Tree_print(&((*root)->left), mode);
            printf(" %c", (*root)->val);
            Tree_print(&((*root)->right), mode);
        }
        break;
    case 2:
        if ((*root))
        {
            Tree_print(&((*root)->left), mode);
            Tree_print(&((*root)->right), mode);
            printf(" %c", (*root)->val);
        }
        break;
    default:
        printf("Invalid mode!\n");
        exit(-1);
        break;
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
}