#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int sz = 1e7;
int prime[20] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71 };

ll gcd(ll a, ll b)
{
    if(b == 0) return a;
    return gcd(b, a % b);
}

int main()
{
    ll a, b;
    for(int time, _ = scanf("%d", &time); time--;)
    {
        scanf("%lld %lld", &a, &b);
        if(gcd(a, b) == 1)
        {
            printf("1\n%lld %lld\n", a, b);
            continue;
        }
        for(int i = 0; i < 20; ++i)
        {
            if(a % prime[i] && b % prime[i])
            {
                printf("2\n%lld %lld\n%lld %lld\n", prime[i], b - prime[i], a - prime[i], prime[i]);
                break;
            }
        }
    }
    return 0;
}