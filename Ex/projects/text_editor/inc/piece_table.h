#ifndef _PIECE_TABLE_H
#define _PIECE_TABLE_H
typedef struct piece
{
    char *text;
    int start;
    int length;
    struct piece *next;
    // 可优化点，单链表存储
} piece;
bool piece_create(piece **node, char *text, int start, int length);
bool piece_list_init(piece **head, char *origin);
bool piece_insert(piece **head, char *add, int insert_len, int start, int insert_place);
#endif