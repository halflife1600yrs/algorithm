#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    ll x,y;
    int a,b;
    while(~scanf("%lld %d %lld %d",&x,&a,&y,&b))
    {
        __int128_t p1=x,p2=y;
        p1*=b,p2*=a;
        if(p1==p2) printf("=\n");
        else if(p1<p2) printf("<\n");
        else printf(">\n");
    }
    return 0;
}