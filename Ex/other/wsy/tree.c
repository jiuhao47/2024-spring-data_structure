#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct TreeNode      //树的结点结构
{
    char data;               // 结点数据
    struct TreeNode *lchild; // 左子树指针
    struct TreeNode *rchild; // 右子树指针
    int flag;                // 在后序遍历中用来标记是否已被访问过
} TreeNode;

typedef struct StackNode    //辅助栈结构
{
    TreeNode *data;         // 结点数据
    struct StackNode *next; // 指向栈的下一个元素
} StackNode;


void CreateTree(TreeNode **T, int *index, char *data)  // 以先序序列输入创建二叉树
{
    char str;
    str = data[*index];
    (*index)++;
    if (str == ' ')   // 用' '表示空结点
    {
        *T = NULL;
    }
    else
    {
        *T = (TreeNode *)malloc(sizeof(TreeNode));
        (*T)->data = str;
        (*T)->flag = 0;
        CreateTree(&((*T)->lchild), index, data); // 递归创建左子树
        CreateTree(&((*T)->rchild), index, data); // 递归创建右子树
    }
}


StackNode *InitStack()  // 初始化栈表
{
    StackNode *s = (StackNode *)malloc(sizeof(StackNode));
    s->data = NULL;
    s->next = NULL;
    return s;
}


void Push(TreeNode *data, StackNode *s)  // 入栈
{
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    node->data = data;
    node->next = s->next;
    s->next = node;
}

int EmptyStack(StackNode *s)  // 判断栈是否为空
{
    if (s->next == NULL)
        return 1;
    else
        return 0;
}

StackNode *Pop(StackNode *s) //出栈 
{
    if (EmptyStack(s))
    {
        return NULL;
    }
    else
    {
        StackNode *node = s->next;
        s->next = node->next;
        return node;
    }
}


StackNode *getTop(StackNode *s)  // 获取栈顶数据
{
    if (EmptyStack(s))
    {
        return NULL;
    }
    else
    {
        return s->next;
    }
}

void preOrder(TreeNode *T)  // 非递归先序遍历
{
    TreeNode *p = T;  //p是遍历指针
    StackNode *s = InitStack();
    while (p || !EmptyStack(s))
    {
        if (p)
        {
            printf("%c ", p->data);
            Push(p, s);
            p = p->lchild;
        }
        else
        {
            p = Pop(s)->data;
            p = p->rchild;
        }
    }
}


void inOrder(TreeNode *T)  // 非递归中序遍历
{
    TreeNode *p = T;  //p是遍历指针
    StackNode *s = InitStack();
    while (p || !EmptyStack(s))
    {
        if (p)
        {
            Push(p, s);
            p = p->lchild;
        }
        else
        {
            p = Pop(s)->data;
            printf("%c ", p->data);
            p = p->rchild;
        }
    }
}


void postOrder(TreeNode *T)  // 非递归后序遍历
{
    TreeNode *p = T;  //p是遍历指针
    StackNode *s = InitStack();
    while (p || !EmptyStack(s))
    {
        if (p)
        {
            Push(p, s);
            p = p->lchild;
        }
        else
        {
            TreeNode *top = getTop(s)->data;  //用新建的top指针与flag标记判断结点是否被访问
            if (top->rchild && top->rchild->flag == 0)
            {
                top = top->rchild;
                Push(top, s);
                p = top->lchild;
            }
            else
            {
                top = Pop(s)->data;
                if (top->flag == 0)
                {
                    printf("%c ", top->data);
                    top->flag = 1;
                }
            }
        }
    }
}

int main()
{
    int index = 0;
    TreeNode *T;
    char data[100];
    printf("请输入序列，按先序遍历方式输入，并以“ ”代表空节点: ");
    fgets(data, sizeof(data), stdin);  //输入字符串
    CreateTree(&T, &index, data);
    printf("先序遍历结果为：");
    preOrder(T);
    printf("\n");
    printf("中序遍历结果为：");
    inOrder(T);
    printf("\n");
    printf("后序遍历结果为：");
    postOrder(T);
    return 0;
}