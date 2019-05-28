#include <bits/stdc++.h>

using namespace std;

const int MAXN=60,MAXV=60*60,MAXE=60*MAXV,INF=0x7f7f7f7f;

int n,m;
char land[MAXN][MAXN];

struct Graph
{ // 向前星存边框架,后面的算法继承此类;比赛的时候把struct去掉
    struct Edge
    {
        int to, last, l;
        void set(int _to, int _last, int _l) { to = _to, last = _last, l = _l; }
    } edges[MAXE]; // 注意!!!边记得开两倍!!!
    int top, head[MAXV];

    void init() { top = 0, memset(head, -1, sizeof(head)); }

    void add(int fr, int to, int l)
    {
        edges[top].set(to, head[fr], l);
        head[fr] = top++;
    }

    int depth[MAXV];

    bool bfs(int start,int end)
    {
        memset(depth,-1,sizeof(depth));
        queue<int> q;
        q.push(start);
        depth[start]=0;
        int fr,to;
        while(!q.empty())
        {
            fr=q.front(),q.pop();
            for(int i=head[fr];~i;i=edges[i].last)
            {
                to=edges[i].to;
                if(depth[to]!=-1||edges[i].l<=0) continue;
                depth[to]=depth[fr]+1;
                q.push(to);
            }
        }
        return depth[end]>0;
    }

    int dfs(int fr,int end,int addflow=INF)
    {
        if(fr==end) return addflow;
        int tf=0,to;
        for(int i=head[fr];~i;i=edges[i].last)
        {
            to=edges[i].to;
            if(depth[to]!=depth[fr]+1||edges[i].l<=0) continue;
            int add=dfs(to,end,min(addflow-tf,edges[i].l));
            tf+=add,edges[i].l-=add,edges[i^1].l+=add;
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
} G;

char read()
{
    char c;
    while(c=getchar())
    {
        if(c=='#'||c=='x'||c=='*') return c;
        else continue;
    }
    return -1;
}

inline int pos(int x,int y) { return (x-1)*m+y; }

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
        {
            land[i][j]=read();
            if(land[i][j]=='*')
            {
                G.add(0,pos(i,j),1);
                G.add(pos(i,j),0,0);                
            }
        }
    for(int i=1,j,k;i<=n;++i)
    {
        j=1,k=1;
        for(int j=1;j<n;++j,++k)
            if(land[i][j]=='*') break;
        for(++j;j<=n;++j)
        {
            if(land[i][j]=='*')
            {
                G.add(pos(i,j),pos(i,k),1);
                G.add(pos(i,k),pos(i,j),0);
            }
        }
        j=1,k=1;
        for(int j=1;j<=m;++j)
        {
            
        }
    }
    return 0;
}