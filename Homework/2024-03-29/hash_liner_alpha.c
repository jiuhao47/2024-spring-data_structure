#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define AVALIABLE 1
#define TABSIZE 26
#define STRSIZE 10

typedef char Hashelement;

typedef struct Hashtab
{
    Hashelement *tab[TABSIZE];
    int size;
} Hashtab;
int hash(Hashelement *k);
bool insert(Hashtab *hashtab, Hashelement *k);
Hashelement *getinput();
void hashsortprint(Hashtab *hashtab);
int hash(Hashelement *k)
{
    return (k[0] - 'a') % TABSIZE;
}

bool insert(Hashtab *hashtab, Hashelement *k)
{
    if (hashtab->size < TABSIZE)
    {
        int index = hash(k);
        while (hashtab->tab[index] != 0)
        {
            index = (index + 1) % TABSIZE;
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

Hashelement *getinput()
{
    int size = STRSIZE;
    Hashelement c;
    Hashelement *str = (Hashelement *)malloc(sizeof(Hashelement) * STRSIZE);
    int i = 0;
    while ((c = getchar()) != '\n')
    {
        if (i == size)
        {
            size *= 2;
            str = (Hashelement *)realloc(str, sizeof(Hashelement) * size);
        }
        str[i] = c;
        i = i + 1;
    }
    str[i] = '\0';
    return str;
}

void hashsortprint(Hashtab *hashtab)
{
    int i = 0;
    while (i < TABSIZE)
    {
        int p = 0;
        while (p < TABSIZE)
        {
            int j = (i + p) % TABSIZE;
            Hashelement *c = hashtab->tab[j];
            if (c == NULL)
            {
                break;
            }
            if (c != AVALIABLE)
            {
                if (c[0] == 'a' + i)
                {
                    printf("%d:%s\n", j, c);
                    hashtab->tab[j] = AVALIABLE;
                }
            }
            p = p + 1;
        }
        i = i + 1;
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
    Hashelement *str;
    while ((str = getinput())[0] != '\0')
    {
        insert(&Hashtab, str);
    }
    hashsortprint(&Hashtab);
    /*
    for (int i = 0; i < TABSIZE; i++)
    {
        if (Hashtab.tab[i] != 0)
        {
            printf("%d:%s\n", i, Hashtab.tab[i]);
        }
    }
    */
    return 0;
}
