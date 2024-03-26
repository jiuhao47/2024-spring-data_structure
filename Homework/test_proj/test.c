#include <stdio.h>
int school[101][101] = {0};
int main()
{
    freopen("test.txt", "r", stdin);
    int i;
    char a, b, c, d;
    char a1, b1, c1;
    int p;
    int end = 1;
    while (end == 1)
    {
        a = getchar();
        while (a != ' ' && a != EOF)
        {
            a = getchar();
        }
        scanf("%c%c%c%c%d", &b, &b1, &c, &c1, &p);
        school[c][b] += p;
        char d;
        if ((d = getchar()) == EOF)
            end = 0;
    }
    char End = 'E';
    for (i = 'A'; i <= 'E'; i++)
    {
        int ADD = ADD = school[i]['M'] + school[i]['F'];
        if (ADD != 0)
        {
            End = 'E';
        }
        if (ADD == 0 && End == 'E')
        {
            End = i - 1;
        }
    }
    for (i = 'A'; i <= End; i++)
    {
        if (school[i]['M'] != 0)
        {
            printf("%c M %d\n", i, school[i]['M']);
        }
        if (school[i]['F'] != 0)
        {
            printf("%c F %d\n", i, school[i]['F']);
        }
        int ADD = school[i]['M'] + school[i]['F'];
        if (ADD != 0)
        {
            printf("%c %d", i, ADD);
            if (i != End)
                printf("\n");
        }
    }
    return 0;
}