#include <stdio.h>

unsigned int f(unsigned int n);

int main()
{
    unsigned int n;
    printf("Input n:");
    scanf("%d", &n);
    printf("The Answer is %d", f(n));
    return 0;
}

unsigned int f(unsigned int n)
{
    if (n == 0)
    {
        return n + 1;
    }
    else
    {
        return n * f(n / 2);
    }
}
