#include <stdio.h>
#include <stdlib.h>

struct Stack
{
    unsigned int data;
    struct Stack *next;
} stack;

struct Stack *head = NULL;
struct Stack *Stack_init();
void Stack_destroy(struct Stack *head);
int Stack_empty_judge(struct Stack *head);
int Stack_len(struct Stack *head);
void Stack_push(struct Stack *head, unsigned int data);
int Stack_pop(struct Stack *head, unsigned int *data);
int Stack_top(struct Stack *head, unsigned int *data);

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

void Stack_push(struct Stack *head, unsigned int data)
{
    struct Stack *p = (struct Stack *)malloc(sizeof(struct Stack));
    p->data = data;
    p->next = head->next;
    head->next = p;
}

int Stack_pop(struct Stack *head, unsigned int *data)
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

int Stack_top(struct Stack *head, unsigned int *data)
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

unsigned int f(unsigned int n);

int main()
{
    unsigned int n;
    printf("Input n:");
    scanf("%d", &n);
    printf("The Answer is %u\n", f(n));
    return 0;
}

unsigned int f(unsigned int n)
{
    unsigned int answer;
    head = Stack_init();
    unsigned int temp = n;
    while (temp)
    {
        Stack_push(head, temp);
        temp = temp / 2;
    }
    answer = 1;
    while (Stack_pop(head, &temp))
    {
        answer = answer * temp;
    }
    Stack_destroy(head);
    return answer;
}
