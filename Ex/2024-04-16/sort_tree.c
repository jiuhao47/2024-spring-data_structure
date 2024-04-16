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

Treenode *root;
bool Treeinit(Treenode **root, EleType val);
bool Treenode_insert(Treenode **root, Treenode *newnode);
bool Tree_print(Treenode **root, int mode);
Treenode *Treenode_build(EleType val);

typedef Treenode *EleType_Stack;
typedef struct Stack
{
    EleType_Stack data;
    struct Stack *next;
} Stack;

bool Stackinit(Stack **head)
{
    if (*head)
    {
        return false;
    }
    else
    {
        *head = (Stack *)malloc(sizeof(Stack));
        (*head)->next = NULL;
        return true;
    }
}

bool Stack_push(Stack **head, EleType_Stack data)
{
    Stack *p = (Stack *)malloc(sizeof(Stack));
    if (!p)
    {
        return false;
        // malloc fail
    }
    p->data = data;
    p->next = (*head)->next;
    (*head)->next = p;
    return true;
}

bool Stack_pop(Stack **head, EleType_Stack *data)
{
    Stack *q = (*head)->next;
    if (!q)
    {
        return false;
        // Empty Stack;
    }
    else
    {
        *data = q->data;
        (*head)->next = q->next;
        free(q);
        return true;
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
/*
bool Tree_print(Treenode **root, int mode)
{
    // 0 1 2
    switch (mode)
    {
    case 0:
        if ((*root))
        {
            printf(" %d", (*root)->val);
            Tree_print(&((*root)->left), mode);
            Tree_print(&((*root)->right), mode);
        }
        break;
    case 1:
        if ((*root))
        {
            Tree_print(&((*root)->left), mode);
            printf(" %d", (*root)->val);
            Tree_print(&((*root)->right), mode);
        }
        break;
    case 2:
        if ((*root))
        {
            Tree_print(&((*root)->left), mode);
            Tree_print(&((*root)->right), mode);
            printf(" %d", (*root)->val);
        }
        break;
    default:
        printf("Invalid mode!\n");
        exit(-1);
        break;
    }
}
*/
bool Tree_print(Treenode **root, int mode)
{
    Stack *head = NULL;
    Stack *head_2 = NULL;
    Stackinit(&head);
    Stackinit(&head_2);
    // 0 1 2
    Treenode *p;
    switch (mode)
    {
    case 0:
        p = *root;
        Stack_push(&head, p);
        while (head->next)
        {
            Stack_pop(&head, &p);
            printf(" %d", p->val);
            if (p->right)
            {
                Stack_push(&head, p->right);
            }
            if (p->left)
            {
                Stack_push(&head, p->left);
            }
        }
        break;
    case 1:
        p = *root;
        while (p || head->next)
        {
            // 将左子树全部压入栈
            while (p)
            {
                Stack_push(&head, p);
                p = p->left;
            }

            // 弹出栈顶元素并访问
            if (head->next)
            {
                Stack_pop(&head, &p);
                printf(" %d", p->val);
                // 将指针移动到右子树
                p = p->right;
            }
        }
        break;
    case 2:
        p = *root;
        Stack_push(&head, p);
        while (head->next)
        {
            Stack_pop(&head, &p);
            Stack_push(&head_2, p);
            if (p->left != NULL)
            {
                Stack_push(&head, p->left);
            }
            if (p->right != NULL)
            {
                Stack_push(&head, p->right);
            }
        }
        while (head_2->next)
        {
            Stack_pop(&head_2, &p);
            printf("%d ", p->val);
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
    Treenode *root = NULL;
    int i = 0;
    Treeinit(&root, 5);
    while (i < 10)
    {
        Treenode *p = Treenode_build(i);
        Treenode_insert(&root, p);
        ++i;
    }
    int mode;
    printf("Input the mode of print:");
    scanf("%d", &mode);
    Tree_print(&root, mode);
}