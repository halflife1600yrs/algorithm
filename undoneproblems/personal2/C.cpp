#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;

pll operator+(const pll& a,const pll& b)
{
    return pll(a.first+b.first,a.second+b.second);
}

pll turn90(pll x)
{
    return pll(x.second,-x.first);
}

int main()
{
    pll a,b,c;
    scanf("%lld %lld",&a.first,&b.second);
    scanf("%lld %lld",&b.first,&b.second);
    scanf("%lld %lld",&c.first,&c.second);
    pll p[4];
    p[0]=turn90(a)+c;
    p[1]=turn90(p[0])+c;
    p[2]=turn90(p[1])+c;
    p[3]=a;
    for(int i=0;i<4;++i)
    {
        if(b==p[i])
        {
            puts("YES");
            return 0;
        }
    }
    puts("NO");
    return 0;
}