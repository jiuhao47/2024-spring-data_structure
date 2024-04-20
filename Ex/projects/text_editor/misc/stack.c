#include "basic_head.h"
#include "stack.h"
#include "linkedlist.h"
#include "i_o_process.h"
#include "basic_controls.h"
#include "version_manage.h"
#include "piece_table.h"

bool Stack_init(Stack **head)
{
    if (!(*head))
    {
        (*head) = (Stack *)malloc(sizeof(Stack));
        (*head)->next = NULL;
        (*head)->data = 0;
        // Stack initialized successfully;
        return true;
    }
    else
    {
        // Stack already initialized;
        return false;
    }
}

bool Stack_push(Stack **head, ElementType data)
{
    if (!(*head))
    {
        // Stack do not exist;
        return false;
    }
    else
    {
        Stack *p = (Stack *)malloc(sizeof(Stack));
        p->data = data;
        p->next = (*head)->next;
        (*head)->next = p;
        return true;
        // Push successfully;
    }
}

bool Stack_pop(Stack **head, ElementType *data)
{
    if (!(*head))
    {
        return false;
        // Stack do not exist;
    }
    else
    {
        if (!((*head)->next))
        {
            return false;
            // Stack empty;
        }
        else
        {
            Stack *q = (Stack *)malloc(sizeof(Stack));
            q = (*head)->next;
            *data = q->data;
            (*head)->next = q->next;
            free(q);
            return true;
            // Pop successfully;
        }
    }
}

bool Stack_top(Stack **head, ElementType *data)
{
    if (!(*head))
    {
        return false;
        // Stack do not exist;
    }
    else
    {
        if (!((*head)->next))
        {
            return false;
            // Stack empty;
        }
        else
        {
            *data = (*head)->next->data;
            return true;
            // top visit successfully;
        }
    }
}