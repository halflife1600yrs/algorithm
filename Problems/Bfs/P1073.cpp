#include <bits/stdc++.h>

using namespace std;

const int MAXV=1e5+5,MAXE=1e6+5;
int val[MAXV],mini[MAXV],maxi[MAXV];
int v,e;

namespace q
{
    const int top=MAXV*1.5;
    int data[top],s,t;
    void push(int x) { data[t==top-1?t=0,top-1:t++]=x; }
    int pop() { return data[s==top-1?s=0,top-1:s++]; }
}

namespace G
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } es[MAXE]; // 边记得开两倍!!!

    int top, head[MAXV];

    void init() { top = 0, memset(head, -1, sizeof(head)); }

    void add(int fr, int to)
    {
        es[top].set(to, head[fr]);
        head[fr] = top++;
    }

    int head2[MAXV];
    void rev()
    {
        fill(head2 + 1, head2 + v + 1, -1);
        for(int fr=1,to;fr<=v;++fr)
        {
            for(int i=head[fr],j;~i&&(j=es[i].last,1);i=j)
            {
                to=es[i].to;
                es[i].set(fr,head2[to]);
                head2[to]=i;
            }
        }
        for(int i=1;i<=v;++i) head[i]=head2[i];
    }

    bool inq[MAXV];

    void spfa1(int st)
    {
        memset(mini,0x7f,sizeof(mini));
        memset(inq,0,sizeof(inq));
        q::s=q::t=0;
        q::push(st);
        mini[st]=val[st];
        int fr,to;
        while(q::s!=q::t)
        {
            fr=q::pop();
            inq[fr]=0;
            for(int i=head[fr];~i;i=es[i].last)
            {
                to=es[i].to;
                if(min(val[to],mini[fr])<mini[to])
                {
                    mini[to]=min(val[to],mini[fr]);
                    if(!inq[to]) q::push(to),inq[to]=1;
                }
            }
        }
    }

    void spfa2(int st)
    {
        memset(maxi,0,sizeof(maxi));
        memset(inq,0,sizeof(inq));
        q::s=q::t=0;
        q::push(st);
        maxi[st]=val[st];
        int fr,to;
        while(q::s!=q::t)
        {
            fr=q::pop();
            inq[fr]=0;
            for(int i=head[fr];~i;i=es[i].last)
            {
                to=es[i].to;
                if(max(val[to],maxi[fr])>maxi[to])
                {
                    maxi[to]=max(val[to],maxi[fr]);
                    if(!inq[to]) q::push(to),inq[to]=1;
                }
            }
        }
    }
}

int main()
{
    scanf("%d %d",&v,&e);
    for(int i=1;i<=v;++i) scanf("%d",&val[i]);
    G::init();
    for(int i=0,fr,to,op;i<e;++i)
    {
        scanf("%d %d %d",&fr,&to,&op);
        G::add(fr,to);
        if(op==2) G::add(to,fr);
    }
    G::spfa1(1);
    G::rev();
    G::spfa2(v);
    int ans=0;
    for(int i=1;i<=v;++i)
    {
        ans=max(ans,maxi[i]-mini[i]);
    }
    printf("%d\n",ans);
    return 0;
}

/*==================================================================
added at 2019-08-10 09:06:26	P1073
最优贸易,有三个状态:没买到物品,买到物品,卖出物品
两次bfs,第一次从开始点出发记录每个点及之前能买到的最小物品价格,消除前效性
然后在反图上从结束点出发记录每个点之后能卖出的最大物品价格,消除后效性
然后每个点两个值相减就好了
还可以用tarjan缩点之后dag上dp
==================================================================*/