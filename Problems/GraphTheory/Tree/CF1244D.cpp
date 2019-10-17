#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <tuple>

using namespace std;

typedef long long ll;
const ll INF=0x7f7f7f7f7f7f7f7f;
const int MAXV=1e5+5,MAXE=2*MAXV;
int V,c[3][MAXV];
const int way[6][3]={
    {0,1,2},
    {0,2,1},
    {1,2,0},
    {1,0,2},
    {2,1,0},
    {2,0,1},
};

int getc(int x,int y)
{
    bool vis[3]={0,0,0};
    vis[x]=vis[y]=1;
    for(int i=0;i<3;++i)
        if(!vis[i]) return i;
}

namespace T
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } es[MAXE]; // 边记得开两倍!!!
    int top, head[MAXV], d[MAXV];
    void init() { top = 0, fill(head + 1, head + V + 1, -1); }
    bool add(int fr, int to)
    {
        ++d[fr],++d[to];
        if(d[fr]>2||d[to]>2) return 1;
        es[top].set(to, head[fr]);
        head[fr] = top++;
        es[top].set(fr, head[to]);
        head[to] = top++;
        return 0;
    }
    int color[MAXV];
    void dfs(int fr,int fa)
    {
        for(int i=head[fr],to;~i;i=es[i].last)
        {
            to=es[i].to;
            if(to==fa) continue;
            color[to]=getc(color[fr],color[fa]);
            dfs(to,fr);
        }
    }
    void work()
    {
        int key=es[head[1]].to;
        color[key]=0,color[1]=1;
        dfs(1,key),dfs(key,1);
        ll ans[3][3];
        memset(ans,0,sizeof(ans));
        for(int i=1;i<=V;++i)
            for(int j=0;j<3;++j)
                ans[color[i]][j]+=c[j][i];
        ll mini=INF;
        int pos;
        for(int i=0;i<6;++i)
        {
            ll tmp=0;
            for(int j=0;j<3;++j)
                tmp+=ans[j][way[i][j]];
            if(tmp<mini) mini=tmp,pos=i;
        }
        printf("%lld\n",mini);
        for(int i=1;i<=V;++i)
            printf("%d ",way[pos][color[i]]+1);
        puts("");
    }
}

int main()
{
    scanf("%d",&V);
    for(int j=0;j<3;++j)
        for(int i=1;i<=V;++i) scanf("%d",&c[j][i]);
    T::init();
    for(int i=1,fr,to;i<V;++i)
    {
        scanf("%d %d",&fr,&to);
        if(T::add(fr,to))
        {
            puts("-1");
            return 0;
        }
    }
    T::work();
    return 0;
}

/*==================================================================
added at 2019-10-15 12:22:15 CF1244D
挺简单一个树形dp,一个地方longlong没写
==================================================================*/