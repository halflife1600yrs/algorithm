#include <bits/stdc++.h>

using namespace std;

const int MAXV=3005,MAXE=2e4+5;
const double INF=1e20;

int v,e;

namespace G
{
    struct Edge
    {
        int fr,to;
        double l;
        void set(int _fr, int _to, double _l) { fr=_fr,to = _to, l = _l; }
    } es[MAXE];

    int top;

    void add(int fr, int to, double l)
    {
        es[top++].set(fr,to, l);
    }

    double path[2][MAXV],pathn[MAXV],maxi[MAXV];

    double karp(int root)
    { // 注意加了超级源点之后的一些地方
        int fr,to;
        double l;
        path[1][root]=path[0][root]=INF; // 从1开始时因为我们连了超级源点
        bool pos=0;
        for(int i=2;i<=v+1;++i) // 实际上有v+1个点
        {
            fill(path[pos]+1,path[pos]+v+1,INF);
            for(int j=0;j<top;++j)
            {
                fr=es[j].fr,to=es[j].to;
                l=path[!pos][fr]+es[j].l;
                if(l<path[pos][to]) path[pos][to]=l;
            }
            pos=!pos;
        }
        for(int i=1;i<=v;++i)
            pathn[i]=path[!pos][i],path[1][i]=0.0,maxi[i]=pathn[i]/v;
        path[1][root]=path[0][root]=INF;
        pos=0;
        for(int i=2;i<=v;++i)
        {
            fill(path[pos]+1,path[pos]+v+1,INF);
            for(int j=0;j<top;++j)
            {
                fr=es[j].fr,to=es[j].to;
                l=path[!pos][fr]+es[j].l;
                if(l<path[pos][to])
                { // 这里的v+1是总点数
                    path[pos][to]=l;
                    if((pathn[to]-l)/(v+1-i)>maxi[to]) maxi[to]=(pathn[to]-l)/(v+1-i);
                }
            }
            pos=!pos;
        }
        l=INF;
        for(int i=1;i<=v;++i)
            if(pathn[i]<INF&&maxi[i]<l) l=maxi[i];
        return l;
    }
}

int main()
{
    scanf("%d %d",&v,&e);
    int fr,to;
    double l;
    for(int i=0;i<e;++i)
    {
        scanf("%d %d %lf",&fr,&to,&l);
        G::add(fr,to,l);
    }
    for(int i=1;i<=v;++i)
        G::add(0,i,0.0);
    printf("%.8lf",G::karp(0));
    return 0;
}

/*==================================================================
added at 2019-08-10 22:16:45	P3199
karp算法
最小比率环
==================================================================*/