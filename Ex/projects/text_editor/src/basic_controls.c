#include "basic_head.h"
#include "basic_controls.h"
int state = STATE_COMMAND;
int scanKeyboard()
{
    int in;
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(0, &stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(0, &stored_settings);
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &new_settings);

    in = getchar();

    tcsetattr(0, TCSANOW, &stored_settings);
    return in;
}
bool state_control(int argc, char *argv[], int input, State *global_state)
{
    if (state == STATE_COMMAND)
    {
        if (input == 10)
        {
            printf("\033[F");
        }
        else if (input != 119)
            printf("\b \b");
        if (input == 44)
        {
            system("clear");
            printf(TITLE);
            printf(COMMAND);

            global_state->cursor = (global_state->cursor >= 1) ? global_state->cursor - 1 : 0;
            // right
            // keyboard : .
            pieces_show(global_state);
            return true;
        }
        else if (input == 46)
        {
            system("clear");
            printf(TITLE);
            printf(COMMAND);

            global_state->cursor = (global_state->cursor < global_state->text_len) ? global_state->cursor + 1 : global_state->text_len;
            // left
            // keyboard : ,
            pieces_show(global_state);
            return true;
        }
        else if (input == 119)
        {
            if (scanKeyboard() == 10)
            {
                if (file_save(argc, argv, global_state))
                    printf("Save successfully\n");
            }
            else
            {
                system("clear");
                printf(TITLE);
                printf(COMMAND);
                pieces_show(global_state);
            }
        }
        else if (input == 127)
        {
            system("clear");
            printf(TITLE);
            printf(COMMAND);
            // delete
            int tempplace = 0;
            piece *f = global_state->head;
            piece *pre_f = f;
            while (f)
            {
                tempplace = tempplace + f->length;
                if (tempplace == global_state->cursor)
                {
                    f->length = (f->length >= 1) ? f->length - 1 : 0;
                    break;
                }
                else if (tempplace > global_state->cursor)
                {
                    piece *front = NULL;
                    piece *back = NULL;
                    piece_create(&front, f->text, f->start, f->length - (tempplace - global_state->cursor) - 1);
                    piece_create(&back, f->text, f->start + f->length - (tempplace - global_state->cursor), (tempplace - global_state->cursor));
                    front->next = back;
                    back->next = f->next;
                    if (f == global_state->head)
                    {
                        global_state->head = front;
                        pre_f = global_state->head;
                    }
                    else
                    {
                        pre_f->next = front;
                    }
                    break;
                }
                pre_f = f;
                f = f->next;
            }
            global_state->cursor = (global_state->cursor >= 1) ? global_state->cursor - 1 : 0;
            global_state->text_len = (global_state->text_len >= 1) ? global_state->text_len - 1 : 0;
            pieces_show(global_state);
            return true;
        }
        else if (input == 113)
        {
            exit(0);
        }
    }
    if (input == 27 && state != STATE_COMMAND)
    {
        system("clear");
        state = STATE_COMMAND;
        printf("\b\b");
        printf(TITLE);
        printf(COMMAND);
        return true;
    }
    else if (input == 105 && state != STATE_INSERT)
    {
        system("clear");
        state = STATE_INSERT;
        printf(TITLE);
        printf(INSERT);
        pieces_show(global_state);
        return true;
    }
    return false;
}

bool file_input(int argc, char *argv[], State *global_state)
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
        fread(buffer, 1, filesize, file);
        buffer[filesize] = '\0';
        global_state->origin = buffer;
        fclose(file);
        return true;
    }
}

bool file_save(int argc, char *argv[], State *global_state)
{
    char *text = (char *)malloc(sizeof(global_state->text_len + 1));
    piece *p = global_state->head;
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
    text[global_state->text_len] = '\0';
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
