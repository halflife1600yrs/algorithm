#include <bits/stdc++.h>

using namespace std;

const int MAXV=1e5+5,MAXE=2*MAXV;
int V;

int Head[MAXV],Tail[MAXV],sz[MAXV];
namespace G
{
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } edges[MAXE]; // 边记得开两倍!!!
    int top, head[MAXV];
    void init() { top = 0, fill(head + 1, head + V + 1, -1); }
    void add(int fr, int to)
    {
        edges[top].set(to, head[fr]);
        head[fr] = top++;
    }
    void print()
    {
        if(!sz[1])
        {
            printf("%d\n",sz[1]);
            return;
        }
        printf("%d ",sz[1]);
        int fr=Head[1],fa=-1;
        while(fr!=Tail[1])
        {
            printf("%d ",fr);
            for(int i=head[fr];~i;i=edges[i].last)
                if(edges[i].to!=fa)
                {
                    fa=fr,fr=edges[i].to;
                    break;
                }
        }
        printf("%d\n",Tail[1]);
    }
}

int main()
{
    int n,q;
    while(~scanf("%d %d",&n,&q))
    {
        for(int i=1;i<=n;++i)
        {
            Head[i]=Tail[i]=i;
            sz[i]=1;
        }
        G::init();
        for(int i=0,a,b;i<q;++i)
        {
            scanf("%d %d",&a,&b);
            if(sz[b]==0)
            {
                swap(Head[a],Tail[a]);
                continue;
            }
            if(sz[a]==0)
            {
                Head[a]=Tail[b],Tail[a]=Head[b];
                sz[a]=sz[b],sz[b]=0;
            } else
            {
                G::add(Tail[a],Head[b]),G::add(Head[b],Tail[a]);
                Tail[a]=Head[a],Head[a]=Tail[b];
                sz[a]+=sz[b],sz[b]=0;
            }
        }
        G::print();
    }
    return 0;
}

/*==================================================================
added at 2019-09-18 19:11:43 19省赛K
双向链表?模拟题
==================================================================*/