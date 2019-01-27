#include <bits/stdc++.h>

using namespace std;

long long cas[1005] = { 0, 1, 1, 2 };
const int mode = 998244353;
long long C[1005][1005];

int main()
{
    for(int i = 1; i < 1005; ++i) C[i][1] = i, C[i][i] = 1, C[i][0] = 1;
    for(int i = 1; i < 1005; ++i)
        for(int j = 1; j < i; ++j)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mode;
    int n;
    for(int i = 4; i <= 1005; ++i)
    {
        for(int j = 1; j <= i; j += 2)
            cas[i] = ((cas[j] * cas[i - 1 - j] % mode) * C[i - 1][j] % mode + cas[i]) % mode;
        if(i % 2 == 0)
            cas[i] = (cas[i] + cas[i - 1]) % mode;
    }
    while(~scanf("%d", &n)) printf("%lld\n", cas[n]);
    return 0;
}