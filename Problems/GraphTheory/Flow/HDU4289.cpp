#include <bits/stdc++.h>

using namespace std;

const int MAXV=1000,MAXE=2e6+5,INF=0x7f7f7f7f;

int v,e;
int ans,st,en;
namespace G
{
    int head[MAXV];
    int top;
    struct Edge
    {
        int to, last, l;
        void set(int _to, int _last, int _l) { to = _to, last = _last, l = _l; }
    } edges[MAXE << 1];
    void init() { top = 0, memset(head, -1, sizeof(head)); }
    void add(int fr, int to, int l)
    {
        edges[top].set(to, head[fr], l);
        head[fr] = top++;
        edges[top].set(fr, head[to], 0);
        head[to] = top++;
    }

    int depth[MAXV];
    bool bfs()
    {
        queue<int> q;
        memset(depth, -1, sizeof(depth));
        q.push(st);
        depth[st] = 0;
        int fr, to;
        while(!q.empty())
        {
            fr = q.front(), q.pop();
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if(depth[to] == -1 && edges[i].l > 0)
                    depth[to] = depth[fr] + 1, q.push(to);
            }
        }
        return depth[en] > 0;
    }

    int dfs(int fr, int addflow = INF)
    {
        if(fr == en) return addflow;
        int tf = 0, to, d = depth[fr] + 1;
        for(int i = head[fr], add; ~i; i = edges[i].last)
        { // 一次dfs多次增广,tf记录当前已经增广流量
            to = edges[i].to;
            if(depth[to] == d && edges[i].l > 0)
            {
                add = dfs(to, min(addflow - tf, edges[i].l));
                edges[i].l -= add, edges[i ^ 1].l += add, tf += add;
            }
        }
        if(!tf) depth[fr] = -1; // 因为是多次dfs增广,不能增广的点标记深度为-1
        return tf;
    }

    int dinic()
    {
        int ans = 0;
        while(bfs()) ans += dfs(st);
        return ans;
    }
}

int main()
{
    while(~scanf("%d%d",&v,&e))
    {
        scanf("%d %d",&st,&en);
        en+=v;
        G::init();
        for(int i=1,val;i<=v;++i)
        {
            scanf("%d",&val);
            G::add(i,i+v,val);
        }
        for(int i=0,fr,to;i<e;++i)
        {
            scanf("%d %d",&fr,&to);
            G::add(fr+v,to,INF); // 出点到入点
            G::add(to+v,fr,INF);
        }
        printf("%d\n",G::dinic());
    }
    return 0;
}

/*==================================================================
added at 2019-07-12 18:35:46 HDU4289
这里被模板坑了,dfs应该是判断edges[i].l>0而不是等于0
==================================================================*/