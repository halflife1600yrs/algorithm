#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXV=2e5+5,MODE=1e9+7;
int v,e,d[MAXV],prefix[MAXV];

int main()
{
    scanf("%d %d",&v,&e);
    int fr,to;
    for(int i=0;i<e;++i)
    {
        scanf("%d %d",&fr,&to);
        ++d[fr],++d[to];
    }
    sort(d+1,d+v+1,greater<int>());
    for(int i=1;i<=v;++i)
        prefix[i]=prefix[i-1]+d[i];
    int sz=0;
    for(int i=1;i<=v;++i)
        if(prefix[i]==i*(ll)(i-1)+prefix[v]-prefix[i])
        {
            sz=i;
            break;
        }
    if(!sz)
    {
        puts("0");
        return 0;
    }
    ll dn=0,dn_1=0,Dn_1=0,Dn=0;
    for(int i=1;i<=sz;++i)
    { // 团内
        if(d[i]==sz) ++Dn;
        if(d[i]==sz-1) ++Dn_1;
    }
    for(int i=sz+1;i<=v;++i)
    { // 团外
        if(d[i]==sz) ++dn;
        if(d[i]==sz-1) ++dn_1;
    }
    ll ans=(Dn_1+dn+Dn*dn+Dn_1*dn_1+1)%MODE;
    printf("%lld\n",ans);
    return 0;
}

/*==================================================================
added at 2019-08-16 17:13:08 校选2B
删去一个点:团里面度数为n-1
加入一个点:团外面度数为n
交换一个点:团外面n和n;n-1和n-1
外面n-1和里面n不能交换因为里面n-1跟它不连接
==================================================================*/