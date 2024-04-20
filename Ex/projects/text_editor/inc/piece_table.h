#ifndef _PIECE_TABLE_H
#define _PIECE_TABLE_H
typedef struct piece
{
    char **text;
    int start;
    int length;
    struct piece *next;
    // 可优化点，单链表存储
} piece;

bool file_save(int argc, char *argv[], piece **head, int text_len);
bool state_control(int argc, char *argv[], piece **head, int input, int *cursor, int *text_len);
bool piece_create(piece **node, char **text, int start, int length);
bool piece_list_init(piece **head, char **origin);
bool piece_insert(piece **head, char **origin, char **add, int insert_len, int start, int insert_place);
bool pieces_show(piece **head, int cursor, int *text_len);
bool place_find(piece **head, int cursor, int *place_find);
// bool piece_gather(piece **head);
#endif