#include "basic_head.h"
#include "stack.h"
#include "linkedlist.h"
#include "i_o_process.h"
#include "basic_controls.h"
#include "version_manage.h"
#include "piece_table.h"
bool piece_create(piece **node, char *text, int start, int length)
{
    if (!(*node))
    {
        piece *p = (piece *)malloc(sizeof(piece));
        p->length = length;
        p->start = start;
        p->text = text;
        p->next = NULL;
        (*node) = p;
        return true;
    }
    else
    {
        printf("Piece_create: Create Error!\n");
        return false;
        // piece already exists;
    }
}

bool piece_list_init(piece **head, char *origin)
{
    return piece_create(head, origin, 0, strlen(origin));
}

bool piece_insert(piece **head, char *add, int insert_len, int start, int insert_place)
{
    // strappend(add,text);
    // abandoned
    piece *temp;
    if (!piece_create(&temp, add, start, insert_len))
    {
        return false;
    }
    int temp_place = 0;
    int gap = 0;
    piece *f = (piece *)malloc(sizeof(piece));
    f->length = f->start = 0;
    f->text = NULL;
    f = *head;
    // piece *f = *head;
    //?Only head
    //?ahead none!~?
    while (f)
    {
        temp_place = temp_place + f->length;
        if (temp_place > insert_place)
        {
            break;
        }
        else if (temp_place == insert_place)
        {
            gap = 1;
            break;
        }
        else
        {
            f = f->next;
        }
    }
    if (gap)
    {
        temp->next = f->next;
        f->next = temp;
        return true;
    }
    else
    {
        piece *front;
        piece *back;
        piece_create(&front, add, f->next->start, f->next->length - (temp_place - insert_place));
        piece_create(&back, add, f->next->start + front->length, (temp_place - insert_place));
        piece *p_free = f->next;
        front->next = temp;
        temp->next = back;
        back->next = f->next->next;
        f->next = front;
        // f->front->temp->back->f->next->next;
        free(p_free);
        return true;
    }
}

bool pieces_show(piece **head)
{
    piece *p = head;
    while (p)
    {

        p = p->next;
    }
}