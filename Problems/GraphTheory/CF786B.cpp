#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXV=524290,MAXE=10*MAXV;
const ll INF=0x7f7f7f7f7f7f7f7f;
int V,E;
ll dis[MAXV];

typedef pair<ll, int> pii;

namespace G
{
    struct Edge
    {
        int to, last, l;
        void set(int _to, int _last, int _l) { to = _to, last = _last, l = _l; }
    } edges[MAXE]; // 边记得开两倍!!!
    int top, head[MAXV];
    void init() { top = 0, fill(head + 1, head + V + 1, -1); }
    // 线段树建图一定不要用memset,只需要fill真实节点就行了
    inline void add(int fr, int to, int l)
    {
        edges[top].set(to, head[fr], l);
        head[fr] = top++;
    }
    bool vis[MAXV];
    void dijkstra(int start)
    {
        fill(dis + 1, dis + V + 1, INF);
        // fill(vis + 1, vis + V + 1, 0);
        priority_queue<pii,vector<pii>,greater<pii>> q;
        dis[start] = 0;
        q.push(pii(0, start));
        int fr, to;
        while(!q.empty())
        {
            fr = q.top().second, q.pop();
            if(vis[fr]) continue; // fr可能多次入队,但第一次出队时就已经更新完成
            vis[fr] = 1;
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if(vis[to]) continue;
                ll d = dis[fr] + edges[i].l;
                if(d < dis[to]) dis[to] = d, q.push(pii(d, to));
            }
        }
    }
}

namespace sgt
{ // inTree从上向下连边,处理点向区间连边，outTree相反
    int point, inTree, outTree; // inTree/outTree记录两棵树根
    int L[MAXV], R[MAXV]; // 记录左右节点位置使点在线段树和图中标号相同
    #define mid ((l + r) >> 1)
    int p, st, en, w; // 记录查询的变量
    bool pattern;
    int build_t(int l, int r)
    {
        if(r == l) return l; // 把真实的节点放在1-v的位置
        int cur = ++V; // 当前节点编号为V
        G::head[cur] = -1; // 初始化一下
        L[cur] = build_t(l, mid), R[cur] = build_t(mid + 1, r);
        if(pattern) G::add(cur, L[cur], 0), G::add(cur, R[cur], 0);
        else G::add(L[cur], cur, 0), G::add(R[cur], cur, 0);
        return cur;
    }
    void build(int v)
    { // 传入图的真实点数即可,从1开始标号
        V = point = v, G::init(); // 记录一下真实的节点有几个
        pattern = 1, inTree = build_t(1, v);
        pattern = 0, outTree = build_t(1, v);
    }
    void work(int l, int r, int pos)
    {
        if(st <= l && r <= en)
        {
            if(pattern) G::add(p, pos, w);
            else G::add(pos, p, w);
            return;
        }
        if(en < l || r < st) return;
        work(l, mid, L[pos]), work(mid + 1, r, R[pos]);
    }
    // 一个点p和一个区间[st,en]连权为w的边
    void add_edge(int p_, int st_, int en_, int w_, bool pat_)
    { // pat:1-点向区间连边,此时用inTree;0-相反
        p = p_, st = st_, en = en_, w = w_, pattern = pat_;
        work(1, point, pattern ? inTree : outTree);
    }
    #undef mid
}
int main()
{
    int v,q,s;
    scanf("%d %d %d",&v,&q,&s);
    int op,fr,l,r,w;
    sgt::build(v);
    for(int i=0;i<q;++i)
    {
        scanf("%d",&op);
        switch(op)
        {
            case 1:
                scanf("%d %d %d",&fr,&l,&w);
                G::add(fr,l,w);
                break;
            case 2:
                scanf("%d %d %d %d",&fr,&l,&r,&w);
                sgt::add_edge(fr,l,r,w,1);
                break;
            case 3:
                scanf("%d %d %d %d",&fr,&l,&r,&w);
                sgt::add_edge(fr,l,r,w,0);
        }
    }
    G::dijkstra(s);
    for(int i=1;i<v;++i)
        printf("%lld ",dis[i]==INF?-1:dis[i]);
    printf("%lld\n",dis[v]==INF?-1:dis[v]);
    return 0;
}

/*==================================================================
added at 2019-08-23 10:16:52 CF786B
线段树优化建图模板题
==================================================================*/