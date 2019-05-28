#include <bits/stdc++.h>

using namespace std;

const int MAXN=50,INF=0x7f7f7f7f;
const int MAXV=MAXN*MAXN+2*MAXN+1010,MAXE=2*(3*MAXN*MAXN+2*MAXN+3*1010);

int n,m;
int linc[MAXN],colc[MAXN];
int val[MAXN][MAXN];

struct Quee
{
    int data[MAXV],s,t;
    void push(int x) { data[t++]=x; }
    int pop() { return data[s++]; }
    int& operator[](int x) { return data[x]; }
} q;

namespace G
{
    struct Edge
    {
        int to, last, l;
        void set(int _to, int _last, int _l) { to = _to, last = _last, l = _l; }
    } edges[MAXE];
    int top, head[MAXV];
    void init() { top = 0, memset(head, -1, sizeof(head)); }
    inline void add(int fr, int to, int l)
    {
        edges[top].set(to, head[fr], l);
        head[fr] = top++;
        edges[top].set(fr,head[to],0);
        head[to]=top++;
    }

    int depth[MAXV];
    bool bfs(int start,int end)
    {
        memset(depth,-1,sizeof(depth));
        q.t=q.s=0;
        depth[start]=0;
        q.push(start);
        int fr,to;
        while(q.s!=q.t)
        {
            fr=q.pop();
            for(int i=head[fr];~i;i=edges[i].last)
            {
                to=edges[i].to;
                if(depth[to]==-1&&edges[i].l>0) depth[to]=depth[fr]+1,q.push(to);
            }
        }
        return depth[end]!=-1;
    }
    int dfs(int fr,int end,int addflow=INF)
    {
        if(fr==end) return addflow;
        int to,tf=0,d=depth[fr]+1;
        for(int i=head[fr],add;~i;i=edges[i].last)
        {
            to=edges[i].to;
            if(depth[to]==d&&edges[i].l>0)
            {
                add=dfs(to,end,min(edges[i].l,addflow-tf));
                edges[i].l-=add,edges[i^1].l+=add,tf+=add;
            }
        }
        if(tf==0) depth[fr]=-1;
        return tf;
    }
    int dinic(int start,int end)
    {
        int ans=0;
        while(bfs(start,end)) ans+=dfs(start,end);
        return ans;
    }
}

inline int linp(int x) { return x; } // 0->n-1
inline int colp(int x) { return n+x; } // n->2n-1
inline int p(int x,int y) { return (x+2)*n+y; } // 2n->(n+1)n+n-1
inline int linkp(int x) { return (n+2)*n+x; } // (n+2)n->(n+2)n+m-1

int main()
{
    scanf("%d %d",&n,&m);
    G::init();
    int start=(n+2)*n+m,end=(n+2)*n+m+1;
    int sum=0;
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
        {
            scanf("%d",&val[i][j]);
            sum+=val[i][j];
            G::add(linp(i),p(i,j),INF);
            G::add(colp(j),p(i,j),INF);
            G::add(p(i,j),end,val[i][j]);
        }
    for(int i=0,j=linp(i);i<n;++i,++j)
    {
        scanf("%d",&linc[i]);
        G::add(start,j,linc[i]);
    }
    for(int i=0,j=colp(i);i<n;++i,++j)
    {
        scanf("%d",&colc[i]);
        G::add(start,j,colc[i]);
    }
    for(int i=0,x1,y1,x2,y2,l,j=linkp(i);i<m;++i,++j)
    {
        scanf("%d %d %d %d %d",&x1,&y1,&x2,&y2,&l);
        sum+=l;
        G::add(p(x1-1,y1-1),j,INF);
        G::add(p(x2-1,y2-1),j,INF);
        G::add(j,end,l);
    }
    int ans=G::dinic(start,end);
    printf("%d\n",sum-ans);
    return 0;
}

/*=======================================
added at 2019.May28 20:23:33	problem:NK847F
最大权必合子图
再复习一下:正权点连汇点,负权点连源点,答案为正权点求和-最大流
=======================================*/