#include <stdio.h>
#include <stdlib.h>
struct SqQueue
{
    int *base;
    int head;
    int back;
    int count;
    int MAX;
};
int SqQueue_init(struct SqQueue *SqQueue, int max);
int SqQueue_EnQueue(struct SqQueue *SqQueue, int data);
int SqQueue_DeQueue(struct SqQueue *SqQueue, int *data);
int SqQueue_GetHead(struct SqQueue *SqQueue, int *data);
int SqQueue_Destroy(struct SqQueue *SqQueue);
int solve(int x, int y);

int SqQueue_init(struct SqQueue *SqQueue, int max)
{
    SqQueue->base = (int *)malloc(max * sizeof(int));
    if (!SqQueue->base)
    {
        return 0;
    }
    SqQueue->MAX = max;
    SqQueue->head = SqQueue->back = SqQueue->count = 0;
    return 1;
}

int SqQueue_EnQueue(struct SqQueue *SqQueue, int data)
{
    if (SqQueue->count == SqQueue->MAX)
    {
        return 0;
    }
    SqQueue->base[SqQueue->back] = data;
    SqQueue->back = (SqQueue->back + 1) % SqQueue->MAX;
    SqQueue->count++;
    return 1;
}

int SqQueue_DeQueue(struct SqQueue *SqQueue, int *data)
{
    if (SqQueue->count == 0)
    {
        return 0;
    }
    *data = SqQueue->base[SqQueue->head];
    SqQueue->head = (SqQueue->head + 1) % SqQueue->MAX;
    SqQueue->count--;
    return 1;
}

int SqQueue_GetHead(struct SqQueue *SqQueue, int *data)
{
    if (SqQueue->count == 0)
    {
        return 0;
    }
    *data = SqQueue->base[SqQueue->head];
    return 1;
}

int SqQueue_Destroy(struct SqQueue *SqQueue)
{
    free(SqQueue->base);
    return 1;
}

int main()
{
    int n, k;
    int max;
    int f_0 = 1;
    int f_1 = 1;
    printf("Enter the k you want:");
    scanf("%d", &k);
    printf("Enter the n you want:");
    scanf("%d", &n);
    while (n - k + 1 < 0)
    {
        printf("Invalid input, please enter again\n");
        scanf("%d", &n);
    }
    n = n - 2;
    printf("Enter the max number you want:");
    scanf("%d", &max);
    struct SqQueue *SqQueue = (struct SqQueue *)malloc(sizeof(struct SqQueue));
    SqQueue_init(SqQueue, k);
    SqQueue_EnQueue(SqQueue, f_0);
    SqQueue_EnQueue(SqQueue, f_1);
    int temp1 = f_0;
    int temp2 = f_1;
    int answer;
    while (SqQueue->count < k)
    {
        answer = solve(temp1, temp2);
        if (answer > max)
        {
            printf("The input of max is invalid\n");
            return 0;
        }
        SqQueue_EnQueue(SqQueue, answer);
        temp1 = temp2;
        temp2 = answer;
        --n;
    }
    printf("\n");
    int rest;
    while (n--)
    {
        SqQueue_DeQueue(SqQueue, &rest);
        answer = solve(temp1, temp2);
        if (answer > max)
        {
            printf("The input of max is invalid\n");
            return 0;
        }
        SqQueue_EnQueue(SqQueue, answer);
        temp1 = temp2;
        temp2 = answer;
    }
    for (int i = 0; i < k; i++)
    {
        printf("%2d ", SqQueue->base[i]);
    }
    printf("\nOver!\n");
    return 0;
}

int solve(int x, int y)
{
    return x + y;
}