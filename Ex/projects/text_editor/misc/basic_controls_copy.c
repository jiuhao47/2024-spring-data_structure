#include "basic_head.h"
#include "stack.h"
#include "linkedlist.h"
#include "i_o_process.h"
#include "basic_controls.h"
#include "version_manage.h"
#include "piece_table.h"
int state = STATE_COMMAND;
bool state_control(int argc, char *argv[], Stack **undo_head, Stack **redo_head, piece **head, int input, int *cursor, int *text_len)
{
    int temp_place_to_end = *text_len - *cursor;
    // printf("temp_place_to_end=%d\n", temp_place_to_end);
    ElementType top = NULL;
    Stack_top(undo_head, &top);
    if (state == STATE_COMMAND)
    {
        // system("clear");
        printf("-- COMMAND --\n");
        printf("\b");
        if (input == 44)
        {
            *cursor = (*cursor >= 1) ? *cursor - 1 : 0;
            // right
            // keyboard : .
            if (top)
            {
                if (top->op == 2 || top->op == 3)
                {
                    top->op = 4;
                }
            }
            return true;
        }
        else if (input == 46)
        {
            *cursor = (*cursor < *text_len) ? *cursor + 1 : *text_len;
            // left
            // keyboard : ,
            if (top)
            {
                if (top->op == 2 || top->op == 3)
                {
                    top->op = 4;
                }
            }
            return true;
        }
        else if (input == 119)
        {
            if (scanKeyboard() == 10)
            {
                if (file_save(argc, argv, head, *text_len))
                    printf("Save successfully\n");
            }
            if (top)
            {
                if (top->op == 2 || top->op == 3)
                {
                    top->op = 4;
                }
            }
        }
        else if (input == 127)
        {
            // delete???
            // Bug? 2024-04-20
            int tempplace = 0;
            piece *f = *head;
            // piece *pre_f = f;
            while (f)
            {
                tempplace = tempplace + f->length;
                if (tempplace == *cursor)
                {
                    f->length = (f->length >= 1) ? f->length - 1 : 0;
                    break;
                }
                else if (tempplace > *cursor)
                {
                    printf("Middle delete\n");
                    // Bug?
                    // piece *front = NULL;
                    piece *back = NULL;
                    // piece_create(&front, f->text, f->start, f->length - (tempplace - *cursor) - 1);
                    piece_create(&back, f->text, f->start + f->length - (tempplace - *cursor), (tempplace - *cursor));
                    back->next = f->next;
                    f->length = f->length - (tempplace - *cursor) - 1;
                    f->next = back;
                    // front->next = back;
                    /*
                    if (f == *head)
                    {
                        *head = front;
                    }
                    else
                    {
                        pre_f->next = front;
                    }
                    free(f);
                    f = front;
                    */
                    break;
                }
                // pre_f = f;
                f = f->next;
            }
            *cursor = (*cursor >= 1) ? *cursor - 1 : 0;
            *text_len = (*text_len >= 1) ? *text_len - 1 : 0;

            // Bug may be?
            if (Stack_top(undo_head, &top))
            {
                if (top->op == 1 || top->op == 4)
                {
                    ElementType undoUnit = (ElementType)malloc(sizeof(UndoRedoUnit));
                    undoUnit->frontnode = f;
                    undoUnit->op = 2;
                    undoUnit->change_data = 1;
                    undoUnit->cursor = temp_place_to_end;
                    Stack_push(undo_head, undoUnit);
                }
                else if (top->op == 2 || top->op == 3)
                {
                    if (top->frontnode == f)
                    {
                        top->change_data = top->change_data + 1;
                    }
                    else
                    {
                        ElementType undoUnit = (ElementType)malloc(sizeof(UndoRedoUnit));
                        undoUnit->frontnode = f;
                        undoUnit->op = 3;
                        undoUnit->change_data = 1;
                        undoUnit->cursor = temp_place_to_end;
                        Stack_push(undo_head, undoUnit);
                    }
                }
            }
            return true;
        }
        else if (input == 122)
        {
            // undo
            if (scanKeyboard() == 10)
            {
                if (Stack_pop(undo_head, &top))
                {
                    if (top->op == 1)
                    {
                        swap(&top->frontnode->length, &top->change_data);
                        swap(cursor, &top->cursor);
                        // printf("top->cursor=%d\n", top->cursor);
                        Stack_push(redo_head, top);
                    }
                    else
                    {
                        while (top->op > 1 && top->op < 5)
                        {
                            piece_gather(head);
                            top->frontnode->length = top->frontnode->length + top->change_data;
                            *cursor = *text_len - top->cursor + top->change_data;
                            if (top->op == 2)
                            {
                                top->op = 4;
                            }
                            else if (top->op == 4)
                            {
                                top->op = 2;
                            }
                            Stack_push(redo_head, top);
                            Stack_top(undo_head, &top);
                            if (top->op == 1 || top->op == 4)
                            {
                                break;
                            }
                            else
                            {
                                if (Stack_pop(undo_head, &top))
                                {
                                    ;
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                    }
                }
                else
                {
                    ;
                }
            }
        }
        else if (input == 121)
        {
            if (scanKeyboard() == 10)
            {
                if (Stack_pop(redo_head, &top))
                {
                    if (top->op == 1)
                    {
                        swap(&top->frontnode->length, &top->change_data);
                        swap(cursor, &top->cursor);
                        Stack_push(undo_head, top);
                    }
                    else
                    {
                        while (top->op > 1 && top->op < 5)
                        {
                            int temp_place_find = 0;
                            place_find(head, *text_len - top->cursor, &temp_place_find);
                            // 找到光标位置
                            // 返回光标在结点中相对尾端的位置
                            printf("place_find=%d\n", temp_place_find);
                            printf("top->frontnode->next->start=%d\n", top->frontnode->next->start);
                            printf("top->frontnode->length=%d\n", top->frontnode->length);
                            printf("top->op=%d", top->op);
                            piece *redo = top->frontnode->next;
                            while (redo)
                            {
                                printf("Keep finding\n");
                                printf("place_find=%d\n", temp_place_find);
                                printf("redo->start=%d\n", redo->start);
                                printf("sub=%d", top->frontnode->length - temp_place_find + 1);
                                if (redo->start == top->frontnode->length - temp_place_find + 1)
                                {
                                    printf("find!\n");
                                    redo->length = temp_place_find;
                                    break;
                                }
                                redo = redo->next;
                            }
                            top->frontnode->length = top->frontnode->length - temp_place_find - top->change_data + 1;
                            // 对
                            *cursor = *text_len - top->cursor - top->change_data;
                            //?
                            if (top->op == 2)
                            {
                                top->op = 4;
                            }
                            else if (top->op == 4)
                            {
                                top->op = 2;
                            }
                            Stack_push(undo_head, top);
                            Stack_top(redo_head, &top);
                            if (top->op == 1 || top->op == 4)
                            {
                                break;
                            }
                            else
                            {
                                if (Stack_pop(redo_head, &top))
                                {
                                    ;
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                    }
                }
                else
                {
                    ;
                }
            }
        }
    }
    if (input == 27 && state != STATE_COMMAND)
    {
        // system("clear");
        state = STATE_COMMAND;
        printf("\b\b");
        printf("-- COMMAND --\n");
        if (top)
        {
            if (top->op == 2 || top->op == 3)
            {
                top->op = 4;
            }
        }
        return true;
    }
    else if (input == 105 && state != STATE_INSERT)
    {
        // system("clear");
        state = STATE_INSERT;
        printf("-- INSERT --\n");
        return true;
    }
    return false;
}

bool file_input(int argc, char *argv[], char **origin)
{
    if (argc < 2)
    {
        return false;
        // NO file input
    }
    else if (argc > 2)
    {
        printf("Error: Too many input!\n");
        exit(-1);
    }
    else if (argc == 2)
    {
        FILE *file = fopen(argv[1], "r");
        if (file == NULL)
        {
            printf("Error: Can not open file:%s\n", argv[1]);
            fclose(file);
            exit(-1);
        }
        // get file size
        fseek(file, 0, SEEK_END);
        long filesize = ftell(file);
        rewind(file);

        // alloc memory
        char *buffer = (char *)malloc(filesize + 1);
        if (buffer == NULL)
        {
            printf("Error: No enough memory\n");
            fclose(file);
            exit(-1);
        }

        // get file content
        fread(buffer, 1, filesize, file);
        buffer[filesize] = '\0';
        *origin = buffer;
        // printf("文件内容：\n%s\n", buffer);
        fclose(file);
        return true;
    }
}

bool file_save(int argc, char *argv[], piece **head, int text_len)
{
    char *text = (char *)malloc(sizeof(text_len + 1));
    piece *p = *head;
    int place = 0;
    while (p)
    {
        for (int i = 0; i < (*p).length; i++)
        {
            text[place] = (*((*p).text))[(*p).start + i];
            ++place;
        }
        p = p->next;
    }
    text[text_len] = '\0';
    FILE *file = NULL;
    if (argc == 2)
    {
        file = fopen(argv[1], "w");
        if (file == NULL)
        {
            printf("Can not open file:%s\n", argv[1]);
            return false;
        }
    }
    else
    {
        char filename[100];
        printf("Input the filename (less than 100 characters): ");
        scanf("%s", filename);
        file = fopen(filename, "w");
    }
    fprintf(file, "%s", text);
    fclose(file);
    return true;
}

void swap(int *x, int *y)
{
    *x = *y + *x;
    *y = *x - *y;
    *x = *x - *y;
}

void my_numpy()
{
    return;
}
/*
bool piece_undo_record(Stack **Stack_head, piece **head, int *cursor, int input, int *text_len)
{

}
*/