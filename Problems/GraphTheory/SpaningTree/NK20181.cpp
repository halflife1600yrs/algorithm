#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
const int MAXV=1005;
const double INF=1e100;
int v,k;
pii points[MAXV];

double dis[MAXV];
bool vis[MAXV];
double graph[MAXV][MAXV];

void add(int fr, int to, double l)
{
    graph[fr][to] = graph[to][fr] = min(graph[to][fr], l);
}

int prim()
{
    for(int i=1;i<=v;++i) dis[i]=INF;
    memset(vis, 0, sizeof(vis));
    dis[1] = 0, vis[1] = 1;
    double ans = 0;
    int lenz = 0, last = 1;
    for(int i = 0; i < v - 1; ++i)
    {
        double mini = INF;
        int next = -1;
        for(int j = 1; j <= v; ++j)
        {
            if(vis[j]) continue;
            if(graph[last][j] < dis[j]) dis[j] = graph[last][j];
            if(dis[j] < mini) mini = dis[j], next = j;
        }
        if(next == -1) break;
        ans += mini, ++lenz;
        vis[next] = 1;
        last = next;
    }
    if(lenz != v - 1) return -1;
    return ans;
}

bool cmp(double a,double b) { return a>b; }

int main()
{
    scanf("%d %d",&v,&k);
    for(int i=1;i<=v;++i) scanf("%d %d",&points[i].first,&points[i].second);
    for(int i=1;i<v;++i)
        for(int j=i+1;j<=v;++j)
            graph[i][j]=graph[j][i]=hypot(points[i].first-points[j].first,points[i].second-points[j].second);
    prim();
    sort(dis+1,dis+v+1,cmp);
    // disp(dis,1,v+1)
    printf("%.2f",dis[k-1]);
    return 0;
}

/*=======================================
added at 2019.Apr28 16:46:38	problem:NK20181
划分若干个点使得最近的两组距离最大
不过不是放在最小生成树专题应该想不出来
事实上就是在最小生成树上依次去掉最大的边就行了
记得连边的时候要对称
=======================================*/