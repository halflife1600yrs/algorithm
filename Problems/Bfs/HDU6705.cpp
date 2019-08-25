#pragma GCC optimize ("O2")
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,int> pli;
const int MAXV=5e4+5,MAXE=5e4+5;
int V,E,Q;
ll ans[MAXV];
pii query[MAXV];

namespace G
{
    struct Edge
    {
        int to, last, l;
        void set(int _to, int _last, int _l) { to = _to, last = _last, l = _l; }
    } es[MAXE]; // 边记得开两倍!!!

    int top, head[MAXV];

    void init() { top = 0, fill(head + 1, head + V + 1, -1); }
    inline void add(int fr, int to, int l)
    {
        es[top].set(to, head[fr], l);
        head[fr] = top++;
    }
    void sort_edge()
    {
        priority_queue<pii,vector<pii>,greater<pii>> q;
        for(int i=1;i<=V;++i)
        {
            for(int j=head[i];~j;j=es[j].last) q.push(pii(es[j].l,es[j].to));
            for(int j=head[i];~j;j=es[j].last) tie(es[j].l,es[j].to)=q.top(),q.pop();
        }
    }
    void work()
    {
        priority_queue<pli,vector<pli>,greater<pli>> q;
        for(int i=1;i<=V;++i)
            if(~head[i]) q.push(pli(es[head[i]].l,head[i]));
        int pos1=0,pos2=0,cur,last;
        ll dis;
        while(pos2<Q)
        {
            tie(dis,cur)=q.top(),q.pop();
            ++pos1;
            while(pos2<Q && pos1==query[pos2].first)
                ans[query[pos2].second]=dis,++pos2;
            last=es[cur].last;
            if(~last) q.push(pli(dis-es[cur].l+es[last].l,last)); // 加入出点相同的下一条边
            last=head[es[cur].to];
            if(~last) q.push(pli(dis+es[last].l,last)); // 加入从入点出去的第一条边
        }
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
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int T;
    read(T);
    while(T--)
    {
        read(V),read(E),read(Q);
        G::init();
        int fr,to,l;
        for(int i=0;i<E;++i)
        {
            read(fr),read(to),read(l);
            G::add(fr,to,l);
        }
        G::sort_edge();
        for(int i=0;i<Q;++i)
        {
            read(query[i].first);
            query[i].second=i;
        }
        sort(query,query+Q);
        G::work();
        for(int i=0;i<Q;++i) printf("%lld\n",ans[i]);
    }
    return 0;
}

/*==================================================================
added at 2019-08-23 19:06:18 2019CCPC网络赛1004
类似于牛客多校882的D题是一个优先队列优化的bfs
但是每次都把每个点邻接的边全部加进去就会T
所以应该是把每个点的出边都排个序,然后优先队列弹出一条边后把它的头邻接和尾邻接的下一条边加入答案
要是比赛的时候能想出来就好了
==================================================================*/