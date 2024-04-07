/**
 * @ IIE, CAS.
 * @ Info  最大值栈
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <time.h>

typedef struct MaxStack
{
    int val;
    int max;
    struct MaxStack *next;
} MaxStack;

int maxStackGetMax(MaxStack *tail)
{
    if (!tail)
    {
        return -1;
    }
    return tail->max;
}

void push(MaxStack **head, MaxStack **tail, int val)
{
    if (!(*head))
    {
        *head = (MaxStack *)malloc(sizeof(MaxStack));
        *tail = *head;
        (*head)->next = NULL;
        (*head)->val = val;
        (*head)->max = val;
    }
    else
    {
        MaxStack *p = (MaxStack *)malloc(sizeof(MaxStack));
        p->next = NULL;
        p->val = val;
        p->max = (*tail)->max > val ? (*tail)->max : val;
        p->next = NULL;
        (*tail)->next = p;
        *tail = p;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    MaxStack *header = NULL;
    MaxStack *tail = NULL;
    for (int i = 1; i <= n; i++)
    {
        int val;
        scanf("%d", &val);
        push(&header, &tail, val);
    }

    int ans = maxStackGetMax(tail);
    printf("%d\n", ans);
    return 0;
}