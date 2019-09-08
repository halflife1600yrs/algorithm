#pragma GCC optimize ("O2")
#pragma G++ optimize ("O2")

#include <bits/stdc++.h>

using namespace std;

const int MAXN=4e7+5;
int rk[MAXN];
int pre[MAXN],nxt[MAXN];

int main()
{
    freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int T,n,m,q,k;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d",&n,&m,&q);
        for(int i=2;i<n;++i)
        {
            pre[i]=i-1;
            nxt[i]=i+1;
        }
        pre[1]=n,nxt[1]=2;
        pre[n]=n-1,nxt[n]=1;
        int cur=1;
        for(int i=1;i<n;++i)
        {
            rk[cur]=i;
            nxt[pre[cur]]=nxt[cur];
            pre[nxt[cur]]=pre[cur];
            for(int j=m;j>=0;--j) cur=nxt[cur];
        }
        rk[cur]=n;
        for(int i=0;i<q;++i)
        {
            scanf("%d",&k);
            printf("%d\n",rk[k]);
        }
    }
    cout<<clock()<<endl;
    return 0;
}

/*==================================================================
added at 2019-09-08 14:37:37 E
!!!!调大范围
==================================================================*/