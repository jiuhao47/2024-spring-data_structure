#include <stdio.h>
#include <stdlib.h>
struct polyitem
{
    int c;
    int e;
};
struct polynode
{
    struct polynode *next;
    struct polyitem *item;
};

typedef struct polynode polynode;
typedef struct polyitem polyitem;

// polynode *last;

void build_poly(polynode *head);
polyitem *buid_item(int num);
void solve(polynode *head, double x0);
double mypow(double x0, int pow);

int main()
{
    double x0;
    polynode *head = (polynode *)malloc(sizeof(polynode));
    build_poly(head);
    printf("Input x0:");
    scanf("%lf", &x0);
    solve(head, x0);
    return 0;
}

void build_poly(polynode *head)
{
    head->next = NULL;
    // last = head;
    int num;
    printf("Enter Polynomial term number:");
    scanf("%d", &num);
    while (num < 1)
    {
        printf("INVALID INPUT, input again!");
        scanf("%d", &num);
    }
    for (int i = 1; i < num + 1; i++)
    {
        polynode *q = (polynode *)malloc(sizeof(polynode));
        q->item = buid_item(i);
        q->next = head->next;
        head->next = q;
    }
    printf("\nBuild Success!\n");
}

polyitem *buid_item(int num)
{
    polyitem *p = (polyitem *)malloc(sizeof(polyitem));
    printf("Enter c of the %d item:", num);
    scanf("%d", &(p->c));
    printf("Enter e of the %d item:", num);
    scanf("%d", &(p->e));
    return p;
}

void solve(polynode *head, double x0)
{
    polynode *m = head->next;
    double sum = 0;
    while (m)
    {
        sum = sum + (m->item->c) * (mypow(x0, m->item->e));
        m = m->next;
    }
    printf("The answer is %lf\n", sum);
}

double mypow(double x0, int pow)
{
    double answer = 1;
    for (int i = 0; i < pow; i++)
    {
        answer = answer * x0;
    }
    return answer;
}