#include <bits/stdc++.h>

using namespace std;

const int MAXN=105;
const int MAXV=MAXN*MAXN,MAXE=MAXV*4;
const int INF=0x7f7f7f7f;
int n,m,point;
int land[MAXN][MAXN],rsum[MAXN][MAXN],dsum[MAXN][MAXN];
int edge[MAXV];

struct Node
{
    int n,x,y;
    Node() {}
    Node(int _n,int _x,int _y):n(_n),x(_x),y(_y) {}
};
struct Quee
{
    int t;
    Node data[MAXV];
    inline void add(Node x) { data[t++]=x; }
    inline Node& operator[](int x) { return data[x]; }
} wp,rp,dp;

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
};

int main()
{
    char clear[5],str[8];
    while(~scanf("%d %d",&n,&m))
    {
        G::init();
        wp.t=rp.t=dp.t=0;
        int point=2;
        for(int i=0,sum;i<n;++i)
        {
            for(int j=0;j<m;++j)
            {
                scanf("%3[ \n\r]",clear);
                if(scanf("%7[.]",str))
                {
                    land[i][j]=point;
                    wp.add(Node(point++,i,j));
                    continue;
                } else land[i][j]=-1;
                if(scanf("%d",&sum)) dsum[i][j]=sum,dp.add(Node(point++,i,j));
                else scanf("%3[X]",str);
                scanf("%c",clear);
                if(scanf("%d",&sum)) rsum[i][j]=sum,rp.add(Node(point++,i,j));
                else scanf("%3[X]",str);
            }
        }
        for(int i=0,x,y;i<rp.t;++i)
        {
            x=rp[i].x,y=rp[i].y;
            for(int j=y+1;j<m;++j)
            {
                if(land[x][j]>=0)
                {
                    --rsum[x][y];
                    G::add(rp[i].n,land[x][j],8);
                    edge[land[x][j]]=G::top-2;
                }
                else break;
            }
            G::add(0,rp[i].n,rsum[x][y]);
        }
        for(int i=0,x,y;i<dp.t;++i)
        {
            x=dp[i].x,y=dp[i].y;
            for(int j=x+1;j<n;++j)
            {
                if(land[j][y]>=0)
                {
                    G::add(land[j][y],dp[i].n,8);
                    --dsum[x][y];
                }
                else break;
            }
            G::add(dp[i].n,1,dsum[x][y]);
        }
        G::dinic(0,1);
        for(int i=0;i<n;++i)
        {
            for(int j=0;j<m;++j)
            {
                if(land[i][j]<=0) printf("_");
                else printf("%d",9-G::edges[edge[land[i][j]]].l);
                printf("%c",j<m-1?' ':'\n');
            }
        }
    }
    return 0;
}

/*=======================================
added at 2019.May09 21:36:00	problem:HDU3338
t了还没过。
还有优化空间
=======================================*/