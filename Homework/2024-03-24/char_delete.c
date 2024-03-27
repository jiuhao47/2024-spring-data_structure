#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char datatype;

typedef struct HString
{
    datatype *ch;
    int length;
    int strsize;
} HString;
void StrDelete(HString *s, char *t);
void Strinit(HString *s);
void StrAssign(HString *s, datatype *sc);

void Strinit(HString *s)
{
    s->ch = (datatype *)malloc(sizeof(datatype));
    s->ch[0] = '\0';
    s->length = 0;
    s->strsize = 1;
    return;
}

void StrAssign(HString *s, datatype *sc)
{
    int i = 0;
    while (sc[i] != '\0')
        i++;
    if (i >= s->strsize)
    {
        s->ch = (datatype *)realloc(s->ch, (i + 1) * sizeof(datatype));
        s->strsize = i + 1;
    }
    s->length = i;
    for (i = 0; i < s->length; i++)
        s->ch[i] = sc[i];
    s->ch[i] = '\0';
    return;
}
void StrDelete(HString *s, char *t)
{
    int i = 0, j = 0;
    int t_length = strlen(t);
    datatype *result = (datatype *)malloc((s->strsize + 1) * sizeof(datatype));

    while (i < s->length)
    {
        if (strncmp(&s->ch[i], t, t_length) == 0)
        {
            i += t_length;
        }
        else
        {
            result[j++] = s->ch[i++];
        }
    }

    result[j] = '\0';

    free(s->ch);
    s->ch = result;
    s->length = j;
    s->strsize = j + 1;
}
int main()
{
    datatype s[] = "abcdabcdabcd\n";
    datatype t[] = "abc";
    HString *S = (HString *)malloc(sizeof(HString));

    Strinit(S);
    StrAssign(S, s);
    printf("%s", S->ch);
    StrDelete(S, t);
    printf("%s", S->ch);
    return 0;
}