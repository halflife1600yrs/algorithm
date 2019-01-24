#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    int t;
    ll n;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%lld", &n);
        if(n <= 2)
            printf("1\n");
        else
            printf("0\n");
    }
    return 0;
}