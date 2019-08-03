### 倍增LCA

> 预处理$O(Elog_2V)$,查询$O(log_2V)$

```c++
const int DEPTH = 20; // log_2(MAXV)
int lg2[MAXV];
int get_log(int x)
{ //保存每个数对2的对数
    if(lg2[x]) return lg2[x];
    for(int i = 0; i < 22; ++i)
        if((1 << i) > x) return (lg2[x] = i - 1);
}
struct LCA : Graph
{
    int depth[MAXV], fa[MAXV][DEPTH];

    void bfs(int root)
    { //bfs得到所有结点的第(2^i)个祖先
        queue<int> q;
        q.push(root);
        fa[root][0] = -1, depth[root] = 0;
        int fr, to;
        while(!q.empty())
        { //标准bfs过程
            fr = q.front(), q.pop();
            for(int i = head[fr]; i != -1; i = edges[i].last)
            {
                to = edges[i].to;
                if(to == fa[fr][0]) continue;
                fa[to][0] = fr, depth[to] = depth[fr] + 1;
                //关键点,一个数的第(2^i)个祖先是它的第(2^ i-1)个祖先的第(2^ i-1)个祖先
                for(int j = 1; (1 << j) <= depth[to]; ++j)
                    fa[to][j] = fa[fa[to][j - 1]][j - 1];
                q.push(to);
            }
        }
    }
    int query(int a, int b)
    { // 注意用于处理两点路径信息的时候,都先更新再上跳
        if(depth[a] < depth[b]) swap(a, b);
        while(depth[a] > depth[b]) //先抬到同一层
            a = fa[a][get_log(depth[a] - depth[b])];
        if(a == b) return a;
        for(int i = get_log(depth[a]); i >= 0; --i)
            if(fa[a][i] != fa[b][i]) //如果祖先相同,说明高于等于LCA,这时候要continue
                a = fa[a][i], b = fa[b][i]; //不同的话说明可以继续跳,先跳一步
        // 注意这里还要再更新一次路径信息
        return fa[a][0]; // 返回lca编号
    }
};
```

## Tarjan

> 复杂度$O(V+E)$

```c++
struct Stack
{
    int data[MAXV], t;
    void add(int x) { data[t++] = x; }
    int top() { return data[t]; }
} S;

struct TARJAN : Graph
{
    bool ins[MAXV];
    int low[MAXV], dfn[MAXV], dfs_num;

    int tarjan()
    { // 返回强连通分量数目
        dfs_num = S.t = 0;
        // memset(ins, 0, sizeof(ins));
        memset(dfn, -1, sizeof(dfn));
        int ans = 0;
        for(int i = 1; i <= v; ++i)
            if(dfn[i] == -1) ans += dfs(i);
        return ans;
    }

    int dfs(int fr)
    {
        low[fr] = dfn[fr] = ++dfs_num;
        S.add(fr);
        ins[fr] = 1;
        int to, ans = 0;
        for(int i = head[fr]; ~i; i = edges[i].last)
        {
            to = edges[i].to;
            if(dfn[to] == -1)
            {
                ans += dfs(to);
                low[fr] = min(low[to], low[fr]);
            } else if(ins[to])
                low[fr] = min(dfn[to], low[fr]);
        }
        if(dfn[fr] == low[fr])
        {
            ++ans;
            while(S.top() != fr)
            {
                --S.t;
                ins[S.top()] = 0;
            }
        }
        return ans;
    }
};
```

