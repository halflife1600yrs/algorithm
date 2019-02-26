#include <bits/stdc++.h>

using namespace std;

const int MAXV=2e5+5,MAXE=3e5+5;
typedef pair<int,int> pII;
int v,e;
struct Graph
{
    int top,vised;
    int vis[MAXV];
    pII edges[MAXE];
    void init()
    {
        top=vised=0;
        memset(vis,0,sizeof(vis));
    }
    void add(int fr,int to)
    {
        edges[top++]=pII(fr,to);
        if(!vis[fr]) ++vised;
        if(!vis[to]) ++vised;
        ++vis[fr],++vis[to];
    }
    bool check()
    {
        if(vised<v) return 1;
        for(int i=0;i<top;++i)
            if(vis[edges[i].first]>1&&vis[edges[i].second]>1) return 1;
        return 0;
    }
} G;

int main()
{
    scanf("%d %d",&v,&e);
    int a,b;
    G.init();
    for(int i=0;i<e;++i)
    {
        scanf("%d %d",&a,&b);
        G.add(a,b);
    }
    if(G.check()) printf("No\n");
    else printf("Yes\n");
    return 0;
}