#include <bits/stdc++.h>

using namespace std;

const int MAXV=10005,MAXE=100005;
int v,e;

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
    int low[MAXV],dfn[MAXV],dfs_num;

    int tarjan()
    {
        dfs_num=S.t=0;
        memset(ins,0,sizeof(ins));
        memset(dfn,-1,sizeof(dfn));
        int ans=0;
        for(int i=1;i<=v;++i)
            if(dfn[i]==-1) ans+=dfs(i);
        return ans;
    }

    int dfs(int fr)
    {
        low[fr]=dfn[fr]=++dfs_num;
        S.add(fr);
        ins[fr]=1;
        int to,ans=0;
        for(int i=head[fr];~i;i=edges[i].last)
        {
            to=edges[i].to;
            if(dfn[to]==-1)
            {
                ans+=dfs(to);
                low[fr]=min(low[to],low[fr]);
            } else if(ins[to])
                low[fr]=min(low[to],dfn[fr]);
        }
        if(dfn[fr]==low[fr])
        {
            ++ans;
            while(S.top()!=fr)
            {
                --S.t;
                ins[S.top()]=0;
            }
        }
        return ans;
    }
} G;

int main()
{
    while(scanf("%d %d",&v,&e),v|e)
    {
        G.init();
        for(int i=0,fr,to;i<e;++i)
        {
            scanf("%d %d",&fr,&to);
            G.add(fr,to);
        }
        if(G.tarjan()<=1) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}

/*=======================================
added at 2019.May08 16:17:22	problem:HDU1269
6 8
1 3
1 2
3 4
2 4
4 1
3 5
4 6
5 6

=======================================*/