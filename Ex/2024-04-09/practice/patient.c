#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
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
    if (!(*head))
    {
        (*head) = (Queue *)malloc(sizeof(Queue));
        (*tail) = (Queue *)malloc(sizeof(Queue));
        (*head)->next = (Queue *)malloc(sizeof(Queue));

        (*head)->next->data = data;
        (*tail)->next = (*head)->next;
    }
    else
    {
        (*tail)->next->next = (Queue *)malloc(sizeof(Queue));
        (*tail)->next = (*tail)->next->next;
        (*tail)->next->data = data;
        (*tail)->next->next = NULL;
    }
}

bool Queue_out(Queue **head, Queue **tail, int *data)
{
    if ((*head)->next == NULL)
    {
        return false;
    }
    else
    {
        *data = (*head)->next->data;
        Queue *p = (*head)->next;
        (*head)->next = p->next;
        free(p);
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
    printf("Now queue:");
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("<-\n");
    return true;
}

int main()
{
    Queue *head = NULL;
    Queue *tail = NULL;
    char c;
    int num;
    printf("Input what you want to do:\ni:Patient EnQueue\ne:Patient DeQueue\nv:Show the Queue Now\nd:Destory Queue and Exit\nInput:");
    while ((c = getchar()) != 'q')
    {
        printf("-------------------------\n");
        if (c == 'i')
        {
            printf("Insert number:");
            scanf("%d", &num);
            Queue_in(&head, &tail, num);
            Queue_visit(&head, &tail);
        }
        else if (c == 'e')
        {
            if (head)
            {
                if (Queue_out(&head, &tail, &num))
                {
                    printf("Exit number:%d\n", num);
                }
                else
                {
                    printf("Now Empty Queue!\n");
                }
            }
            else
            {
                printf("Queue Not Exist\n");
            }
        }
        else if (c == 'd')
        {
            if (head)
            {
                Queue_destory(&head, &tail);
                printf("Queue Destory\n");
                printf("-------------------------\n");
                exit(0);
            }
            else
            {
                printf("Queue Not Exist\n");
            }
        }
        else if (c == 'v')
        {
            if (head)
            {
                Queue_visit(&head, &tail);
            }
            else
            {
                printf("Queue Not Exist\n");
            }
        }
        else
        {
            printf("Invalid Code!\n");
        }
        getchar();
        printf("-------------------------\n");
        printf("\nInput what you want to do:\ni:Patient EnQueue\ne:Patient DeQueue\nv:Show the Queue Now\nd:Destory Queue and Exit\nInput:");
    }
}