#include <bits/stdc++.h>

using namespace std;

const int MAXN=20;
int n,a,b;
int uset[MAXN*MAXN];
bool vis[MAXN][MAXN];

int get_fa(int x)
{
    if(uset[x]==x) return uset[x];
    return uset[x]=get_fa(uset[x]);
}

void dfs(int x,int y,int fa)
{
    const int xx[8]={a,a,-a,-a,b,b,-b,-b},yy[8]={b,-b,b,-b,a,-a,a,-a};
    vis[x][y]=1;
    for(int i=0;i<8;++i)
    {
        int nx=x+xx[i],ny=y+yy[i];
        if(0<=nx&&nx<n&&0<=ny&&ny<n&&!vis[nx][ny])
        {
            int f=get_fa(nx*MAXN+ny);
            uset[f]=fa;
            dfs(nx,ny,fa);
        }
    }
}

int main()
{
    while(~scanf("%d %d %d",&n,&a,&b))
    {
        if(a==0&&b==0)
        {
            printf("%lld\n",1ll*n*n);
            continue;
        }
        n=min(20,n);
        memset(vis,0,sizeof(vis));
        for(int i=0;i<MAXN*MAXN;++i) uset[i]=i;
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                if(!vis[i][j])
                    dfs(i,j,get_fa(i*MAXN+j));
        int ans=0;
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                if(get_fa(i*MAXN+j)==i*MAXN+j)
                    ++ans;
        printf("%d\n",ans);
    }
    return 0;
}

/*==================================================================
added at 2019-08-09 10:01:48	个人赛第三场F
还是dfs好,分情况讨论真的碰不得
==================================================================*/