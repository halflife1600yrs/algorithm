#include <queue>
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int MAXV=10050,MAXE=50050;
int v,e;
int fa[MAXV],sz[MAXV];
bool out[MAXV];

struct Quee
{
    int data[MAXV],t;
    void add(int x) { data[t++]=x; }
    int top() { return data[t]; }
} S;

struct Graph
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } edges[MAXE];
    int top, head[MAXV];

    void init() { top = 0, memset(head, -1, sizeof(head)); }

    void add(int fr, int to)
    {
        edges[top].set(to, head[fr]);
        head[fr] = top++;
    }

    bool ins[MAXV];
    bool vis[MAXV];
    int dfn[MAXV],low[MAXV];
    int dfs_num;

    int tarjan()
    {
        dfs_num=S.t=0;
        memset(dfn,-1,sizeof(dfn));
        memset(low,0,sizeof(low));
        memset(ins,0,sizeof(ins));
        for(int i=1;i<=v;++i)
            if(dfn[i]==-1) dfs(i);
        memset(vis,0,sizeof(vis));
        int num=0,ans=0;
        for(int i=1;i<=v;++i)
            if(fa[i]==i)
                if(bfs(i))
                {
                    if(num) return 0;
                    ++num,ans+=sz[i];
                }
        return ans;
    }

    void dfs(int fr)
    {
        dfn[fr]=low[fr]=++dfs_num;
        S.add(fr);
        ins[fr]=1;
        int to;
        for(int i=head[fr];~i;i=edges[i].last)
        {
            to=edges[i].to;
            if(dfn[to]==-1)
            {
                dfs(to);
                low[fr]=min(low[to],low[fr]);
            } else if(ins[to])
                low[fr]=min(low[to],dfn[fr]);
        }
        if(dfn[fr]==low[fr])
        {
            sz[fr]=0;
            while(S.top()!=fr)
            {
                --S.t;
                ins[S.top()]=0;
                ++sz[fr];
                fa[S.top()]=fr;
            }
        }
    }

    bool bfs(int start)
    {
        queue<int> q;
        q.push(start);
        int fr,to;
        while(!q.empty())
        {
            fr=q.front(),q.pop();
            vis[fr]=1;
            for(int i=head[fr];~i;i=edges[i].last)
            {
                to=edges[i].to;
                if(fa[to]!=start) return 0;
                if(vis[to]) continue;
                q.push(to);
            }
        }
        return 1;
    }
} G;

int main()
{
    while(~scanf("%d %d",&v,&e))
    {
        G.init();
        for(int i=0,fr,to;i<e;++i)
        {
            scanf("%d %d",&fr,&to);
            G.add(fr,to);
        }
        printf("%d\n",G.tarjan());
    }
    return 0;
}

/*=======================================
added at 2019.May08 20:29:31	problem:P2341
7 10
1 2
1 2
2 3
3 1
1 5
3 4
4 5
5 6
6 4
6 7

4 4
1 2
1 2
2 3
3 1
=======================================*/