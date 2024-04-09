#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITSIZE 20
int KMP_match(char *s, char *t, int pos);
void KMP_getnext(char *s, int *next);

int main()
{
    char *s = (char *)malloc(sizeof(char) * INITSIZE);
    char *t = (char *)malloc(sizeof(char) * INITSIZE);
    printf("Please input the pattern string s:\n");
    scanf("%s", s);
    printf("Please input the main string t:\n");
    scanf("%s", t);
    printf("Matched at %d\n", KMP_match(s, t, 0));
    return 0;
}

int KMP_match(char *s, char *t, int pos)
{
    // s为模式串，t为主串，pos为开始匹配的位置
    int i = pos, j = 0;
    int *next = (int *)malloc(sizeof(int) * (strlen(s) + 1));
    KMP_getnext(s, next);
    while (i < strlen(t) && (j + 1) <= (strlen(s)))
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
    }
    if (s[j] == '\0')
    {
        return i - strlen(s);
    }
    else
    {
        return -1;
    }
}

void KMP_getnext(char *s, int *next)
{
    // s为模式串，next为next数组
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
