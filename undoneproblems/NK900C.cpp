#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
double log2X[11];
const int MODE=1000000007;

inline void modeMul(ll& a,ll b)
{
    a*=b;
    if(a>=MODE) a%=MODE;
}

ll quick_pow(ll base,int up)
{
    ll ans=1;
    while(up)
    {
        if(up&1) modeMul(ans,base);
        modeMul(base,base);
        up>>=1;
    }
    return ans;
}

int main()
{
    log2X[1]=0,log2X[2]=1;
    for(int i=3;i<=10;++i) log2X[i]=log2(i);
    int n,L;
    int ans1=0;
    scanf("%d %d",&n,&L);
    if(L==1&&n>=0) ++ans1;
    if(L==2&&n>=1) ++ans1;
    if(L==4&&n>=2) ++ans1;
    if(L==8&&n>=3) ++ans1;
    int k=1;
    double g=log2X[10];
    while(1)
    {
        double pos1=log2X[L]+g;
        double pos2=log2X[L+1]+g;
        if(floor(pos2)>n) break;
        if(floor(pos2)==ceil(pos1)) ++ans1;
        ++k;
        g+=log2X[10];
    }
    ll tmp=quick_pow(4,ans1);
    ll ans2=(tmp-1+MODE)%MODE;
    printf("%d\n%lld\n",ans1,ans2);
    return 0;
}