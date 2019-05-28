#include <bits/stdc++.h>

using namespace std;

const int MAXV=1005,MAXE=MAXV*MAXV;
const double INF=1e100;
int monkey[505],x[MAXV],y[MAXV];
int v;
double graph[MAXV][MAXV],dis[MAXV];
bool vis[MAXV];

int prim()
{
    for(int i=0;i<v;++i) dis[i]=INF;
    vis[0]=1,dis[0]=0.0;
    double maxi=0;
    int cur=0;
    while(1)
    {
        double mini=INF;
        int next=-1;
        for(int i=0;i<v;++i)
        {
            if(vis[i]) continue;
            if(graph[cur][i]<dis[i]) dis[i]=graph[cur][i];
            if(dis[i]<mini) mini=dis[i],next=i;
        }
        if(next==-1) break;
        maxi=max(maxi,mini);
        cur=next;
        vis[cur]=1;
    }
    return maxi;
}

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i) scanf("%d",&monkey[i]);
    scanf("%d",&v);
    for(int i=0;i<v;++i)
    {
        scanf("%d %d",&x[i],&y[i]);
        for(int j=0;j<i;++j) graph[i][j]=graph[j][i]=hypot(x[i]-x[j],y[i]-y[j]);
    }
    int limit=prim();
    int ans=n;
    for(int i=0;i<n;++i)
        if(monkey[i]<limit) --ans;
    printf("%d\n",ans);
    return 0;
}