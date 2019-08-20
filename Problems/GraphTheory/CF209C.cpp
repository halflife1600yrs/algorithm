#include <bits/stdc++.h>
 
using namespace std;
 
const int MAXV=1e6+5,MAXE=MAXV,MODE=1e9+7;
int d[MAXV],num[MAXV],uset[MAXV];
 
int getFa(int x) 
{
    if(uset[x]==x) return x;
    return uset[x]=getFa(uset[x]);
}
 
int main()
{
    int v,e,fr,to,x,y;
    while(~scanf("%d %d",&v,&e))
    {
        memset(d,0,sizeof(d));
        memset(num,0,sizeof(num));
        for(int i=1;i<=v;++i) uset[i]=i;
        for(int i=0;i<e;++i)
        {
            scanf("%d %d",&fr,&to);
            // if(fr==to) continue;
            ++d[fr],++d[to];
            x=getFa(fr),y=getFa(to);
            uset[x]=y;
        }
        int ans=0,block=0;
        bool flag=0;
        for(int i=1;i<=v;++i)
            if(d[i]&1) ++num[getFa(i)];
        for(int i=1;i<=v;++i)
        {
            if(uset[i]==i&&(i==1||d[i])) ++block;
            // printf("i=%d,num=%d,d=%d,uset=%d\n",i,num[i],d[i],uset[i]);
            if(num[i]>2) ans+=(num[i]-2)>>1;
            if(num[i]>=2) flag=1;
        }
        // printf("b=%d\n",block);
        if(block==1)
            if(flag) ++ans;
        else
            ans+=block;
        printf("%d\n",ans);
    }
    return 0;
}

/*==================================================================
added at 2019-08-15 20:05:50 CF209C
在图上加边形成欧拉回路
需要特殊考虑的情况:
1. 不同连通块
2. 起始点无边
3. 自环
==================================================================*/