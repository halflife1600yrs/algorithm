#include <queue>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

typedef pair<int,double> pid;
const int MAXV=800,MAXE=1e6;
const double INF=1e100;
int way_num[MAXV],x[MAXV],y[MAXV],v;
bool vis[MAXV];
double dis[MAXV];
struct Graph
{
    int top,head[MAXV];
    struct Edge
    {
        int to,last;
        double l;
        void set(int _to,int _last,double _l) { to=_to,last=_last,l=_l; }
    } edges[MAXE];
    void init() { top=0,memset(head,-1,sizeof(head)); }
    void add(int fr,int to,double l)
    {
        edges[top].set(to,head[fr],l);
        head[fr]=top++;
    }
    void Dij(int start);
} G;
struct cmp
{
    bool operator()(const pid& a,const pid& b) { return a.second>b.second; }
};
void Graph::Dij(int start)
{
    fill(dis,dis+v,INF);
    priority_queue<pid,vector<pid>,cmp> q;
    dis[start]=0.0;
    q.push(pid(start,0.0));
    int fr,to;
    double d;
    while(!q.empty())
    {
        fr=q.top().first,q.pop();
        if(vis[fr]) continue;
        vis[fr]=1;
        for(int i=head[fr];~i;i=edges[i].last)
        {
            to=edges[i].to;
            if(vis[to]) continue;
            d=dis[fr]+edges[i].l;
            if(d<dis[to]) dis[to]=d,q.push(pid(to,d));
        }
    }
}

inline double distance(int x,int y) { return sqrt(1.0*x*x+y*y); }

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int x1,y1,x2,y2;
    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
    way_num[0]=-1,x[0]=x1,y[0]=y1;
    int way=v=1,a,b;
    while(~scanf("%d %d",&a,&b))
    {
        if(a==-1&&b==-1) ++way;
        else
        {
            x[v]=a;
            y[v]=b;
            way_num[v++]=way;
        }
    }
    x[v]=x2,y[v]=y2;
    way_num[v++]=-2;
    G.init();
    double d;
    for(int i=0;i<v-1;++i)
    {
        for(int j=i+1;j<v;++j)
        {
            d=distance(x[i]-x[j],y[i]-y[j]);
            if(way_num[i]!=way_num[j])
            {
                G.add(i,j,d*4.0),G.add(j,i,d*4.0);
                continue;
            }
            if(j==i+1)
            {
                G.add(i,j,d),G.add(j,i,d);
            }
        }
    }
    G.Dij(0);
    printf("%.0f\n",dis[v-1]*3.0/2000.0);
    return 0;
}

/*=======================================
added at 2019.Apr10 20:14:18	problem:POJ2502
http://acm.student.cs.uwaterloo.ca/~acm00/010922/data/
数据在这里b题
=======================================*/