#include "basic_head.h"
#include "stack.h"
#include "linkedlist.h"
#include "i_o_process.h"
#include "basic_controls.h"
#include "version_manage.h"
#include "piece_table.h"
void addbuf_append(char c, char **addbuf);
int main()
{

    char *origin = "Hello World!\n";
    char *addbuf = (char *)malloc(sizeof(char) * STR_LEN);
    int start = 0;
    int now = 0;
    piece *head = NULL;
    piece_list_init(&head, origin);
    int cursor = strlen(origin);
    while (state)
    {
        int input;
        input = scanKeyboard();
        if (state_control(input))
        {
            // Insert!
            // printf("State Changed!\n");
            piece_insert(&head, addbuf, now - start, start, cursor);
        }
        else
        {
            if (state == STATE_INSERT)
            {
                addbuf_append(input, &addbuf);
                ++now;
            }
            // printf("Just input!\n");
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
    printf("\n");
    for (int i = 0; i < length; i++)
    {
        printf(" %d", (*addbuf)[i]);
    }
    printf("\n");
}
