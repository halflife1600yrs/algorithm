#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MODE=1e9+7,MAXN=2e5+5;
ll inv[MAXN],multi[MAXN],invs[MAXN];

void get_inv()
{  
    inv[0]=inv[1]=1;  
    for(int i=2;i<MAXN;i++)
        inv[i]=((MODE-MODE/i)*inv[MODE%i])%MODE;  
}   

void pre()
{
    get_inv();
    for(int i=multi[0]=invs[0]=1;i<MAXN;++i)
    {
        invs[i]=inv[i]*invs[i-1]%MODE;
        multi[i]=multi[i-1]*i%MODE;
    }
}

inline ll Katlan(int x)
{
    return multi[x<<1]*invs[x]%MODE*invs[x]%MODE*inv[x+1]%MODE;
}

inline ll C(int x,int y) // y里面取x
{
    if(x<=0) return 1;
    return multi[y]*invs[x]%MODE*invs[y-x]%MODE;
}

int main()
{
    pre();
    int T,x,y;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&x,&y);
        printf("%lld\n",Katlan(x)*C(y-x-1,y));
    }
    return 0;
}