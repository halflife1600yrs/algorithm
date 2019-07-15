#include <bits/stdc++.h>

using namespace std;

const int MAXV=1005,MAXE=1e4+5;
int val[MAXV];
int v,e;

namespace q
{
    const int top=5*MAXV;
    int data[top],s,t;
    void push(int x) { data[ t==top-1 ? (t=0,top-1) : t++ ]=x; }
    int pop() { return s==top-1 ? (s=0,data[top-1]) : data[s++]; }
}

namespace G
{
    struct Edge
    {
        int to, last, l;
        void set(int _to, int _last, int _l) { to = _to, last = _last, l = _l; }
    } edges[MAXE];

    int top, head[MAXV];

    void init() { top = 0, memset(head, -1, sizeof(head)); }

    void add(int fr, int to, int l)
    {
        edges[top].set(to, head[fr], l);
        head[fr] = top++;
    }

    bool inq[MAXV];
    int vis[MAXV];
    double dis[MAXV];

    bool spfa(int root,double r)
    {
        q::s=q::t=0;
        q::push(root);
        vis[root]=1,dis[root]=0.0;
        int fr,to;
        while(q::s!=q::t)
        {
            fr=q::pop();
            inq[fr]=0;
            for(int i=head[fr];~i;i=edges[i].last)
            {
                to=edges[i].to;
                if(dis[to]>dis[fr]-val[to]+r*edges[i].l)
                {
                    if(++vis[to]>=v) return 1;
                    dis[to]=dis[fr]-val[to]+r*edges[i].l;
                    if(!inq[to]) q::push(to),inq[to]=1;
                }
            }
        }
        return 0;
    }

    bool check(double r)
    {
        for(int i=1;i<=v;++i) vis[i]=0,inq[i]=0,dis[i]=1e100;
        for(int i=1;i<=v;++i)
            if(!vis[i])
                if(spfa(i,r)) return 1;
        return 0;
    }

}


int main()
{
    scanf("%d %d",&v,&e);
    G::init();
    double l=0,r=0,mid;
    for(int i=1;i<=v;++i) scanf("%d",&val[i]),r+=val[i];
    for(int i=0,fr,to,l;i<e;++i)
    {
        scanf("%d %d %d",&fr,&to,&l);
        G::add(fr,to,l);
    }
    while(r-l>0.0001)
    {
        mid=(l+r)/2.0;
        if(G::check(mid)) l=mid;
        else r=mid;
    }
    printf("%.2f\n",(l+r)/2.0);
    return 0;
}

/*==================================================================
added at 2019-07-13 19:35:33 P2868
最大比率环
发现对spfa的理解还不够,要补一下
==================================================================*/