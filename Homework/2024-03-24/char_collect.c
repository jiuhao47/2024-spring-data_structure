#include <stdio.h>
#include <stdlib.h>

typedef int ValType;

typedef struct singlelinkedlist
{
    ValType val;
    int count;
    struct singlelinkedlist *next;
} SLList;
SLList *SLList_init();
void SLList_insert(SLList *head, ValType data);
void SLList_print(SLList *head);
SLList *SLList_init()
{
    SLList *p = (SLList *)malloc(sizeof(SLList));
    p->val = -1;
    p->count = -1;
    p->next = NULL;
    return p;
}

void SLList_insert(SLList *head, ValType data)
{
    SLList *p = (SLList *)malloc(sizeof(SLList));
    p->next = head;
    while (p->next->next != NULL)
    {
        p->next = p->next->next;
        if (p->next->val == data)
        {
            p->next->count++;
            return;
        }
    }
    if (p->next->val == data)
    {
        p->count++;
        return;
    }
    p->count = 1;
    p->val = data;
    p->next->next = p;
    p->next = NULL;
}

void SLList_print(SLList *head)
{
    SLList *p = (SLList *)malloc(sizeof(SLList));
    p->next = head->next;
    while (p->next != NULL)
    {
        printf("Char:%c;Count:%d\n", p->next->val, p->next->count);
        p->next = p->next->next;
    }
}
int main()
{
    SLList *head;
    head = SLList_init();
    ValType c;
    while ((c = getchar()) != '\n')
    {
        SLList_insert(head, c);
    }
    SLList_print(head);
    return 0;
}