#include <bits/stdc++.h>

using namespace std;

const int MAXV=2*2005,MAXE=2005*2005*2+2005*2,INF=0x7f7f7f7f;
typedef pair<int,int> pii;

int v, e;
int ans, cost;
pii points[MAXV];

bool cmp(const pii& a,const pii& b)
{
    return a.first==b.first?a.second>b.second:a.first<b.first;
}

namespace q
{
    const int top=MAXV*2;
    int data[top],s,t;
    inline void push(int x) { data[t==top-1? t=0,top-1:t++]=x; }
    inline int pop() { return data[s==top-1? s=0,top-1:s++]; }
}

namespace G
{
    int head[MAXV];
    int top;
    struct Edge
    { // l为长度/费用,c为费用
        int to, last, l, c;
        void set(int _to, int _last, int _l, int _c) { to = _to, last = _last, l = _l, c = _c; }
    } edges[MAXE << 1];

    void init() { top = 0, memset(head, -1, sizeof(head)); }

    void add(int fr, int to, int l, int c)
    {
        edges[top].set(to, head[fr], l, c);
        head[fr] = top++;
        edges[top].set(fr, head[to], -l, 0);
        head[to] = top++;
    }

    int start, end;
    int dis[MAXV], prev[MAXV], pree[MAXV], minf[MAXV];
    bool vis[MAXV];

    bool spfa()
    {                                   // 这里的初始化不能删因为多次调用
        memset(dis, 0x80, sizeof(dis)); // 最大费用的时候下面要改>号,这里要用0x80初始化为负值
        memset(vis, 0, sizeof(vis));
        memset(minf, 0x7f, sizeof(minf));
        q::s=q::t=0;
        q::push(start);
        dis[start] = 0, vis[start] = 1;
        int fr, to;
        while (q::s!=q::t)
        {
            fr = q::pop();
            vis[fr] = 0;
            for (int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if (edges[i].c > 0 && dis[fr] + edges[i].l > dis[to])
                {
                    dis[to] = dis[fr] + edges[i].l;
                    minf[to] = min(minf[fr], edges[i].c);
                    prev[to] = fr;
                    pree[to] = i;
                    if (!vis[to])
                        q::push(to), vis[to] = 1;
                }
            }
        }
        return dis[end] > 0; // 这里也可以用pree[end]!=-1来判断,但是要初始化pree
    }

    void dfs()
    {
        int cur = end, i, tmp = minf[end];
        while (cur != start)
        {
            i = pree[cur];
            edges[i].c -= tmp;
            edges[i ^ 1].c += tmp;
            cur = prev[cur];
        }
        ans += tmp;
        cost += dis[end] * tmp; // 一般来说是dis[en]
    }

    void mcf()
    {
        ans = cost = 0;
        while (spfa())
            dfs();
    }
}

namespace io {
    const int SIZE = 1e7 + 10;
    char inbuff[SIZE];
    char *l, *r;
    inline void init() {
        l = inbuff;
        r = inbuff + fread(inbuff, 1, SIZE, stdin);
    }
    inline char gc() {
        if (l == r) init();
        return (l != r) ? *(l++) : EOF;
    }
    void read(int &x) {
        x = 0; char ch = gc();
        while(!isdigit(ch)) ch = gc();
        while(isdigit(ch)) x = x * 10 + ch - '0', ch = gc();
    }
} using io::read;

int main()
{
    int T,n,k;
    read(T);
    while(T--)
    {
        read(n),read(k);
        G::init();
        G::start=2*n+1,G::end=2*n+4;
        G::add(G::start,2*n+2,0,k); // 最多选k个
        G::add(2*n+3,G::end,0,k); // 最多选k个
        for(int i=1;i<=n;++i)
        {
            read(points[i].second);
            points[i].first=i;
            G::add(2*n+2,i,0,n);
            G::add(i,i+n,points[i].second,1);
            G::add(i,i+n,0,n);
            G::add(i+n,2*n+3,0,n);
        }
        sort(points+1,points+n+1,cmp);
        int mini;
        for(int i=1;i<n;++i)
        {
            mini=0x7f7f7f7f;
            for(int j=i+1;j<=n;++j)
            {
                if(points[j].second<mini)
                {
                    if(points[j].second>=points[i].second)
                    {
                        G::add(i+n,j,0,n);
                        mini=points[j].second;
                    }
                }
            }
        }
        G::mcf();
        printf("%d\n",cost);
    }
    return 0;
}

/*==================================================================
added at 2019-07-29 16:26:47 1009
又是一道偏序集路径剖分
优化拉满
==================================================================*/