#include <stdio.h>
#include <stdbool.h>

#define AVALIABLE 0
#define TABSIZE 11
typedef int Hashelement;

typedef struct Hashtab
{
    Hashelement tab[TABSIZE];
    int size;
} Hashtab;

int hash(Hashelement k);
bool insert(Hashtab *hashtab, Hashelement k);

int hash(Hashelement k)
{
    return (3 * k) % 11;
}

bool insert(Hashtab *hashtab, Hashelement k)
{
    if (hashtab->size < TABSIZE)
    {
        int index = hash(k);
        int i = 1;
        while (hashtab->tab[index] != 0)
        {
            index = (index + i * ((7 * k) % 10 + 1)) % TABSIZE;
            i++;
        }
        hashtab->tab[index] = k;
        hashtab->size++;
        return true;
        // insert success
    }
    else
    {
        return false;
        // Hashtab full
    }
}

int main()
{
    Hashtab Hashtab;
    for (int i = 0; i < TABSIZE; i++)
    {
        Hashtab.tab[i] = 0;
    }
    Hashtab.size = 0;
    int c = 0;
    int num = 0;
    while ((c = getchar()) != '\n')
    {
        if (c != ' ')
        {
            num = (c - '0') + num * 10;
        }
        else
        {
            insert(&Hashtab, num);
            num = 0;
        }
    }
    for (int i = 0; i < TABSIZE; i++)
    {
        printf("%d:%d ", i, Hashtab.tab[i]);
    }
    return 0;
}