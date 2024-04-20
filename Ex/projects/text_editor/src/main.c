#include "basic_head.h"

#include "basic_controls.h"

int main(int argc, char *argv[])
{
    State Global_State;
    system("clear");
    Global_State.origin = NULL;
    if (!file_input(argc, argv, &Global_State))
    {
        Global_State.origin = "";
    }
    Global_State.addbuf = (char *)malloc(sizeof(char) * STR_LEN);
    Global_State.head = NULL;
    int start = 0;
    int now = 0;
    Global_State.cursor = strlen(Global_State.origin);
    Global_State.text_len == strlen(Global_State.origin);
    piece_list_init(&Global_State);
    printf(TITLE);
    printf(COMMAND);
    pieces_show(&Global_State);
    while (state)
    {
        int input = 0;
        input = scanKeyboard();
        if (state_control(argc, argv, input, &Global_State))
        {
            // Insert!

            if (input == 27)
            {
                if (now - start)
                {
                    piece_insert(&Global_State, now - start, start);
                }
                Global_State.cursor = Global_State.cursor + now - start;
                start = now;
                pieces_show(&Global_State);
            }
        }
        else
        {
            if (state == STATE_INSERT)
            {
                addbuf_append(input, &Global_State);
                ++now;
            }
        }
    }
    free(Global_State.addbuf);
}

void addbuf_append(char c, State *global_state)
{
    static int i_add = 0;
    static int length = STR_LEN;
    if (i_add < length)
    {
        (global_state->addbuf)[i_add] = c;
    }
    else
    {
        length *= 2;
        global_state->addbuf = realloc(global_state->addbuf, length * sizeof(char));
        if (global_state->addbuf == NULL)
        {
            printf("Memory reallocation failed\n");
            exit(1);
        }
        memset(global_state->addbuf + i_add, 0, (length - i_add) * sizeof(char)); // 将新分配的内存空间设置为0
        (global_state->addbuf)[i_add] = c;
    }
    i_add++;
}
