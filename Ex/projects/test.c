
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

typedef enum CmdType
{ // ������������������༭��ɾ��
    _delete,
    _insert
} CmdType;

typedef struct Cmd
{                  // ���������ʽ
    CmdType type;  // �����������
    int pos;       // ��ǰָ����ı�λ��ָ��
    int len;       // �±༭���ݵĳ���
    char *content; // �༭���������
} Cmd;

typedef struct Stack
{                       // ����ջ�ṹ
    Cmd *cmd;           // �����ʽ
    struct Stack *next; // ��һ��ջ�ڵ㣨��������ʵ��ջ��
} Stack;
int doCmd(char *ctx, Cmd *cmd);
Stack *initStack()
{
    Stack *S = (Stack *)malloc(sizeof(Stack));
    S->cmd = NULL;
    S->next = NULL;
    return S;
}

int push(Stack **stack, Cmd *cmd)
{ // ��ջ����
    Stack *node = (Stack *)malloc(sizeof(Stack));
    node->next = *stack;
    node->cmd = cmd;
    *stack = node;
    return 0;
}

// ��ȡջ��Ԫ��
Cmd *getTop(Stack *stack)
{
    if (stack != NULL)
    {
        return stack->cmd;
    }
    return NULL;
}

// ��ջ
int pop(Stack **stack)
{
    if (*stack == NULL)
        return 0;
    Stack *nt = (*stack)->next;
    free(*stack);
    *stack = nt;
    return 0;
}

int doCmdAndRec(char *ctx, Cmd *cmd, Stack *undoStack, Stack *redoStack)
{
    // ���������ջ
    /*
    while (redoStack != NULL)
    {
        printf("Enter\n");
        pop(&redoStack);
    }
    */
    // �༭�ı��������༭����ѹ�볷��ջ
    doCmd(ctx, cmd);
    cmd->type = (cmd->type == _insert) ? _delete : _insert;
    push(&undoStack, cmd);
    return 0;
}
int undoCmd(char *ctx, Stack *undoStack, Stack *redoStack)
{
    Cmd *undo = getTop(undoStack);
    if (undo == NULL)
        return 0;
    pop(&undoStack);
    doCmd(ctx, undo);
    undo->type = (undo->type == _insert) ? _delete : _insert; // �ı�ָ�����ͣ�����ִ������
    push(&redoStack, undo);
    return 0;
}
int redoCmd(char *ctx, Stack *undoStack, Stack *redoStack)
{
    Cmd *redo = getTop(redoStack);
    if (redo == NULL)
        return 0;
    pop(&redoStack);
    doCmd(ctx, redo);
    redo->type = (redo->type == _insert) ? _delete : _insert; // �ı�ָ�����ͣ�����ִ�г���
    push(&undoStack, redo);
    return 0;
}

int doCmd(char *ctx, Cmd *cmd)
{
    if (cmd->type == _insert)
    {
        for (int k = 0; k < cmd->len; k++)
        {
            ctx[strlen(ctx) + k] = ctx[cmd->pos + k];
        } // �Ƚ����Ӵ�������ݸ���һ�������ƣ����ڳ����ӿռ�
        for (int i = 0; i < cmd->len; i++)
        {
            ctx[cmd->pos + i] = cmd->content[i];
        }
        return 0;
    }
    else if (cmd->type == _delete)
    {
        for (int j = 0; j < cmd->len; j++)
        {
            ctx[cmd->pos + j] = ctx[cmd->pos + cmd->len + j];
        }
        return 0;
    }
    return 0;
}

int main()
{
    Stack *undoStack = initStack();
    Stack *redoStack = initStack();
    int t = 0;              // ��������
    int pos = 0;            // ����λ��
    int len = 0;            // ����������
    char s[MAXSIZE] = "";   // ��������
    char ctx[MAXSIZE] = ""; // �������
    while (1)
    {
        printf("�������Ӧ������ѡ��Ҫִ�еĲ�����\n0.���� 1.ɾ�� 2.���� 3.���� 4.�˳�\n");
        scanf("%d", &t);
        Cmd *cmd = (Cmd *)malloc(sizeof(Cmd));
        switch (t)
        {
        case (0):
            printf("����ָ���ʽΪ������λ��+�������ַ�������+�������ݡ������룺");
            scanf("%d%d%s", &pos, &len, s);
            cmd->type = _insert;
            cmd->pos = pos;
            cmd->len = len;
            cmd->content = s;
            doCmdAndRec(ctx, cmd, undoStack, redoStack);
            printf("��ǰ�ı�Ϊ��%s\n", ctx);
            break;
        case (1):
            printf("ɾ��ָ���ʽΪ��ɾ�����λ��+��ɾ���ַ������ȡ������룺");
            scanf("%d%d", &pos, &len);
            cmd->type = _delete;
            cmd->pos = pos;
            cmd->len = len;
            doCmdAndRec(ctx, cmd, undoStack, redoStack);
            printf("��ǰ�ı�Ϊ��%s\n", ctx);
            break;
        case (2):
            undoCmd(ctx, undoStack, redoStack);
            printf("��ǰ�ı�Ϊ��%s\n", ctx);
            break;
        case (3):
            redoCmd(ctx, undoStack, redoStack);
            printf("��ǰ�ı�Ϊ��%s\n", ctx);
            break;
        case (4):
            return 0;
        }
    }
}