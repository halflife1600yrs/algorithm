#include <bits/stdc++.h>

using namespace std;

const int MAXV = 10005, MAXE = 200010;
const int INF = 0x7f7f7f7f;
int v, e;
struct G
{
    int head[MAXV];
    int top;
    int depth[MAXV];
    struct Edge
    {
        int to, last, l;
        void set(int _to, int _last, int _l) { to = _to, l = _l, last = _last; }
    } edges[MAXE];
    void init() { top = 0, memset(head, -1, sizeof(head)); }
    void add(int fr, int to, int l)
    {
        edges[top].set(to, head[fr], l);
        head[fr] = top++;
    }
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
    int start,end;
    while(~scanf("%d %d %d %d", &v, &e, &start, &end))
    {
        int a, b, c;
        G.init();
        for(int i = 0; i < e; i++)
        {
            scanf("%d %d %d", &a, &b, &c);
            G.add(a, b, c);
            G.add(b, a, 0);
        }
        printf("%d\n", G.dinic(start,end));
    }
    return 0;
}

/*=======================================
addred at 2018年11月04日 20:30:07	problem:HDU3549
网络流模板题
=======================================*/
/*=======================================
added at 2018年11月29日 20:35:51	problem:P3376
t了一个下午然后转而用这个模板去做洛谷模板题的时候发现是因为MAXE没有*2导致的错误
血的教训
6 9 1 6
4 2 4
4 3 4
4 6 3
3 1 1
1 4 4
4 1 3
3 6 5
5 6 6
6 3 3
4 5 4 3
4 2 30
4 3 20
2 3 20
2 1 30
1 3 40

-- 4 50
=======================================*/