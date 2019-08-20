### dinic算法

```c++
struct DINIC : Graph
{
    int depth[MAXV];
    bool bfs(int start, int end)
    {
        queue<int> q;
        fill(depth + 1, depth + V + 1, -1); // 一定要初始化bfs可能运行多次
        q.push(start);
        depth[start] = 0;
        int fr, to;
        while(!q.empty())
        {
            fr = q.front(), q.pop();
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if(depth[to] == -1 && edges[i].l > 0)
                    depth[to] = depth[fr] + 1, q.push(to);
            }
        }
        return depth[end] > 0;
    }

    ll dfs(int fr, int end, ll addflow = INF)
    {
        if(fr == end) return addflow;
        int to, d = depth[fr] + 1;
        ll tf = 0, add;
        for(int i = head[fr]; ~i; i = edges[i].last)
        { // 一次dfs多次增广,tf记录当前已经增广流量
            to = edges[i].to;
            if(depth[to] == d && edges[i].l > 0)
            {
                add = dfs(to, end, min(addflow - tf, edges[i].l));
                edges[i].l -= add, edges[i ^ 1].l += add, tf += add;
            }
        }
        if(!tf) depth[fr] = -1; // 因为是多次dfs增广,不能增广的点标记深度为-1
        return tf;
    }

    ll dinic(int start, int end)
    {
        ll ans = 0;
        while(bfs(start, end)) ans += dfs(start, end);
        return ans;
    }
};
```

