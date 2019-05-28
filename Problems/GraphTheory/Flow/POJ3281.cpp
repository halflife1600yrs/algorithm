#include <queue>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXV=600,MAXE=305*205,INF=0x7f7f7f7f;
int n,f,d;

struct Graph
{
    int head[MAXV];
    int start, end, top;
    int depth[MAXV];
    struct Edge
    {
        int to, last, l;
        void set(int _to, int _last, int _l) { to = _to, l = _l, last = _last; }
    } edges[MAXE<<1];
    void init() { top = 0, memset(head, -1, sizeof(head)); }
    void add(int fr, int to, int l)
    {
        edges[top].set(to, head[fr], l);
        head[fr] = top++;
    }
    bool bfs()
    {
        queue<int> Q;
        memset(depth, -1, sizeof(depth));
        Q.push(start);
        depth[start] = 0;
        int fr, to;
        while(!Q.empty())
        {
            fr = Q.front(), Q.pop();
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if(depth[to] == -1 && edges[i].l > 0)
                {
                    depth[to] = depth[fr] + 1;
                    Q.push(to);
                }
            }
        }
        return depth[end] > 0;
    }
    int dfs(int fr, int addflow = INF)
    {
        if(fr == end) return addflow;
        int tf = 0, to, cap;
        for(int i = head[fr]; ~i; i = edges[i].last)
        {
            to = edges[i].to, cap = edges[i].l;
            if(depth[to] == depth[fr] + 1 && cap > 0)
            {
                int add = dfs(to, min(addflow - tf, cap));
                edges[i].l -= add, edges[i ^ 1].l += add, tf += add;
            }
        }
        if(tf == 0) depth[fr] = -1;
        return tf;
    }
    int Dinic()
    {
        int ans = 0;
        while(bfs()) ans += dfs(start);
        return ans;
    }
} G;

inline int cow1(int x) { return x; }
inline int cow2(int x) { return n+x; }
inline int food(int x) { return 2*n+x; }
inline int drink(int x) { return 2*n+f+x; }

int main()
{ // cow,food,drink 1-index
    scanf("%d %d %d",&n,&f,&d);
    G.init();
    G.start=0,G.end=1+2*n+f+d;
    for(int i=1,fn,dn;i<=n;++i)
    {
        scanf("%d %d",&fn,&dn);
        for(int j=0,a;j<fn;++j)
        {
            scanf("%d",&a);
            G.add(food(a),cow1(i),1);
            G.add(cow1(i),food(a),0);
        }
        for(int j=0,a;j<dn;++j)
        {
            scanf("%d",&a);
            G.add(cow2(i),drink(a),1);
            G.add(drink(a),cow2(i),0);
        }
    }
    for(int i=1;i<=n;++i) G.add(cow1(i),cow2(i),1),G.add(cow2(i),cow1(i),0);
    for(int i=1;i<=f;++i) G.add(G.start,food(i),1),G.add(food(i),G.start,0);
    for(int i=1;i<=d;++i) G.add(drink(i),G.end,1),G.add(G.end,drink(i),0);
    printf("%d\n",G.Dinic());
    return 0;
}