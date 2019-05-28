#include <bits/stdc++.h>

using namespace std;

const int MAXV=505,MAXE=MAXV*MAXV,INF=0x7f7f7f7f;
int top,head[MAXV];
struct Edge
{
    int to,last,l;
    void set(int _to,int _last,int _l) { to=_to,last=_last,l=_l; }
} edges[MAXE];

void init() { top=0,memset(head,-1,sizeof(head)); }

void add(int fr,int to,int c)
{
    edges[top].set(to,head[fr],c);
    head[fr]=top++;
    edges[top].set(fr,head[to],0);
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

int main()
{
    int n,sum;
    scanf("%d",&n);
    init();
    const int S=n+1,T=n+2; 
    for(int i=1,a,b;i<=n;++i)
    {
        scanf("%d %d",&a,&b);
        if(a-b>0) add(S,i,a-b),sum+=a-b;
        else add(i,T,b-a);
    }
    int fr,to;
    while(~scanf("%d %d",&fr,&to)) add(to,fr,INF);
    int ans=dinic(S,T);
    printf("%d\n",sum-ans);
    return 0;
}

/*=======================================
added at 2019.May15 21:50:10	problem:NK15828
最大权闭合子图模板
=======================================*/