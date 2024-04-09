#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct Queue
{
    int data;
    struct Queue *next;
} Queue;
bool Queue_in(Queue **head, Queue **tail, int data);
bool Queue_out(Queue **head, Queue **tail, int *data);
bool Queue_destory(Queue **head, Queue **tail);
bool Queue_in(Queue **head, Queue **tail, int data)
{
    if ((*head) == NULL)
    {
        (*head) = (Queue *)malloc(sizeof(Queue));
        (*head)->next = (Queue *)malloc(sizeof(Queue));
        (*head)->next->data = data;
        (*head)->next->next = NULL;
        *tail = (*head)->next;
        return true;
    }
    else
    {
        Queue *p = (Queue *)malloc(sizeof(Queue));
        p->data = data;
        p->next = (*head)->next;
        (*head)->next = p;
        return true;
    }
}

bool Queue_out(Queue **head, Queue **tail, int *data)
{
    if ((*head)->next == NULL)
    {
        // Empty Queue
        return false;
    }
    else
    {
        *data = (*tail)->data;
        Queue *p = (*head)->next;
        while (p->next != *tail)
        {
            p = p->next;
        }
        free(*tail);
        p->next = NULL;
        *tail = p;
        return true;
    }
}

bool Queue_destory(Queue **head, Queue **tail)
{
    if ((*head)->next == NULL)
    {
        // Empty Queue
        return false;
    }
    else
    {
        Queue *p = (*head)->next;
        while (p)
        {
            Queue *q = p;
            p = p->next;
            free(q);
        }
        free(*head);
        *head = NULL;
        *tail = NULL;
        return true;
    }
}

bool Queue_visit(Queue **head, Queue **tail)
{
    Queue *p = (Queue *)malloc(sizeof(Queue));
    p = (*head)->next;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
    return true;
}

int main()
{
    Queue *head = NULL;
    Queue *tail = NULL;
    char c;
    int num;
    printf("Enter code:");
    while ((c = getchar()) != 'q')
    {

        if (c == 'i')
        {
            printf("Insert number:");
            scanf("%d ", &num);
            fflush(stdin);
            Queue_in(&head, &tail, num);
            // printf("\nEnter code:");
        }
        else if (c == 'e')
        {
            Queue_out(&head, &tail, &num);
            printf("Exit number:%d\n", num);
            // printf("\nEnter code:");
        }
        else if (c == 'd')
        {
            Queue_destory(&head, &tail);
            // printf("\nEnter code:");
        }
        else if (c == 'v')
        {
            Queue_visit(&head, &tail);
            // printf("\nEnter code:");
        }
        else
        {
            // printf("Invalid code\n");
            // printf("\nEnter code:");
        }
    }
}