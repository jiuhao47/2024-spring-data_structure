#include "basic_head.h"
#include "piece_table.h"
#include "linkedlist.h"
#include "i_o_process.h"
#include "basic_controls.h"
#include "version_manage.h"

void addbuf_append(char c, char **addbuf);

int main(int argc, char *argv[])
{

    system("clear");
    char *origin = NULL;
    if (!file_input(argc, argv, &origin))
    {
        origin = "";
    }
    char *addbuf = (char *)malloc(sizeof(char) * STR_LEN);
    piece *head = NULL;
    int start = 0;
    int now = 0;
    int cursor = strlen(origin);
    int text_len = strlen(origin);
    piece_list_init(&head, &origin);
    printf(TITLE);
    printf(COMMAND);
    pieces_show(&head, cursor, &text_len);
    while (state)
    {
        int input = 0;
        input = scanKeyboard();
        // printf("%d", input);
        if (state_control(argc, argv, &head, input, &cursor, &text_len))
        {
            // Insert!

            if (input == 27)
            {
                if (now - start)
                {
                    piece_insert(&head, &origin, &addbuf, now - start, start, cursor);
                }
                cursor = cursor + now - start;
                start = now;
                pieces_show(&head, cursor, &text_len);
            }
        }
        else
        {
            if (state == STATE_INSERT)
            {
                addbuf_append(input, &addbuf);
                ++now;
            }
        }
    }
    free(addbuf);
}

void addbuf_append(char c, char **addbuf)
{
    static int i_add = 0;
    static int length = STR_LEN;
    if (i_add < length)
    {
        (*addbuf)[i_add] = c;
    }
    else
    {
        length *= 2;
        *addbuf = realloc(*addbuf, length * sizeof(char));
        if (*addbuf == NULL)
        {
            printf("Memory reallocation failed\n");
            exit(1);
        }
        memset(*addbuf + i_add, 0, (length - i_add) * sizeof(char)); // 将新分配的内存空间设置为0
        (*addbuf)[i_add] = c;
    }
    i_add++;
}
