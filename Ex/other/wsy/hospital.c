#include <stdio.h>

#define MAX_PatientQueue 1000

typedef struct
{
    char name[20];
} Patient;

typedef struct
{
    Patient PatientQueue[MAX_PatientQueue];
    int front;
    int rear;
    int size;
} SqQueue;

// 初始化队列
void InitSqQueue(SqQueue *q)
{
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

// 检查队列是否满
int isFull(SqQueue *q)
{
    if (q->size == MAX_PatientQueue)
        return 1;
    else 
        return 0;
}


// 检查队列是否为空
int isEmpty(SqQueue *q)
{
    if (q->size == 0)
        return 1;
    else 
        return 0;
}

// 入队
void EnSqQueue(SqQueue *q, Patient patient)
{
    if (isFull(q)==1)
    {
        printf("队列已满，无法再接待更多病人。\n");
        return;
    }
    q->PatientQueue[q->rear] = patient;
    q->rear = (q->rear + 1) % MAX_PatientQueue;
    q->size++;
}

// 出队
void DeSqQueue(SqQueue *q)
{
    if (isEmpty(q)==1)
    {
        printf("队列为空，没有需要就诊的病人。\n");
        return;
    }
    Patient patient = q->PatientQueue[q->front];
    q->front = (q->front + 1) % MAX_PatientQueue;
    q->size--;
    printf("病人 %s，请前往就诊。\n", patient.name);
}

// 显示队列中的病人
void DisplaySqQueue(SqQueue *q)
{
    if (isEmpty(q)==1)
    {
        printf("目前队列中没有病人。\n");
        return;
    }
    printf("目前队列中的病人:\n");
    int num = q->size;
    int i = q->front;
    while (num>0)
    {
        printf("姓名: %s \n", q->PatientQueue[i].name);
        i = (i + 1) % MAX_PatientQueue;
        num--;
    }
}

int main()
{
    SqQueue SqQueue;
    InitSqQueue(&SqQueue);
    int choice;
    while (1)
    {   
        printf("=========菜单=========");
        printf("\n        1. 排队\n        2. 就诊\n        3. 查看排队\n        4. 退出\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            if (isFull(&SqQueue))
            {
                printf("队列已满，无法再接待更多病人！\n");
                break;
            }
            Patient patient;
            printf("请输入病人姓名: ");
            scanf("%s", patient.name);
            EnSqQueue(&SqQueue, patient);
            break;
        }
        case 2:
            DeSqQueue(&SqQueue);
            break;
        case 3:
            DisplaySqQueue(&SqQueue);
            break;
        case 4:
            printf("程序退出。\n");
            return 0;
        default:
            printf("请选择正确序号\n");
        }
    }

    return 0;
}