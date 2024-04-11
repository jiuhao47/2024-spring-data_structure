#include "basic_head.h"
#include "stack.h"
#include "linkedlist.h"
#include "i_o_process.h"
#include "basic_controls.h"
#include "version_manage.h"
int state = STATE_COMMAND;
void state_control()
{
    int input;
    input = scanKeyboard();
    if (state == STATE_COMMAND)
    {
        printf("\b");
    }
    if (input == 27 && state != STATE_COMMAND)
    {
        state = STATE_COMMAND;
        printf("\b\b");
        printf("Now Command mode\n");
    }
    else if (input == 105 && state != STATE_INSERT)
    {
        state = STATE_INSERT;
        printf("Now Insert mode\n");
    }
}