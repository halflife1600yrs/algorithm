#include <bits/stdc++.h>

using namespace std;

const int MAXN=5e6+5,MODE=998244353;

typedef long long ll;
int prefix[MAXN],inv[MAXN<<1];

inline int add(int x,int y)
{
    x+=y;
    if(x>=MODE) x-=MODE;
    if(x<0) x+=MODE;
    if(x<0) x+=MODE;
    return x;
}

void init()
{
    inv[0]=inv[1]=1;
    for(int i=2;i<MAXN*2;i++)
        inv[i]=((MODE-MODE/i)*(ll)inv[MODE%i])%MODE;
    prefix[0]=1; // 计算1/(2n+1)的前缀和
    for(int i=1;i<MAXN;++i)
        prefix[i]=add(prefix[i-1],inv[2*i+1]);
}

int main()
{
    init();
    int T,l,r,x,ans;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&l,&r);
        x=floor(1.0*r/l);
        if(!(x&1)) x-=1;
        ans=r*(ll)prefix[x>>1]%MODE;
        ans=add(ans,-l*(ll)((x+1)>>1)%MODE);
        ans=(ans*(ll)inv[r-l]%MODE);
        printf("%lld\n",ans);
    }
    return 0;
}