#include <bits/stdc++.h>

using namespace std;

const int MAXV=105,MAXE=605;
int V,E;
int pack,val[MAXV],cost[MAXV];

namespace S
{
int data[MAXV], t;
inline void push(int x) { data[t++] = x; }
inline int top() { return data[t - 1]; }
}

namespace G
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } edges[MAXE]; // 边记得开两倍!!!

    int top, head[MAXV];

    void init() { top = 0, fill(head, head + V + 1, -1); }

    void add(int fr, int to)
    {
        edges[top].set(to, head[fr]);
        head[fr] = top++;
    }

    int dfn[MAXV], low[MAXV], fa[MAXV], dfs_num;
    bool ins[MAXV];

    void tarjan(int fr)
    {
        dfn[fr] = low[fr] = ++dfs_num;
        ins[fr] = 1, S::push(fr);
        for(int i = head[fr], to; ~i; i = edges[i].last)
        {
            to = edges[i].to;
            if(!dfn[to])
            {
                tarjan(to);
                low[fr] = min(low[fr], low[to]);
            } else if(ins[to])
                low[fr] = min(low[fr], dfn[to]);
        }
        if(dfn[fr] == low[fr])
        {
            int t;
            while(S::top() != fr)
            {
                t=S::top();
                low[t] = dfn[fr];
                fa[t]=fr;
                val[fr]+=val[t],cost[fr]+=val[t];
                val[t]=cost[t]=-1;
                ins[t] = 0;
                --S::t;
            }
            ins[fr] = 0;
            --S::t;
        }
    }

    int times[MAXV], head2[MAXV], in[MAXV];

    void shrink()
    { // 直接在原图上缩点成DAG并去重边,需要两个辅助数组times和head2,in用来保存DAG的入度
        // fill(dfn + 1, dfn + 1 + V, 0);
        // fill(ins + 1, ins + 1 + V, 0);
        dfs_num = S::t = 0;
        for(int i = 1; i <= V; ++i)
            if(!dfn[i]) tarjan(i);
        fill(head2 + 1, head2 + 1 + V, -1);
        // fill(in + 1, in + 1 + V, 0);
        for(int fr = 1, i, j; fr <= V; ++fr) // 缩点
            for(i = head[fr]; ~i && (j = edges[i].last, 1); i = j)
                if(fa[edges[i].to] != fa[fr])
                {
                    edges[i].set(fa[edges[i].to], head2[fa[fr]]);
                    head2[fa[fr]] = i;
                }
        // fill(times + 1, times + 1 + V, 0);
        for(int fr = 1, to, i, j; fr <= V; ++fr) // 去重
            for(i = head2[fr], head[fr] = -1; ~i && (j = edges[i].last, 1); i = j)
                if(times[to = edges[i].to] != fr)
                {
                    times[to] = fr;
                    edges[i].set(to, head[fr]);
                    head[fr] = i;
                    ++in[to];
                }
        for(int i=1;i<=V;++i)
            if(!in[i]&&cost[i]>=0) add(0,i);
    }

    void dfs()
    {

    }
}

int main()
{
    scanf("%d %d",&V,&pack);
    for(int i=1;i<=V;++i) scanf("%d",&cost[i]);
    for(int i=1;i<=V;++i) scanf("%d",&val[i]);
    G::init();
    for(int i=1,fa;i<=V;++i)
    {
        scanf("%d",&fa);
        if(fa) G::add(fa,i);
    }
    return 0;
}
/*=======================================
added at 2019.Jun04 21:26:12	problem:NK19981
5 10
1 2 3 4 5
1 2 3 4 5
2 3 4 1 4
=======================================*/