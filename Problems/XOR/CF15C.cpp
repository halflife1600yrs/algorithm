#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll prefix(ll x)
{
    switch(x&3ll)
    {
        case 0: return x;
        case 1: return 1;
        case 2: return x+1;
        default: return 0;
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    ll x,m,ans=0;
    while(T--)
    {
        scanf("%lld %lld",&x,&m);
        ans^=prefix(m+x-1)^prefix(x-1);
    }
    puts(ans?"tolik":"bolik");
    return 0;
}