#include <bits/stdc++.h>

using namespace std;

const int MAXV=5005,MAXE=MAXV;

struct Edge
{
    int to, last;
    void set(int _to, int _last) { to = _to, last = _last; }
} edges[MAXE<<1];
int top, head[MAXV];
void init() { top = 0, memset(head, -1, sizeof(head)); }
void add(int fr, int to)
{
    edges[top].set(to, head[fr]);
    head[fr] = top++;
}

const int L=MAXV*5;
int d[L],st,en;
void push(int x) { d[st==L-1 ? st=0,L-1 : st++]=x; }
int pop() { return d[en==L-1 ? en=0,L-1 : en++]; }

int dis[MAXV],vis[MAXV];

int main()
{
    int v,e,q;
    scanf("%d %d %d",&v,&e,&q);
    init();
    for(int i=0,fr,to;i<e;++i)
    {
        scanf("%d %d",&fr,&to);
        add(fr,to),add(to,fr);
    }
    int s,t;
    for(int i=1;i<=q;++i)
    {
        scanf("%d %d",&t,&s);
        for(int j=st=en=0,p;j<t;++j)
        {
            scanf("%d",&p);
            push(p);
            dis[p]=0,vis[p]=i;
        }
        int fr,to;
        while(st!=en)
        {
            fr=pop();
            for(int k=head[fr];~k;k=edges[k].last)
            {
                to=edges[k].to;
                if(vis[to]==i) continue;
                push(to),vis[to]=i;
                dis[to]=dis[fr]+1;
            }
        }
        int ans=0;
        for(int j=1;j<=v;++j)
            if(dis[j]<=s&&vis[j]==i) ++ans;
        printf("%d\n",ans);
    }
    return 0;
}

/*==================================================================
added at 2019-07-14 17:24:46 NK14521
又忘了bfs的最短性质了
==================================================================*/