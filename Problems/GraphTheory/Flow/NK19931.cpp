#include <bits/stdc++.h>

using namespace std;

const int MAXV=55,MAXE=MAXV*MAXV*2,INF=0x7f7f7f7f;
int n;
int land[MAXV][MAXV];
bool conn[MAXV][MAXV];

struct Quee
{
    int s,t,data[MAXV];
    void add(int x) { data[t++]=x; }
    int top() { return data[s]; }
} q;

struct Graph
{
    struct Edge
    {
        int to, last, l;
        void set(int _to, int _last, int _l) { to = _to, last = _last, l = _l; }
    } edges[MAXE];

    int top, head[MAXV];

    void init() { top = 0, memset(head, -1, sizeof(head)); }

    void add(int fr, int to, int l)
    {
        edges[top].set(to, head[fr], l);
        head[fr] = top++;
        edges[top].set(fr,head[to],0);
        head[to]=top++;
    }

    int dis[MAXV];

    bool bfs(int start,int end)
    {
        memset(dis,-1,sizeof(dis));
        q.s=q.t=0;
        q.add(start),dis[start]=0;
        int fr,to;
        while(q.s!=q.t)
        {
            fr=q.top(),++q.s;
            for(int i=head[fr];~i;i=edges[i].last)
            {
                to=edges[i].to;
                if(dis[to]!=-1||edges[i].l<=0) continue;
                dis[to]=dis[fr]+1;
                q.add(to);
            }
        }
        return dis[end]>0;
    }

    int dfs(int fr,int end,int addflow=INF,int last=0)
    {
        if(fr==end) return addflow;
        int to,tf=0,d=dis[fr]+1;
        for(int i=head[fr],add;~i;i=edges[i].last)
        {
            to=edges[i].to;
            if(dis[to]!=d||edges[i].l<=0) continue;
            add=dfs(to,end,min(edges[i].l,addflow-tf),fr);
            tf+=add,edges[i].l-=add,edges[i^1].l+=add;
        }
        if(!tf) dis[fr]=-1;
        return tf;
    }

    int dinic(int start,int end)
    {
        int ans=0;
        while(bfs(start,end)) ans+=dfs(start,end);
        return ans;
    }
} G;

void build()
{
    G.init();
    for(int i=0;i<n-1;++i) 
        for(int j=i+1;j<n;++j)
            if(land[i][j])
            {
                G.add(i,j,land[i][j]);
                G.add(j,i,land[j][i]);
            }
}

int read()
{
    char c;
    while(c=getchar())
    {
        if(c=='O') return 1;
        if(c=='X') return 0;
        if(c=='N') return INF;
        continue;
    }
    return 0;
}

int main()
{
    int a1,a2,an,b1,b2,bn;
    while(~scanf("%d",&n))
    {
        scanf("%d %d %d %d %d %d",&a1,&a2,&an,&b1,&b2,&bn);
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                land[i][j]=read();
        int start=n,end=n+1;

        build();
        G.add(start,a1,an),G.add(start,b1,bn);
        G.add(a2,end,an),G.add(b2,end,bn);
        int ans1=G.dinic(start,end);

        swap(b1,b2);
        build();
        G.add(start,a1,an),G.add(start,b1,bn);
        G.add(a2,end,an),G.add(b2,end,bn);
        int ans2=G.dinic(start,end);

        if(ans1>=an+bn&&ans2>=an+bn) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}