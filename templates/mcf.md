### 费用流

```c++
int ans, cost;
struct G
{ // 最小费用流每条边有两个属性,l为费用,c为流量
// 加边方法为正向l,c;反向-l,0
    int start, end, dis[MAXV], prev[MAXV], pree[MAXV], minf[MAXV];
    bool vis[MAXV];
    bool spfa()
    { // 这里的初始化不能删因为多次调用
        fill(dis + 1, dis + V + 1, INF); // 最大费用的时候这里要用-INF初始化
        fill(vis + 1, vis + V + 1, 0);
        fill(minf + 1, minf + V + 1, INF);
        queue<int> q;
        q.push(start);
        dis[start] = 0, vis[start] = 1;
        pree[end] = -1;
        int fr, to;
        while(!q.empty())
        {
            fr = q.front(), q.pop();
            vis[fr] = 0;
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if(edges[i].c > 0 && dis[fr] + edges[i].l < dis[to])
                { // 最大费用的时候要改>号
                    dis[to] = dis[fr] + edges[i].l;
                    minf[to] = min(minf[fr], edges[i].c);
                    prev[to] = fr, pree[to] = i;
                    if(!vis[to]) q.push(to), vis[to] = 1;
                }
            }
        }
        return pree[end] != -1;
    }
    void extend()
    {
        int cur = end, i, tmp = minf[end];
        while(cur != start)
        {
            i = pree[cur];
            edges[i].c -= tmp;
            edges[i ^ 1].c += tmp;
            cur = prev[cur];
        }
        ans += tmp, cost += dis[end];
    }
    void mcf()
    {
        ans = cost = 0;
        while(spfa()) extend();
    }
};
```

