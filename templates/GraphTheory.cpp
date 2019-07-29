#include <bits/stdc++.h>

using namespace std;

typedef int Type;
const int MAXV = 1e5 + 5, MAXE = 5e5 + 5;
const int INF = 0x7f7f7f7f;
// INF的值根据需要增大
int v, e;

struct Graph
{ // 向前星存边框架,后面的算法继承此类;比赛的时候把struct去掉
    struct Edge
    {
        int to, last, l;
        void set(int _to, int _last, int _l) { to = _to, last = _last, l = _l; }
    } edges[MAXE]; // 注意!!!边记得开两倍!!!
    // 建模之后一定不要忘记计算新模型的边数
    int top, head[MAXV];

    void init() { top = 0, memset(head, -1, sizeof(head)); }

    void add(int fr, int to, int l)
    {
        edges[top].set(to, head[fr], l);
        head[fr] = top++;
    }
};

/*================================================================================*/
// 迪杰斯特拉算法
// 复杂度O((V+E)lgV)
typedef pair<int, int> pii;
struct cmp
{
    bool operator()(const pii& a, const pii& b) { return a.second > b.second; }
};

struct DIJKSTRA : Graph
{
    int dis[MAXV];
    bool vis[MAXV];

    void dijkstra(int start)
    {
        memset(dis, 0x7f, sizeof(dis));
        memset(vis, 0, sizeof(vis));
        priority_queue<pii, vector<pii>, cmp> q;
        dis[start] = 0;
        q.push(pii(start, 0));
        int fr, to;
        while(!q.empty())
        {
            fr = q.top().first, q.pop();
            if(vis[fr]) continue; // fr可能多次入队,但第一次出队时就已经更新完成
            vis[fr] = 1;
            for(int i = head[fr], d; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if(vis[to]) continue;
                d = dis[fr] + edges[i].l;
                // 这里也可以用来处理最小路径上的最大边或最大路径上的最小边
                // 求最小路径上最大边时,优先队列cmp不变,上句改为d=max(dis[fr],edges[i].l)
                // 同时下一句应该改为d更大时更新
                if(d < dis[to]) dis[to] = d, q.push(pii(to, d));
            }
        }
    }
};

/*================================================================================*/
// spfa算法
// 复杂度O(KE),如果被卡就退化为O(VE)
struct SPFA : Graph
{
    int dis[MAXV], cnt[MAXV];
    bool vis[MAXV];

    bool spfa()
    {
        memset(vis, 0, sizeof(vis));
        memset(dis, 0x7f, sizeof(dis));
        memset(cnt, 0, sizeof(cnt));
        queue<int> q;
        dis[1] = 0;
        q.push(1);
        vis[1] = cnt[1] = 1;
        int fr, to;
        while(!q.empty())
        {
            fr = q.front(), q.pop();
            vis[fr] = 0;
            for(int i = head[fr], d; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                d = dis[fr] + edges[i].l; // 这里注意即使在队列中也要更新
                if(d < dis[to])
                {
                    dis[to] = d;
                    if(vis[to]) continue;
                    vis[to] = 1, ++cnt[to];
                    if(cnt[to] > v) return 1;
                    q.push(to);
                }
            }
        }
        return 0;
    }
};

/*================================================================================*/
// 树上倍增求LCA
// 预处理O(ElgV),查询O(lgV)
// 可以用来处理树上两点间路径长、路径上最值
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
        return fa[a][0];
    }
};


/*================================================================================*/
// Prim
// O(V*V)
// 可以用Fibonacci堆优化到O(E+vlgV),但是我不会
struct PRIM
{
    int dis[MAXV];
    bool vis[MAXV];

    int graph[MAXV][MAXV];

    void init() { memset(graph, 0x7f, sizeof(graph)); }

    void add(int fr, int to, int l)
    { // 记得无向图要赋值两个点
        graph[fr][to] = graph[to][fr] = min(graph[to][fr], l);
    }

