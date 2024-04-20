#ifndef _BASIC_CONTROLS_H
#define _BASIC_CONTROLS_H
#define STR_LEN 16
#define STATE_COMMAND 1
#define STATE_INSERT 2
#define STATE_OFF 0
typedef struct piece
{
    char **text;
    int start;
    int length;
    struct piece *next;
    // 可优化点，单链表存储
} piece;

typedef struct State
{
    int state;
    int text_len;
    int cursor;
    char *addbuf;
    char *origin;
    piece *head;
} State;

extern State Global_State;
extern int state;

bool state_control(int argc, char *argv[], int input, State *global_state);

void addbuf_append(char c, State *global_state);
bool piece_create(piece **node, char **text, int start, int length);
bool piece_list_init(State *global_state);
bool piece_insert(State *global_state, int insert_len, int start);
bool pieces_show(State *global_state);

bool file_input(int argc, char *argv[], State *global_state);
bool file_save(int argc, char *argv[], State *global_state);
int scanKeyboard();
#endif