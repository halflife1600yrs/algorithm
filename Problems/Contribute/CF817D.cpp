#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN=1e6+5;
int val[MAXN];
int left_ge[MAXN],right_gt[MAXN],left_le[MAXN],right_lt[MAXN];

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&val[i]);
    int pos;
    val[0]=0x7f7f7f7f,left_ge[1]=0;
    for(int i=1;i<=n;++i)
    {
        pos=i-1;
        while(val[pos]<val[i]) pos=left_ge[pos];
        left_ge[i]=pos;
    }
    val[0]=0,left_le[1]=0;
    for(int i=1;i<=n;++i)
    {
        pos=i-1;
        while(val[pos]>val[i]) pos=left_le[pos];
        left_le[i]=pos;
    }
    val[n+1]=0x7f7f7f7f,right_gt[n]=n+1;
    for(int i=n-1;i>0;--i)
    {
        pos=i+1;
        while(val[pos]<=val[i]) pos=right_gt[pos];
        right_gt[i]=pos;
    }
    val[n+1]=0,right_lt[n]=n+1;
    for(int i=n-1;i>0;--i)
    {
        pos=i+1;
        while(val[pos]>=val[i]) pos=right_lt[pos];
        right_lt[i]=pos;
    }
    ll ans=0;
    for(int i=1;i<=n;++i)
    {
        ans+=val[i]*(ll)(right_gt[i]-i)*(i-left_ge[i]);
        ans-=val[i]*(ll)(right_lt[i]-i)*(i-left_le[i]);
    }
    printf("%lld\n",ans);
    return 0;
}

/*==================================================================
added at 2019-08-06 19:43:30	个人赛第二场A
似乎正解是用单调栈的,什么时候补一下
==================================================================*/