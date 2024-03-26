/**
 * @ IIE, CAS.
 * @ Info  删除并复制节点
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

typedef struct LinkedList
{
    int val;
    struct LinkedList *next;
} LinkedList;

void solve(LinkedList *header, int remove)
{
    LinkedList *p = (LinkedList *)malloc(sizeof(LinkedList));
    LinkedList *q = (LinkedList *)malloc(sizeof(LinkedList));
    LinkedList *t = (LinkedList *)malloc(sizeof(LinkedList));
    q->next = p->next = header;
    for (int i = 0; i < remove; i++)
    {
        if (p->next->next != NULL)
        {
            p->next = p->next->next;
        }
        else
        {
            printf("Error!\n");
        }
    }
    while (p->next->next != NULL)
    {
        q->next = q->next->next;
        p->next = p->next->next;
    }
    t->next = q->next->next;
    if (q->next->next->next != NULL)
    {
        q->next->next = q->next->next->next;
    }
    else
    {
        q->next->next = NULL;
    }
    free(t);
    q->next->val = q->next->next->val;
}

int main()
{
    int n, mx;
    scanf("%d%d", &n, &mx); // n为链表节点数，mx即为待删除第mx个节点
    LinkedList *header = NULL;
    LinkedList *tail = NULL;
    for (int i = 1; i <= n + 1; i++)
    {
        int val;
        scanf("%d", &val);
        if (!header)
        {
            header = (LinkedList *)malloc(sizeof(LinkedList));
            tail = header;
            tail->next = NULL;
            tail->val = val;
        }
        else
        {
            LinkedList *node = (LinkedList *)malloc(sizeof(LinkedList));
            node->val = val;
            node->next = NULL;
            tail->next = node;
            tail = node;
        }
    }

    solve(header, mx);

    for (LinkedList *it = header; it != NULL; it = it->next)
    {
        printf("%d ", it->val);
    }
    puts("");
    return 0;
}