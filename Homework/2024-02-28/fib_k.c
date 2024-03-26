#include <stdio.h>
long long int solve(int k, int m);
int main()
{
    int k, m;
    printf("Enter parameter k&m in format k m\n");
    scanf("%d %d", &k, &m);
    printf("The %d number is %lld\n", m, solve(k, m));
    return 0;
}

long long int solve(int k, int m)
{
    long long int f[k];
    for (int i = 0; i < k - 1; i++)
    {
        f[i] = 0;
    }
    f[k - 1] = 1;
    int j = k;
    int index = 0;
    long long int sum = 0;
    while (j <= m)
    {
        sum = 0;
        index = j % k;
        for (int n = 0; n < k; n++)
        {
            sum = sum + f[n];
        }
        f[index] = sum;
        j = j + 1;
    }
    return f[index];
}
