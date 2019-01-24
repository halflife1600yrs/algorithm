#include <bits/stdc++.h>

int main()
{
    int cas;
    int n, m, A, B;
    scanf("%d", &cas);
    while(cas--)
    {
        long long ans = 0;
        scanf("%d %d %d %d", &n, &m, &A, &B);
        if(A * m < B)
            ans = A * n;
        else if(n % m * A > B)
            ans = (n / m + 1) * B;
        else
            ans = n / m * B + n % m * A;
        printf("%lld\n", ans);
    }
    return 0;
}