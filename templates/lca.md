### 倍增LCA

> 预处理$O(Elog_2V)$,查询$O(log_2V)$

```c++
const int DEP = 20; // log_2(MAXV)
struct LCA : Graph
{
    int depth[MAXV], fa[MAXV][DEP];

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
                //一个点的第(2^i)个祖先是它的第(2^ i-1)个祖先的第(2^ i-1)个祖先
                for(int j = 1; (1 << j) <= depth[to]; ++j)
                    fa[to][j] = fa[fa[to][j - 1]][j - 1];
                q.push(to);
            }
        }
    }

    int query(int a, int b)
    { // 注意用于处理两点路径信息的时候,都先更新再上跳
        if(depth[a] < depth[b]) swap(a, b);
        for(int i = DEP - 1; i >= 0; --i) //先抬到同一层
            if(depth[a] - (1 << i) >= depth[b])
                a = fa[a][i];
        if(a == b) return a;
        for(int i = DEP - 1; i >= 0; --i) //如果祖先相同,说明高于等于LCA
            if(fa[a][i] != fa[b][i])
                a = fa[a][i], b = fa[b][i];
        return fa[a][0]; // 注意这里还要再更新一次路径信息
    }
};
```

