/**
 * @ IIE, CAS.
 * @ Info  删除大值节点
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

void solve(LinkedList *header, int mx)
{
    LinkedList *p = (LinkedList *)malloc(sizeof(LinkedList));
    LinkedList *q;
    p->next = header;
    while (p->next != NULL)
    {
        // printf("Read:%d\n", p->next->val);
        if ((p->next->next != NULL) && (p->next->next->val > mx))
        {
            // printf("Delete %d\n", p->next->next->val);
            q = p->next->next;
            if (p->next->next->next != NULL)
            {
                p->next->next = p->next->next->next;
            }
            else
            {
                p->next->next = NULL;
            }
            free(q);
        }
        else
        {
            p->next = p->next->next;
        }
    }
}

int main()
{
    int n, mx; // n为链表节点数，mx待删除链表阈值
    scanf("%d %d", &n, &mx);
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
// ps.除main函数的内容外，其他地方可以自行更改。