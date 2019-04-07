#include <bits/stdc++.h>

using namespace std;

const int MAXV=10005,MAXE=100005;
int v,e,dp[MAXV];

struct Graph
{
    int top,head[MAXV],in[MAXV];
    struct Edge
    {
        int to,last,l;
        void set(int _to,int _last,int _l) { to=_to,last=_last,l=_l; }
    } edges[MAXE<<1];
    void init()
    {
        top=0;
        memset(head,-1,sizeof(head));
        memset(in,0,sizeof(in));
    }
    void add(int fr,int to,int l)
    {
        edges[top].set(to,head[fr],l);
        ++in[to];
        head[fr]=top++;
    }
    void topsort()
    {
        queue<int> q;
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=v;++i)
            if(!in[i]) q.push(i);
        int fr,to;
        while(!q.empty())
        {
            fr=q.front(),q.pop();
            for(int addr=head[fr];addr!=-1;addr=edges[addr].last)
            {
                to=edges[addr].to;
                dp[to]=max(dp[to],dp[fr]+edges[addr].l);
                if(!(--in[to])) q.push(to);
            }
        }
    }
} G;

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&v,&e);
        G.init();
        for(int i=0,fr,to,l;i<e;++i)
        {
            scanf("%d %d %d",&fr,&to,&l);
            G.add(fr,to,l);
        }
        G.topsort();
        int ans=0;
        for(int i=1;i<=v;++i)
            if(dp[i]>ans) ans=dp[i]; 
        printf("%d\n",ans);
    }
    return 0;
}

/*=======================================
added at 2019.Apr03 16:12:55	problem:JSK1254
拓扑排序求DAG的最长路径
初始化不正确WA2
=======================================*/