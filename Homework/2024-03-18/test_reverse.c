#include <stdio.h>
#include <stdlib.h>

struct Stack
{
    int data;
    struct Stack *next;
} stack;

struct Stack *head = NULL;
struct Stack *Stack_init();
void Stack_destroy(struct Stack *head);
int Stack_empty_judge(struct Stack *head);
int Stack_len(struct Stack *head);
void Stack_push(struct Stack *head, int data);
int Stack_pop(struct Stack *head, int *data);
int Stack_top(struct Stack *head, int *data);

struct Stack *Stack_init()
{
    return (struct Stack *)malloc(sizeof(struct Stack));
}

void Stack_destroy(struct Stack *head)
{
    if (head->next != NULL)
    {
        Stack_destroy(head->next);
    }
    free(head);
    head = NULL;
}

int Stack_empty_judge(struct Stack *head)
{
    if (head->next == NULL)
    {
        return 1;
        // 1:Empty
    }
    return 0;
}

int Stack_len(struct Stack *head)
{
    int count = 0;
    struct Stack *p = head;
    while (p->next != NULL)
    {
        p = p->next;
        ++count;
    }
    return count;
}

void Stack_push(struct Stack *head, int data)
{
    struct Stack *p = (struct Stack *)malloc(sizeof(struct Stack));
    p->data = data;
    p->next = head->next;
    head->next = p;
}

int Stack_pop(struct Stack *head, int *data)
{
    struct Stack *p;
    if (head->next == NULL)
    {
        return 0;
    }
    p = head->next;
    *data = p->data;
    head->next = p->next;
    free(p);
    return 1;
}

int Stack_top(struct Stack *head, int *data)
{
    if (head->next == NULL)
    {
        return 0;
    }
    *data = head->next->data;
    return 1;
}
/*
int Stack_visit(struct Stack *head)
{
    //?
}
*/
int main()
{
    head = Stack_init();
    int c;
    int *temp = (int *)malloc(sizeof(int));
    int state = 1;
    while ((c = getchar()) != '\n')
    {
        if ((c != '&') && (state == 1))
        {
            Stack_push(head, c);
        }
        else if (c == '&')
        {
            state = 0;
        }
        else
        {
            if (Stack_pop(head, temp))
            {
                if (*temp == c)
                {
                }
                else
                {
                    printf("Wrong!\n");
                    Stack_destroy(head);
                    return 0;
                }
            }
            else
            {
                printf("Wrong!\n");
                Stack_destroy(head);
                return 0;
            }
        }
    }
    if (!Stack_empty_judge(head))
    {
        printf("Wrong!\n");
        Stack_destroy(head);
        return 0;
    }
    else
    {
        printf("Right!\n");
        Stack_destroy(head);
        return 0;
    }
}