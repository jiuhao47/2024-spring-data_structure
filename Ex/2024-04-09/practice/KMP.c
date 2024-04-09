#include <stdio.h>
#include <stdlib.h>
#define INITSIZE 20
void KMP_match(char *s, char *t);
void KMP_getnext(char *s, int *next);
void KMP_match(char *s, char *t)
{
    int i = 0, j = 0;
    int *next = (int *)malloc(sizeof(int) * (strlen(s) + 1));
    KMP_getnext(s, next);
    while (t[i] != '\0')
    {
        if (j == -1 || t[i] == s[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
        if (s[j] == '\0')
        {
            printf("Matched at %d\n", i - j);
            j = next[j];
        }
    }
    free(next);
}

void KMP_getnext(char *s, int *next)
{
    int i = 0, j = -1;
    next[0] = -1;
    while (s[i] != '\0')
    {
        if (j == -1 || s[i] == s[j])
        {
            i++;
            j++;
            if (s[i] != s[j])
            {
                next[i] = j;
            }
            else
            {
                next[i] = next[j];
            }
        }
        else
        {
            j = next[j];
        }
    }
}

int main()
{
    char *s = (char *)malloc(sizeof(char) * INITSIZE);
    char *t = (char *)malloc(sizeof(char) * INITSIZE);
    printf("Please input the string s and t:\n");
    scanf("%s", s);
    scanf("%s", t);
    KMP_match(s, t);
    return 0;
}