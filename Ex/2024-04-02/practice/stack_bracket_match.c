/**
 * @ IIE, CAS.
 * @ Info  不是很有效的括号匹配
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct Stack
{
    int val;
    struct Stack *next;
} Stack;

void push(Stack **head, int val)
{
    if (!(*head))
    {
        *head = (Stack *)malloc(sizeof(Stack));
        (*head)->val = val;
        (*head)->next = NULL;
    }
    else
    {
        Stack *p = (Stack *)malloc(sizeof(Stack));
        p->val = val;
        p->next = (*head);
        (*head) = p;
    }
}

bool pop(Stack **head, int *val)
{
    if (!(*head))
    {
        return false;
        // Empty Stack
    }
    else
    {
        *val = (*head)->val;
        Stack *p = (*head);
        (*head) = p->next;
        free(p);
        return true;
    }
}
bool isValidWithOneModification(char *s)
{
    Stack *head = NULL;
    int permit = 1;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[')
        {
            push(&head, s[i]);
        }
        else if (s[i] == ')' || s[i] == '}' || s[i] == ']')
        {
            int val;
            if (!pop(&head, &val))
            {
                return false;
            }
            else
            {
                switch (val)
                {
                case '{':
                    val = '}';
                    break;
                case '(':
                    val = ')';
                    break;
                case '[':
                    val = ']';
                    break;
                default:;
                }
                // printf("Read:%c;Pop:%c\n", s[i], val);
                // printf("Permit=%d,\n", permit);
                if (val == s[i])
                {
                    continue;
                }
                else if (permit)
                {
                    permit = 0;
                    continue;
                }
                else
                {
                    return false;
                }
            }
        }
    }
    if (head != NULL)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int main()
{
    char s[1001];
    scanf("%1000s", &s);
    if (isValidWithOneModification(s))
    {
        printf("%d\n", 1);
    }
    else
    {
        printf("%d\n", 0);
    }

    return 0;
}
