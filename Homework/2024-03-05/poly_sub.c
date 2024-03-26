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

void build_poly(polynode *head);
polyitem *buid_item(int num);
void build_sub_poly(polynode *head);
void print_poly(polynode *head);

int main()
{
    double x0;
    polynode *head = (polynode *)malloc(sizeof(polynode));
    printf("P_{n_1}(x):\n");
    build_poly(head);
    printf("P_{n_2}(x):\n");
    build_sub_poly(head);
    print_poly(head);
    return 0;
}

void print_poly(polynode *head)
{
    polynode *n = head->next;
    while (n)
    {
        printf("(%d)x^(%d)+", n->item->c, n->item->e);
        n = n->next;
    }
}

void build_sub_poly(polynode *head)
{
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
        polynode *m = head->next;
        while (m)
        {
            if (m->item->e == q->item->e)
            {
                m->item->c = m->item->c - q->item->c;
                free(q);
                q = NULL;
                break;
            }
            else
            {
                m = m->next;
            }
        }
        if (q)
        {
            q->item->c = (-1) * q->item->c;
            q->next = head->next;
            head->next = q;
        }
    }
    printf("\nSub Success!\n");
}

void build_poly(polynode *head)
{
    head->next = NULL;
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