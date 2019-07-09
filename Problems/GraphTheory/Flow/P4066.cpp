#include <bits/stdc++.h>
#define debug1(x) std::cout<<#x"="<<x<<std::endl
#define debug2(x,y) std::cout<<#x"="<<x<<","#y"="<<y<<std::endl
using namespace std;

const int MAXV=2005*5,MAXE=MAXV*200,INF=0x7f7f7f7f,inf=0x80808080;

namespace q
{
    int data[MAXV*10],s,t;
    inline void push(int x)
    {
        data[t++]=x;
        if(t==MAXV*10) t=0;
    }
    inline int pop()
    {
        if(s==MAXV*10-1)
        {
            s=0;
            return data[MAXV*10-1];
        } 
        return data[s++];
    }
}
int ans,cost;
int st,en;
namespace G
{
    int head[MAXV];
    int top;
    struct Edge
    {
        int to, last, l, c;
        void set(int _to, int _last, int _l, int _c) { to = _to, last = _last, l = _l, c = _c; }
    } edges[MAXE << 1];
    void init() { top = 0, memset(head, -1, sizeof(head)); }
    void add(int fr, int to, int l, int c)
    {
        // debug2(fr,to);
        edges[top].set(to, head[fr], l, c);
        head[fr] = top++;
        edges[top].set(fr, head[to], -l, 0);
        head[to] = top++;
    }
    int dis[MAXV],pree[MAXV],prev[MAXV],minf[MAXV];
    bool vis[MAXV];
    bool spfa()
    {
        q::s=q::t=0;
        memset(dis,0x80,sizeof(dis));
        memset(minf,0x7f,sizeof(minf));
        memset(vis,0,sizeof(vis));
        memset(pree,-1,sizeof(pree));
        q::push(st);
        vis[st]=1,dis[st]=0;
        int fr,to;
        while(q::s!=q::t)
        {
            fr=q::pop();
            vis[fr]=0;
            // debug1(fr);
            for(int i=head[fr];~i;i=edges[i].last)
            {
                to=edges[i].to;
                if(edges[i].c&&dis[to]<dis[fr]+edges[i].l)
                {
                    dis[to]=dis[fr]+edges[i].l;
                    minf[to]=min(minf[fr],edges[i].c);
                    pree[to]=i;
                    prev[to]=fr;
                    // debug2(to,fr);
                    if(!vis[to]) q::push(to),vis[to]=1;
                }
            }
        }
        return pree[en]!=-1; // 这里不能用!=inf判断,不然费用0死循环了
    }
    void dfs()
    {
        int cur=en,i;
        int tmp=minf[en];
        while(cur!=st)
        {
            // debug1(cur);
            i=pree[cur];
            edges[i].c-=tmp;
            edges[i^1].c+=tmp;
            cur=prev[cur];
        }
        cost+=dis[en]*tmp;
    }
    void mcf()
    {
        ans=cost=0;
        while(spfa()) dfs();
    }
}

struct Point
{
    int id,x,y;
    bool operator<(const Point& a) const
    {
        return x==a.x?y<a.y:x<a.x; // 对的
        // return x<a.x; // 错的
    }
} point[MAXV];

int main()
{
    int n;
    scanf("%d",&n);
    G::init();
    st=0,en=2*n+3; // 开始点入点0,出点2n+1,结束点入点2n+2,出点2n+3
    G::add(0,2*n+1,0,2);
    G::add(2*n+2,2*n+3,0,2);
    for(int i=1;i<=n;++i)
    { // 普通点入点1-n,出点n+1-2n
        scanf("%d %d",&point[i].x,&point[i].y);
        point[i].id=i;
        G::add(2*n+1,i,0,2); // 连开始点出点
        G::add(i,i+n,1,1); // 入点连出点,吃了的
        G::add(i,i+n,0,1); // 没吃的
        G::add(i+n,2*n+2,0,2); // 连结束点入点
    }
    sort(point+1,point+n+1);
    for(int i=1,mini;i<=n;++i)
    {
        mini=INF;
        for(int j=i+1;j<=n;++j)
        {
            if(point[j].y<point[i].y) continue;
            if(point[j].y<mini)
            {
                G::add(point[i].id+n,point[j].id,0,2);
                mini=point[j].y;
            }
        }
    }
    G::mcf();
    printf("%d\n",cost);
    return 0;
}

/*==================================================================
added at 2019-07-08 20:38:54 P4066
排序方式出现了错误,没有考虑到x相等的情况
其实是网络流比较基本?的题目
这题主要的难度在于边的传递性,莽建边会T+MLE
不同节点间的可建边关系(a.x>=b.x&&a.y>=b.y)是偏序集
那么根据可建边的传递性只要建出在其哈斯图上的边就行了
方法是按x排序后检测y,O(n2)
==================================================================*/