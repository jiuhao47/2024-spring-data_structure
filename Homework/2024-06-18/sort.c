#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXSIZE 1000000
typedef int KeyType;
typedef struct RedType
{
    KeyType key;
} RedType;

typedef struct SqList
{
    RedType r[MAXSIZE + 1];
    int length;
} SqList;

void ListDisplay(SqList *L)
{
    for (int i = 1; i <= L->length; i++)
    {
        printf("%d ", L->r[i].key);
    }
    printf("\n");
}
void insert_sort(int *array, int size)
{
    for (int i = 1; i < size; i++)
    {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

void bubblesort(int *array, int length)
{
    int i, j, min;
    int temp;
    for (i = 0; i < length - 1; i++)
    {
        min = i;
        for (j = i + 1; j < length; j++)
        {
            if (array[j] < array[min])
            {
                min = j;
            }
        }
        if (min != i)
        {
            temp = array[i];
            array[i] = array[min];
            array[min] = temp;
        }
    }
}

int main()
{
    int length;
    SqList L;
    scanf("%d", &length);
    while (length > MAXSIZE)
    {
        printf("The length is too long, please enter again");
        scanf("%d", &length);
    }
    L.length = length;
    for (int i = 1; i <= length; i++)
    {
        // printf("%dth:", i);
        scanf("%d", &L.r[i].key);
    }
    ListDisplay(&L);
    int sort_mode;
    scanf("%d", &sort_mode);
    if (sort_mode == 1)
    {
        insert_sort(&L.r[1].key, L.length);
        printf("insert sort\n");
        ListDisplay(&L);
    }
    else if (sort_mode == 2)
    {
        printf("bubble sort\n");
        bubblesort(&L.r[1].key, L.length);
        ListDisplay(&L);
    }
    else
    {
        printf("Invalid sort mode");
        return 0;
    }
}