#include <bits/stdc++.h>

using namespace std;

const int sz = 1e5 + 5, cap = 1e6 + 5;
int arry[sz], sieve[cap];

int main()
{
    int n, k;
    while(~scanf("%d %d", &n, &k))
    {
        for(int i = 0; i < n; i++) scanf("%d", &arry[sz]);
        sort(arry, arry + n);
        memset(sieve, sizeof(sieve), 0);
        for(int i = 0; i < n; i++) sieve[arry[i]] = 1;
        for(int i = 1; i <= k; i++)
        {
            for(int j = 0; j < n; j++)
            {
                sieve[i * arry[j]] += sieve[i] + sieve[arry[j]];
                if(i % arry[j] == 0) break;
            }
        }
        int ans, time;
        for(int i = 1; i <=k; i++)
        {

        }
    }
}