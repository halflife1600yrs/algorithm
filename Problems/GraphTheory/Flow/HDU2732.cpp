#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
const int MAXN=25;
const int MAXV=4*MAXN*MAXN,MAXE=8*MAXV;
const int INF=0x7f7f7f7f;
int k;
char land[MAXN][MAXN],jump[MAXN][MAXN];

struct Quee
{
    int t;
    pii data[MAXV];
    void add(pii x) { data[t++]=x; }
    pii& operator[](int x) { return data[x]; }
} Q;

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
        edges[top].set(fr, head[to], 0);
        head[to]=top++;
    }

    int depth[MAXV];
    bool bfs(int start, int end)
    {
        queue<int> q;
        memset(depth, -1, sizeof(depth));
        q.push(start);
        depth[start] = 0;
        int fr, to;
        while(!q.empty())
        {
            fr = q.front(), q.pop();
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if(depth[to] != -1 || edges[i].l <= 0) continue;
                depth[to] = depth[fr] + 1;
                q.push(to);
            }
        }
        return depth[end] > 0;
    }

    int dfs(int fr, int end, int addflow = INF)
    {
        if(fr == end) return addflow;
        int tf = 0, to;
        for(int i = head[fr]; ~i; i = edges[i].last)
        { // 一次dfs多次增广,tf记录当前已经增广流量
            to = edges[i].to;
            if(depth[to] != depth[fr] + 1 || edges[i].l <= 0) continue;
            int add = dfs(to, end, min(addflow - tf, edges[i].l));
            edges[i].l -= add, edges[i ^ 1].l += add, tf += add;
        }
        if(tf == 0) depth[fr] = -1; // 因为是多次dfs增广,不能增广的点标记深度为-1
        return tf;
    }

    int dinic(int start, int end)
    {
        int ans = 0;
        while(bfs(start, end)) ans += dfs(start, end);
        return ans;
    }
} G;

int main()
{
    int n,m;
    char str[30];
    for(int T,_=scanf("%d",&T);T--;++_)
    {
        int sum=0;
        scanf("%d %d",&n,&k);
        Q.t=0;
        G.init();
        for(int i=0;i<n;++i)
        {
            scanf("%s",&str);
            m=strlen(str);
            for(int j=0;j<m;++j)
            {
                jump[i][j]=str[j]-'0';
                if(jump[i][j]) Q.add(pii(i,j)),Q.add(pii(i,j));
            }
        }
        for(int i=0;i<n;++i)
        {
            scanf("%s",&str);
            m=strlen(str);
            for(int j=0;j<m;++j)
                land[i][j]=str[j];
        }
        for(int i=0,x,y;i<Q.t;i+=2)
        {
            x=Q[i].first,y=Q[i].second;
            G.add(i,i+1,jump[x][y]); // 点权
            if(land[x][y]=='L') G.add(Q.t,i,1),++sum; // 从源点汇入
            if(x<=k-1||x>=n-k||y<=k-1||y>=m-k) G.add(i+1,Q.t+1,jump[x][y]); // 汇点
            for(int j=0;j<Q.t;j+=2)
                if(j!=i && abs(Q[j].first-x)+abs(Q[j].second-y)<=k)
                    G.add(i+1,j,jump[x][y]);
        }
        int ans=sum-G.dinic(Q.t,Q.t+1);
        printf("Case #%d: ",_);
        if(ans) printf("%d lizard%s %s left behind.\n",ans,ans==1?"":"s",ans==1?"was":"were");
        else printf("no lizard was left behind.\n");
    }
    return 0;
}

/*=======================================
added at 2019.May09 20:11:05	problem:HDU2732
网络流加边的地方写反了、、、
点权转换为入点到出点的流
=======================================*/