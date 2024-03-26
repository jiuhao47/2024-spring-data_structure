/**
 * @ IIE, CAS.
 * @ Info  获取中间值
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

int solve(LinkedList *header)
{
    int i = 1;
    LinkedList *fast = (LinkedList *)malloc(sizeof(LinkedList));
    LinkedList *slow = (LinkedList *)malloc(sizeof(LinkedList));
    slow->val = fast->val = 0;
    slow->next = fast->next = header;
    while (fast->next->next != NULL)
    {
        fast->next = fast->next->next;
        if (fast->next->next != NULL)
        {
            fast->next = fast->next->next;
        }
        else
        {
            return slow->next->val;
        }
        slow->next = slow->next->next;
    }
    return slow->next->val;
}

int main()
{
    int n;
    scanf("%d", &n);
    LinkedList *header = NULL;
    LinkedList *tail = NULL;
    for (int i = 1; i <= n; i++)
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

    int ans = solve(header);
    printf("%d\n", ans);
    return 0;
}