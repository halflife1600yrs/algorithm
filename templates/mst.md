### PRIM

> $O(V^2)$

```c++
ll dis[MAXV];
bool vis[MAXV];
ll graph[MAXV][MAXV]; // 邻接矩存边,初始化为INF
void add(int fr, int to, ll l)
{ // 邻接矩阵的对称性
    graph[fr][to] = graph[to][fr] = min(graph[to][fr], l);
}
ll prim()
{
    memset(dis, 0x7f, sizeof(dis));
    // memset(vis, 0, sizeof(vis));
    dis[1] = 0, vis[1] = 1;
    int lenz = 0, last = 1, next; // lenz记录mst边数
    ll ans = 0, mini;
    for(int i = 0; i < v - 1; ++i)
    {
        mini = INF, next = -1;
        for(int j = 1; j <= v; ++j)
        {
            if(vis[j]) continue;
            if(graph[last][j] < dis[j]) dis[j] = graph[last][j];
            if(dis[j] < mini) mini = dis[j], next = j;
        }
        if(next == -1) break;
        ans += mini, ++lenz;
        vis[next] = 1;
        last = next;
    }
    if(lenz != v - 1) return -1;
    return ans;
}
```

### KRUSKAL

> $O(Elog_2E)$

```c++
int top, u_set[MAXV]; // 并查集
int getf(int x)
{
    if(u_set[x] == x) return x;
    return u_set[x] = getf(u_set[x]);
}
struct Edge
{
    int fr, to, l;
    void set(int _fr, int _to, ll _l) { fr = _fr, to = _to, l = _l; }
    bool operator<(const Edge& x) const { return l < x.l; }
} edges[MAXE];

void init() { top = 0; }

void add(int fr, int to, ll l) { edges[top++].set(fr, to, l); }

ll kruskal(int v)
{
    for(int i = 0; i < v; ++i) u_set[i] = i;
    sort(edges, edges + top);
    ll ans = 0;
    int fr, to, x, y;
    for(int i = 0; i < top; ++i)
    {
        fr = edges[i].fr, to = edges[i].to;
        x = getf(fr), y = getf(to);
        if(x == y) continue;
        ans += edges[i].l;
        u_set[y] = x; // 注意这里更新的是y和x的fa
    }
    return ans;
}
```

### 拓扑排序

> $O(V)$

```c++
struct TOPSORT : Graph
{
    int in[MAXV];
    ll dp[MAXV]; // 以拓扑排序求DAG的最长路为例

    void add(int fr, int to, ll l) // override
    { // init里面没有in的初始化,多组样例不要忘记加
        edges[top].set(to, head[fr], l);
        ++in[to];
        head[fr] = top++;
    }

    void topsort()
    {
        queue<int> q;
        // memset(dp, 0, sizeof(dp));
        for(int i = 1; i <= v; ++i)
            if(!in[i]) q.push(i);
        int fr, to;
        while(!q.empty())
        {
            fr = q.front(), q.pop();
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                dp[to] = max(dp[to], dp[fr] + edges[i].l);
                if(!(--in[to])) q.push(to);
            }
        }
    }
};
```

