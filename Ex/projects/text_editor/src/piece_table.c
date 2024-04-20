#include "basic_head.h"
#include "basic_controls.h"
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

bool piece_list_init(State *global_state)
{
    return piece_create(&global_state->head, &global_state->origin, 0, strlen(global_state->origin));
}

bool piece_insert(State *global_state, int insert_len, int start)
{
    int temp_start = global_state->cursor;
    piece *temp = NULL;
    if (!piece_create(&temp, &global_state->addbuf, start, insert_len))
    {
        return false;
    }
    int temp_place = 0;
    int gap = 0;
    piece *f = (piece *)malloc(sizeof(piece));
    piece *pre_f = NULL;
    f->length = f->start = 0;
    f->text = NULL;
    f->next = global_state->head;
    pre_f = f->next;
    while (f->next)
    {
        temp_place = temp_place + f->next->length;
        if (temp_place > global_state->cursor)
        {
            break;
        }
        else if (temp_place == global_state->cursor)
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
        piece_create(&front, f->next->text, f->next->start, f->next->length - (temp_place - global_state->cursor));
        piece_create(&back, f->next->text, f->next->start + f->next->length - (temp_place - global_state->cursor), (temp_place - global_state->cursor));
        front->next = temp;
        temp->next = back;
        back->next = f->next->next;
        if (f->next == global_state->head)
        {
            global_state->head = front;
            pre_f = global_state->head;
        }
        else
        {
            pre_f->next = front;
        }
    }
    return true;
}

bool pieces_show(State *global_state)
{

    piece *p = global_state->head;
    if (!p)
    {
        // list not exist
        return false;
    }
    int place = 0;
    int count = 0;
    while (p)
    {
        if ((global_state->cursor == 0) & (global_state->cursor == place) & (count == 0))
        {
            printf("\033[7m \033[m");
        }
        for (int i = 0; i < (*p).length; i++)
        {

            printf("%c", (*((*p).text))[(*p).start + i]);
            ++place;
            if (global_state->cursor == place)
            {
                printf("\033[7m \033[m");
            }
        }
        ++count;
        p = p->next;
    }
    printf("\nEditor:");
    global_state->text_len = place;
    return true;
}