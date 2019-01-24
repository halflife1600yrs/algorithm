#include <bits/stdc++.h>

int main()
{
    long long n;
    while(~scanf("%lld", &n))
    {
        if(n == 1)
            printf("2\n");
        else
            printf("%lld\n", 2 * n - 1);
    }
    return 0;
}