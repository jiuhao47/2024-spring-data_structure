/**
 * @ IIE, CAS.
 * @ Info  平衡二叉树判定
 *
 */

// mmh % everyone!!!!
// #pragma GCC optimize(2)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <time.h>
typedef struct Tree
{
    int val;                   // 数字
    struct Tree *left, *right; // 左右孩子指针
} Tree;

int isBalance(Tree *root);
int myabs(int n);
int treeDepth(Tree *root);
Tree *insert(Tree *node, int val);

int isBalance(Tree *root)
{
    if (root == NULL)
    {
        return 1;
    }
    int leftDepth = treeDepth(root->left);
    int rightDepth = treeDepth(root->right);
    if (myabs(leftDepth - rightDepth) > 1)
    {
        return 0;
    }
    else
    {
        return isBalance(root->left) && isBalance(root->right);
    }
}
int myabs(int n)
{
    return (n >= 0) ? n : -1 * n;
}
int treeDepth(Tree *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        int left = treeDepth(root->left);
        int right = treeDepth(root->right);
        return (left > right ? left : right) + 1;
    }
}

Tree *insert(Tree *node, int val)
{
    if (node == NULL)
    {
        Tree *newNode = (Tree *)malloc(sizeof(Tree));
        newNode->val = val;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (val < node->val)
    {
        node->left = insert(node->left, val);
    }
    else
    {
        node->right = insert(node->right, val);
    }
    return node;
}

int main()
{
    int n;
    scanf("%d", &n);
    Tree *root = NULL;
    for (int i = 0; i < n; i++)
    {
        int val;
        scanf("%d", &val);
        root = insert(root, val);
    }
    puts(isBalance(root) ? "yes" : "no");
    return 0;
}