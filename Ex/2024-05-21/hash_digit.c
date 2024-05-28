#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int data;
    struct Node *next;
} Node;
int main()
{
    int key_table_len;
    scanf("%d", &key_table_len);
    int search_len;
    scanf("%d", &search_len);
    Node *key[key_table_len];
    for (int i = 0; i < key_table_len; i++)
    {
        key[i] = (Node *)malloc(sizeof(Node));
        key[i]->data = -1;
        key[i]->next = NULL;
    }
    for (int i = 0; i < key_table_len; i++)
    {
        int key_input;
        scanf("%d", &key_input);
        int index = key_input % key_table_len;
        if (key[index]->data == -1)
        {
            key[index]->data = key_input;
            key[index]->next = NULL;
        }
        else
        {
            Node *temp = key[index];
            while (temp->next != NULL)
            {
                if (temp->next->data == key_input)
                {
                    return 0;
                }
                temp = temp->next;
            }
            temp->next = (Node *)malloc(sizeof(Node));
            temp->next->data = key_input;
            temp->next->next = NULL;
        }
    }
    for (int i = 0; i < search_len; i++)
    {
        int search_input;
        scanf("%d", &search_input);
        int index = search_input % key_table_len;
        Node *temp = key[index];
        while (temp != NULL)
        {
            if (temp->data == search_input)
            {
                printf("yes\n");
                break;
            }
            temp = temp->next;
        }
        if (temp == NULL)
        {
            printf("no\n");
        }
    }
}
