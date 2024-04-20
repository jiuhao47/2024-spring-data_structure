#include "basic_head.h"
#include "linkedlist.h"
#include "i_o_process.h"
#include "basic_controls.h"
#include "version_manage.h"
#include "piece_table.h"
bool piece_create(piece **node, char **text, int start, int length)
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

bool piece_list_init(piece **head, char **origin)
{
    return piece_create(head, origin, 0, strlen(*origin));
}

bool piece_insert(piece **head, char **origin, char **add, int insert_len, int start, int insert_place)
{
    int temp_start = insert_place;
    piece *temp = NULL;
    if (!piece_create(&temp, add, start, insert_len))
    {
        return false;
    }
    int temp_place = 0;
    int gap = 0;
    piece *f = (piece *)malloc(sizeof(piece));
    piece *pre_f = NULL;
    f->length = f->start = 0;
    f->text = NULL;
    f->next = *head;
    pre_f = f->next;
    while (f->next)
    {
        temp_place = temp_place + f->next->length;
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
            pre_f = f->next;
            f->next = f->next->next;
        }
    }
    if (gap)
    {
        temp->next = f->next->next;
        f->next->next = temp;
    }
    else
    {
        piece *front = NULL;
        piece *back = NULL;
        piece_create(&front, f->next->text, f->next->start, f->next->length - (temp_place - insert_place));
        piece_create(&back, f->next->text, f->next->start + f->next->length - (temp_place - insert_place), (temp_place - insert_place));
        front->next = temp;
        temp->next = back;
        back->next = f->next->next;
        if (f->next == *head)
        {
            *head = front;
            pre_f = *head;
        }
        else
        {
            pre_f->next = front;
        }
    }
    return true;
}

bool pieces_show(piece **head, int cursor, int *text_len)
{

    piece *p = *head;
    int place = 0;
    int count = 0;
    while (p)
    {
        if ((cursor == 0) & (cursor == place) & (count == 0))
        {
            printf("\033[7m \033[m");
        }
        for (int i = 0; i < (*p).length; i++)
        {

            printf("%c", (*((*p).text))[(*p).start + i]);
            ++place;
            if (cursor == place)
            {
                printf("\033[7m \033[m");
            }
        }
        ++count;
        p = p->next;
    }
    printf("\nEditor:");
    *text_len = place;
    return true;
}

bool place_find(piece **head, int cursor, int *place)
{
    int tempplace = 0;
    piece *f = *head;
    while (f)
    {
        tempplace = tempplace + f->length;
        if (tempplace >= cursor)
        {
            *place = tempplace - cursor + 1;
            break;
        }
        f = f->next;
    }
}