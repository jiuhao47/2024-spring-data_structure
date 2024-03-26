#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    FALSE = 0,
    TRUE = 1
} bool;

typedef int DLlistDataType;

typedef struct double_linked_list
{
    DLlistDataType data;
    DLlist *next;
    DLlist *prev;
} DLlist;

DLlist *DLlist_new_node(DLlistDataType data)
{
    DLlist *p = (DLlist *)malloc(sizeof(DLlist));
    if (p == NULL)
    {
        printf("DList_New_Node: Malloc Error!");
        exit(-1);
    }
    p->data = data;
    p->next = p->prev = NULL;
    return p;
}

DLlist *DLlist_init(void)
{
    DLlist *head = DLlist_new_node(0);
    head->next = head->prev = head;
    return head;
}

bool DLlist_destroy(DLlist *head)
{
}