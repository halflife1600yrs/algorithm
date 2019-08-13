#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXV=2005,MAXE=6e4+5;
const ll INF=0x7f7f7f7f7f7f7f7f;
int v;
ll dis[MAXV];

namespace q
{
    const int top=MAXV*2;
    int data[top],s,t;
    void push(int x) { data[t==top-1?t=0,top-1:t++]=x; }
    int pop() { return data[s==top-1?s=0,top-1:s++]; }
}

namespace G
{
    struct Edge
    {
        int to,last,l;
        void set(int _to,int _last,int _l) { to=_to,last=_last,l=_l; }
    } es[MAXE];

    int head[MAXV],top;

    void init() { top=0,memset(head,-1,sizeof(head)); }

    void add(int fr,int to,int l)
    {
        es[top].set(to,head[fr],l);
        head[fr]=top++;
    }

    int cnt[MAXV];
    bool inq[MAXV];

    bool spfa(int root)
    {
        q::s=q::t=0;
        memset(cnt,0,sizeof(cnt));
        memset(inq,0,sizeof(inq));
        memset(dis,0x7f,sizeof(dis));
        dis[root]=0,cnt[root]=1;
        q::push(root);
        int fr,to;
        while(q::s!=q::t)
        {
            fr=q::pop();
            inq[fr]=0;
            for(int i=head[fr];~i;i=es[i].last)
            {
                to=es[i].to;
                ll d=dis[fr]+es[i].l;
                if(d<dis[to])
                {
                    dis[to]=d;
                    if(inq[to]) continue;
                    inq[to]=1,++cnt[to];
                    if(cnt[to]>v) return 1;
                    q::push(to);
                }
            }
        }
        return 0;
    }
}

int main()
{
    for(int T,_=scanf("%d",&T);T--;++_)
    {
        int q,X;
        scanf("%d %d %d",&v,&q,&X);
        int a,b,c,d;
        G::init();
        for (int i = 0; i < q; ++i)
        {
            scanf("%d %d %d %d",&a,&b,&c,&d);
            if(a==b&&c==d)
            {
                G::add(a,c,X);
                G::add(c,a,-X);
            } else if(a==b&&c!=d)
            {
                if(a!=c) G::add(a,c,X-1);
                G::add(d,a,-X-1);
            } else if(a!=b&&c!=d)
            {
                G::add(d,a,-X-1);
                if(a!=c&&b!=c) G::add(b,c,X-1);
            } else if(a!=b&&c==d)
            {
                G::add(d,a,-X-1);
                if(b!=c) G::add(b,c,X-1);
            }
        }
        for(int i=v;i>1;--i) G::add(i,i-1,-1);
        printf("Case #%d: ",_);
        if(G::spfa(v))
        {
            printf("IMPOSSIBLE\n");
        } else
        {
            for(int i=2;i<v;++i) printf("%lld ",dis[i]-dis[i-1]);
            printf("%lld\n",dis[v]-dis[v-1]);
        }
    }
    return 0;
}

/*
100
4 3 4
1 1 2 3
2 3 2 3
2 3 3 4

4 2 2
1 2 3 4
2 3 2 3

5 2 3
1 2 2 3
2 3 2 3

4 4 4
1 1 3 4
2 2 3 4
3 3 4 4
4 4 4 5

5 2 3
1 1 3 3
1 2 4 5

2 3 3
1 1 1 2
1 2 1 2
1 2 2 2
*/

/*==================================================================
added at 2019-08-13 16:04:04 17CCPCfinalJ题
第一次在比赛写差分约束系统然后就过了
感谢队友的样例,把建边过程中的错误都找出来了
不连通的情况:
利用后面的一定比前面的大的限制,从后往前连边然后从第n号点跑一个全负值的最短路
==================================================================*/