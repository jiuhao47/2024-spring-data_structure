#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node;

typedef struct HashTable
{
    node *firstNode;
} HashTable;
void HashTable_insert(HashTable *table, int key, int size);
void HashTable_create(HashTable **table, int *key, int key_table_len);
void HashTable_display(HashTable *table, int size);
void HashTable_delete(HashTable *table, int key, int size);
void HashTable_search(HashTable *table, int key, int size);
void HashTable_destroy(HashTable *table, int size);
void HashTable_ASL_cal(HashTable *table, int size);
void HashTable_create(HashTable **table, int *key, int key_table_len)
{
    // int size;
    // printf("Input the size of Hashtable: ");
    // scanf("%d", size);
    *table = (HashTable *)malloc(sizeof(HashTable) * key_table_len);
    for (int i = 0; i < key_table_len; i++)
    {
        (*table)[i].firstNode = NULL;
    }
    for (int i = 0; i < key_table_len; i++)
    {
        HashTable_insert(*table, key[i], key_table_len);
    }
}

void HashTable_insert(HashTable *table, int key, int size)
{
    int index = key % size;
    if (table[index].firstNode == NULL)
    {
        table[index].firstNode = (node *)malloc(sizeof(node));
        table[index].firstNode->data = key;
        table[index].firstNode->next = NULL;
    }
    else
    {
        node *temp = table[index].firstNode;
        while (temp->next != NULL)
        {
            if (temp->next->data == key)
            {
                return;
            }
            temp = temp->next;
        }
        temp->next = (node *)malloc(sizeof(node));
        temp->next->data = key;
        temp->next->next = NULL;
    }
}

void HashTable_display(HashTable *table, int size)
{
    printf("HashTable Display:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d: ", i);
        if (table[i].firstNode != NULL)
        {
            node *temp = table[i].firstNode;
            while (temp != NULL)
            {
                printf("%d ->", temp->data);
                temp = temp->next;
            }
        }
        printf("\n");
    }
}

void HashTable_delete(HashTable *table, int key, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (table[i].firstNode != NULL)
        {
            node *temp = table[i].firstNode;
            if (temp->data == key)
            {
                table[i].firstNode = temp->next;
                free(temp);
                return;
            }
            while (temp->next != NULL)
            {
                if (temp->next->data == key)
                {
                    node *temp2 = temp->next;
                    temp->next = temp2->next;
                    free(temp2);
                    return;
                }
                temp = temp->next;
            }
        }
    }
}

void HashTable_search(HashTable *table, int key, int size)
{
    for (int i = 0; i < size; i++)
    {
        int search_len = 0;
        if (table[i].firstNode != NULL)
        {
            node *temp = table[i].firstNode;
            while (temp != NULL)
            {
                if (temp->data == key)
                {
                    // printf("Found %d at index %d offset %d\n", key, i, search_len);
                    printf("yes\n");
                    return;
                }
                temp = temp->next;
                search_len++;
            }
        }
    }
    printf("no\n");
}

void HashTable_destroy(HashTable *table, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (table[i].firstNode != NULL)
        {
            node *temp = table[i].firstNode;
            while (temp != NULL)
            {
                node *temp2 = temp;
                temp = temp->next;
                free(temp2);
            }
        }
    }
    free(table);
}

void HashTable_ASL_cal(HashTable *table, int size)
{
    int success_sum = 0;
    int fail_num = 0;
    int num_node = 0;
    for (int i = 0; i < size; i++)
    {
        int temp_len = 0;
        if (table[i].firstNode != NULL)
        {
            node *temp = table[i].firstNode;
            while (temp != NULL)
            {
                temp_len++;
                success_sum += temp_len;
                num_node++;
                temp = temp->next;
            }
            fail_num += temp_len;
        }
    }
    printf("Average Search Length: %f\n", (float)success_sum / num_node);
    printf("Average Search Length for Unsuccessful Search: %f\n", (float)fail_num / size);
}

int main()
{
    int key_table_len;
    scanf("%d", &key_table_len);
    int search_len;
    scanf("%d", &search_len);
    int key_table[key_table_len];
    HashTable *table;

    for (int i = 0; i < key_table_len; i++)
    {
        scanf("%d", &key_table[i]);
    }
    HashTable_create(&table, key_table, key_table_len);

    for (int i = 0; i < search_len; i++)
    {
        int key;
        scanf("%d", &key);
        HashTable_search(table, key, key_table_len);
    }
}