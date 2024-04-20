#ifndef _STACK_H
#define _STACK_H
typedef struct UndoRedoUnit
{
    int op;
    piece *pre_node;
    piece *node;
} UndoRedoUnit;

typedef UndoRedoUnit *ElementType;
typedef struct Stack
{
    ElementType data;
    struct Stack *next;
} Stack;
bool Stack_init(Stack **head);
bool Stack_push(Stack **head, ElementType data);
bool Stack_pop(Stack **head, ElementType *data);
bool Stack_top(Stack **head, ElementType *data);

#endif