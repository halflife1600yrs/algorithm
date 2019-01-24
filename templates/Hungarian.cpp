#include <bits/stdc++.h>

using namespace std;

const int maxv = 2005, maxe = 1e6 + 5;
int v, e, n, m;
struct Graph
{
    int top, head[maxv];
    int check[maxv], match[maxv], pre[maxv];
    struct Edge
    {
        int to, last;
        void set(int _to, int _last) { to = _to, last = _last; }
    } edges[maxe];
    void init() { top = 0, memset(head, -1, sizeof(head)); }
    void addedge(int fr, int to)
    {
        edges[top].set(to, head[fr]);
        head[fr] = top++;
    }
    int Hungarian(int n, int m)
    {
        int ans = 0;
        memset(match, 0, sizeof(match));
        for(int i = 1; i <= n; ++i)
        {
            if(!match[i])
            {
                memset(check, 0, sizeof(check));
                if(dfs(i)) ++ans;
            }
        }
        return ans;
    }
    int hungarian(int n, int m)
    { //check保存bfs树的树根，pre保存该点的前一个同侧点，match保存匹配点
        int ans = 0;
        memset(match, 0, sizeof(match));
        memset(check, 0, sizeof(check));
        memset(pre, 0, sizeof(pre));
        for(int i = 1; i <= n; ++i)
        {
            if(!match[i])
                if(bfs(i)) ans++;
        }
        return ans;
    }
    bool dfs(int fr)
    { //dfs(fr)返回true表示从该点找下去可以找到一条增广路，也即找到一个点未被匹配
        int to;
        for(int addr = head[fr]; addr != -1; addr = edges[addr].last)
        {
            to = edges[addr].to;
            if(!check[to])
            {
                check[to] = 1;
                if(!match[to] || dfs(match[to]))
                {
                    match[fr] = to;
                    match[to] = fr;
                    return true;
                }
            }
        }
        return false;
    }
    bool bfs(int root)
    {
        queue<int> q;
        while(!q.empty()) q.pop();
        q.push(root);
        pre[root] = 0;
        bool flag = 0;
        int fr, to;
        while(!q.empty() && !flag)
        {
            fr = q.front(), q.pop();
            for(int addr = head[fr]; addr != -1; addr = edges[addr].last)
            {
                to = edges[addr].to;
                if(check[to] != root)
                { //每次push的都是match[to]，所以只会加入与root同侧的点
                    check[to] = root;
                    q.push(match[to]);
                    if(match[to])
                        pre[match[to]] = fr;
                    else
                    { //找到增广路径，进行调整
                        flag = 1;
                        while(fr)
                        { //当前路径是pre[fr]->(match[fr]->fr)->to，将其调整为(pre[fr]->match[fr])->(fr->to)
                            int t = match[fr];
                            match[fr] = to, match[to] = fr;
                            fr = pre[fr], to = t;
                        }
                    }
                }
            }
        }
        return match[root] != 0;
    }
} G;

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    while(~scanf("%d %d %d", &n, &m, &e))
    {
        v = n + m;
        int a, b;
        G.init();
        for(int i = 0; i < e; ++i)
        { //两边的图都是1开始记
            scanf("%d %d", &a, &b);
            if(a > n || b > m) continue;
            G.addedge(a, n + b);
        }
        printf("%d\n", G.hungarian(n, m));
    }
    return 0;
}

/*=======================================
added at 2018年12月20日 20:49:25	problem:P3386
二分图最优匹配模板题
=======================================*/