    int prim()
    {
        memset(dis, 0x7f, sizeof(dis));
        memset(vis, 0, sizeof(vis));
        dis[1] = 0, vis[1] = 1;
        int ans = 0, lenz = 0, last = 1;
        for(int i = 0; i < v - 1; ++i)
        {
            int mini = INF, next = -1;
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
};

/*================================================================================*/
// Kruskal
// O(ElgV)
struct KRUSKAL
{
    int top, u_set[MAXV]; // 并查集

    int getf(int x)
    {
        if(u_set[x] == x) return x;
        return u_set[x] = getf(u_set[x]);
    }

    struct Edge
    {
        int fr, to, v;
        void set(int _fr, int _to, int _v) { fr = _fr, to = _to, v = _v; }
        bool operator<(const Edge& x) const { return v < x.v; }
    } edges[MAXE];

    void init() { top = 0; }

    void add(int fr, int to, int l) { edges[top++].set(fr, to, l); }

    int kruskal(int v)
    {
        for(int i = 0; i < v; ++i) u_set[i] = i;
        sort(edges, edges + top);
        int ans = 0, fr, to, x, y;
        for(int i = 0; i < top; ++i)
        {
            fr = edges[i].fr, to = edges[i].to;
            x = getf(fr), y = getf(to);
            if(x == y) continue;
            ans += edges[i].v;
            u_set[y] = x; // 注意这里更新的是y和x的fa
        }
        return ans;
    }
};

/*================================================================================*/
// 拓扑排序
// 要求DAG,也可以处理DAG上路径的信息,如最长路
// O(V+E)
struct TOPSORT : Graph
{
    int in[MAXV], dp[MAXV]; // 这个dp是用来求DAG的最长路

    void add(int fr, int to, int l) // override
    { // init里面没有in的初始化,多组样例不要忘记加
        edges[top].set(to, head[fr], l);
        ++in[to];
        head[fr] = top++;
    }

    void topsort()
    {
        queue<int> q;
        memset(dp, 0, sizeof(dp));
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

/*================================================================================*/
// dinic算法
struct DINIC : Graph
{
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
                if(depth[to] == -1 && edges[i].l > 0)
                    depth[to] = depth[fr] + 1, q.push(to);
            }
        }
        return depth[end] > 0;
    }

    int dfs(int fr, int end, int addflow = INF)
    {
        if(fr == end) return addflow;
        int tf = 0, to, d = depth[fr] + 1;
        for(int i = head[fr], add; ~i; i = edges[i].last)
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

    int dinic(int start, int end)
    {
        int ans = 0;
        while(bfs(start, end)) ans += dfs(start, end);
        return ans;
    }
};

/*================================================================================*/
// 匈牙利算法
// 复杂度O(VE)
struct HUNGARIAN : Graph
{
    int check[MAXV], match[MAXV], pre[MAXV];
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
        // memset(match, 0, sizeof(match)); // 这里多个样例要更新
        // memset(check, 0, sizeof(check));
        // memset(pre, 0, sizeof(pre));
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
        for(int i = head[fr]; ~i; i = edges[i].last)
        {
            to = edges[i].to;
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
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
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
};

/*================================================================================*/
// tarjan算法
// 复杂度O(V+E)
struct Quee
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
    {
        dfs_num = S.t = 0;
        memset(ins, 0, sizeof(ins));
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

/*================================================================================*/
// 树上倍增
struct Tree : Graph
{
    int father[MAXV][DEPTH], depth[MAXV];
    void bfs(int root)
    { //bfs得到所有结点的第(2^i)个祖先
        queue<int> Q;
        Q.push(root);
        father[root][0] = -1, depth[root] = 0;
        int fr, to;
        while(!Q.empty())
        { //标准bfs过程
            fr = Q.front(), Q.pop();
            for(int addr = head[fr]; addr != -1; addr = edges[addr].last)
            {
                to = edges[addr].to;
                if(to == father[fr][0]) continue;
                father[to][0] = fr, depth[to] = depth[fr] + 1;
                //关键点，一个数的第(2^i)个祖先是它的第(2^ i-1)个祖先的第(2^ i-1)个祖先
                for(int i = 1; (1 << i) <= depth[to]; ++i)
                    father[to][i] = father[father[to][i - 1]][i - 1];
                Q.push(to);
            }
        }
    }
    int query(int a, int b)
    {
        if(depth[a] < depth[b]) swap(a, b);
        while(depth[a] > depth[b]) //先抬到同一层
            a = father[a][get_log(depth[a] - depth[b])];
        if(a == b) return a;
        for(int i = get_log(depth[a]); i >= 0; --i)
            if(father[a][i] != father[b][i]) //如果祖先相同，说明高于等于LCA，这时候要continue
                a = father[a][i], b = father[b][i]; //不同的话说明可以继续跳，先跳一步
        return father[a][0];
    }
};

int main()
{
    return 0;
}