#include <queue>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXV=2005,INF=0x7f7f7f7f;
int v;
char car[MAXV][8];
int graph[MAXV][MAXV],dis[MAXV];
bool vis[MAXV];

void init() { memset(graph,0x7f,sizeof(graph)); }

void add(int fr,int to,int l) { graph[fr][to]=graph[to][fr]=l; }

int Prim()
{
    memset(dis,0x7f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dis[1]=0,vis[1]=1;
    int ans=0,lenz=0,cur=1;
    for(int i=1;i<v;++i)
    {
        int mini=INF,next=-1;
        for(int j=1;j<=v;++j)
        {
            if(vis[j]) continue;
            if(graph[cur][j]<dis[j]) dis[j]=graph[cur][j];
            if(dis[j]<mini) mini=dis[j],next=j;
        }
        if(next==-1) break;
        vis[next]=1,ans+=mini,++lenz,cur=next;
    }
    if(lenz==v-1) return ans;
    return -1;
}

int dif(int a,int b)
{
    int ans=0;
    for(int i=0;i<7;++i)
        ans+=car[a][i]!=car[b][i];
    return ans;
}

int main()
{
    while(scanf("%d",&v),v)
    {
        init();
        for(int i=1;i<=v;++i)
            scanf("%s",car[i]);
        for(int i=1;i<v;++i)
            for(int j=i+1;j<=v;++j)
                add(i,j,dif(i,j));
        printf("The highest possible quality is 1/%d.\n",Prim());
    }
    return 0;
}

/*=======================================
added at 2019.Apr25 20:20:26	problem:POJ1789
mst
=======================================*/