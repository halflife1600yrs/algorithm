#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXV = 1e5 + 5, MAXE = 5e5 + 5; // 建模之后一定不要忘记计算新模型的边数
const int INF = 0x7f7f7f7f;
// INF的值根据需要增大
int V, E;

struct Graph
{ // 向前星存边框架,后面的算法继承此类
    struct Edge
    {
        int to, last;
        ll l;
        void set(int _to, int _last, ll _l = 0) { to = _to, last = _last, l = _l; }
    } edges[MAXE]; // 边记得开两倍!!!

    int top, head[MAXV];

    void init() { top = 0, fill(head + 1, head + V + 1, -1); }

    void add(int fr, int to, ll l = 0)
    {
        edges[top].set(to, head[fr], l);
        head[fr] = top++;
    }

    int times[MAXV]; // 遍历的时间戳
    void uniq()
    { // 删重边
        // fill(times + 1, times + V + 1, 0);
        for(int fr = 1, to; fr <= V; ++fr)
        {
            times[edges[head[fr]].to] = fr;
            for(int i = head[fr], j = edges[i].last; ~j; j = edges[j].last)
            {
                to = edges[j].to;
                if(times[to] == i)
                    edges[i].last = edges[j].last;
                else
                    times[to] = fr, i = j;
            }
        }
    }

    int head2[MAXV];
    void rev()
    { // 求转置,需要辅助数组head2
        fill(head2 + 1, head2 + V + 1, -1);
        for(int fr = 1, to; fr <= V; ++fr)
        {
            for(int i = head[fr], j; ~i && (j = edges[i].last, 1); i = j)
            {
                to = edges[i].to;
                edges[i].set(fr, head2[to], edges[i].l);
                head2[to] = i;
            }
        }
        for(int i = 1; i <= V; ++i) head[i] = head2[i];
    }
};

/*================================================================================*/
// 迪杰斯特拉算法
// 复杂度O((V+E)lgV)
typedef pair<ll, int> pii;
// 似乎用pair自带的比较符号会比自己重载慢一点点
struct DIJKSTRA : Graph
{
    ll dis[MAXV];
    bool vis[MAXV];

    void dijkstra(int start)
    {
        fill(dis + 1, dis + V + 1, INF);
        // fill(vis + 1, vis + V + 1, 0);
        priority_queue<pii, vector<pii>, greater<pii>> q;
        dis[start] = 0;
        q.push(pii(0, start));
        int fr, to;
        while(!q.empty())
        {
            fr = q.top().second, q.pop();
            if(vis[fr]) continue; // fr可能多次入队,但第一次出队时就已经更新完成
            vis[fr] = 1;
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if(vis[to]) continue;
                ll d = dis[fr] + edges[i].l;
                if(d < dis[to]) dis[to] = d, q.push(pii(d, to));
            }
        }
    }
};

/*================================================================================*/
// spfa算法
// 复杂度O(KE),如果被卡就退化为O(VE)
struct SPFA : Graph
{
    ll dis[MAXV];
    int cnt[MAXV];
    bool vis[MAXV];

    bool spfa()
    {
        fill(dis + 1, dis + V + 1, INF);
        // fill(vis + 1, vis + V + 1, INF);
        // fill(cnt + 1, cnt + V + 1, INF);
        queue<int> q;
        dis[1] = 0;
        q.push(1);
        vis[1] = cnt[1] = 1;
        int fr, to;
        while(!q.empty())
        {
            fr = q.front(), q.pop();
            vis[fr] = 0;
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                ll d = dis[fr] + edges[i].l; // 这里注意即使在队列中也要更新
                if(d < dis[to])
                {
                    dis[to] = d;
                    if(vis[to]) continue;
                    vis[to] = 1, ++cnt[to];
                    if(cnt[to] > V) return 1;
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
            for(int i = head[fr]; ~i; i = edges[i].last)
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

    int lca(int a, int b)
    { // 注意用于处理两点路径信息的时候,都先更新再上跳
        if(depth[a] < depth[b]) swap(a, b);
        for(int i = DEP - 1; i >= 0; --i) //先抬到同一层
            if(depth[a] - (1 << i) >= depth[b])
                a = fa[a][i];
        if(a == b) return a;
        for(int i = DEP - 1; i >= 0; --i) //如果祖先相同,说明高于等于LCA,这时候要continue不能break
            if(fa[a][i] != fa[b][i])
                a = fa[a][i], b = fa[b][i];
        return fa[a][0]; // 注意这里还要再更新一次路径信息
    }
};

/*================================================================================*/
// 建立虚树

vector<int> query;
int dfn[MAXV];
struct FAKETREE : LCA
{
    int S[MAXV], dfs_num;

    void dfs1(int fr)
    { // dfs方法
        // dfn[fr]=++dfs_num;
        for(int i = 1; (1 << i) <= depth[fr]; ++i)
            fa[fr][i] = fa[fa[fr][i - 1]][i - 1];
        for(int i = head[fr], to; ~i; i = edges[i].last)
        {
            to = edges[i].to;
            if(to == fa[fr][0]) continue;
            fa[to][0] = fr;
            depth[to] = depth[fr] + 1;
            dfs1(to);
        }
    }

    void build_fake_tree()
    {
        sort(query.begin(), query.end(), // dfn要在dfs求lca的同时处理好
            [](int a, int b) { return dfn[a] < dfn[b]; });
        int t = top = 0, father; // 建虚树之后就会清除原图上的边
        S[++t] = 1, head[1] = -1;
        for(int fr : query)
        {
            if(fr == 1) continue; // 根节点
            if((father = lca(S[t], fr)) != S[t])
            {
                while(dfn[S[t - 1]] > dfn[father]) add(S[t - 1], S[t]), --t; // 出栈并加边
                if(father != S[t - 1])
                    head[father] = -1, add(father, S[t]), S[t] = father;
                else
                    add(S[t - 1], S[t]), --t;
            }
            head[fr] = -1, S[++t] = fr;
        }
        while(t > 1) add(S[t - 1], S[t]), --t;
    }
};

/*================================================================================*/
// Prim
// O(V*V)
// 可以用Fibonacci堆优化到O(E+vlgV),但是我不会
struct PRIM
{
    ll dis[MAXV];
    bool vis[MAXV];

    ll graph[MAXV][MAXV]; // 邻接矩阵存边

    void init() { memset(graph, 0x7f, sizeof(graph)); }

    void add(int fr, int to, ll l)
    { // 记得无向图要赋值两个点
        graph[fr][to] = graph[to][fr] = min(graph[to][fr], l);
    }

    ll prim()
    {
        memset(dis, 0x7f, sizeof(dis));
        // memset(vis, 0, sizeof(vis));
        dis[1] = 0, vis[1] = 1;
        int lenz = 0, last = 1, next; // lenz记录mst边数
        ll ans = 0, mini;
        for(int i = 0; i < V - 1; ++i)
        {
            mini = INF, next = -1;
            for(int j = 1; j <= V; ++j)
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
        if(lenz != V - 1) return -1;
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
        int fr, to, l;
        void set(int _fr, int _to, ll _l) { fr = _fr, to = _to, l = _l; }
        bool operator<(const Edge& x) const { return l < x.l; }
    } edges[MAXE];

    void init() { top = 0; }

    void add(int fr, int to, ll l) { edges[top++].set(fr, to, l); }

    ll kruskal()
    {
        for(int i = 0; i < V; ++i) u_set[i] = i;
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
};

/*================================================================================*/
// 拓扑排序
// 要求DAG,也可以处理DAG上路径的信息,如最长路
// O(V+E)
struct TOPOSORT : Graph
{
    int in[MAXV];
    ll dp[MAXV]; // 以拓扑排序求DAG的最长路为例

    void add(int fr, int to, ll l) // override
    { // init里面没有in的初始化,多组样例不要忘记加
        edges[top].set(to, head[fr], l);
        ++in[to];
        head[fr] = top++;
    }

    void toposort()
    {
        queue<int> q;
        // fill(dp + 1, dp + V + 1, 0);
        for(int i = 1; i <= V; ++i)
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

/*================================================================================*/
// 匈牙利算法
// 复杂度O(VE)
struct HUNGARIAN : Graph
{
    int check[MAXV], match[MAXV], pre[MAXV];
    // check->bfs的时间戳,match->匹配点,pre->bfs祖先
    bool bfs(int root)
    {
        queue<int> q;
        q.push(root);
        pre[root] = 0;
        int fr, to, t;
        while(!q.empty())
        {
            fr = q.front(), q.pop();
            for(int i = head[fr]; ~i; i = edges[i].last)
            {
                to = edges[i].to;
                if(check[to] != root) // 还没有bfs的点
                {
                    if(!match[to])
                    { // 进行增广
                        for(int t; fr && (t = match[fr], 1); fr = pre[fr], to = t)
                            match[fr] = to, match[to] = fr;
                        return 1;
                    }
                    pre[match[to]] = fr;
                    check[to] = root;
                    q.push(match[to]);
                }
            }
        }
        return 0;
    }

    int hungarian()
    {
        int ans = 0;
        // fill(check + 1, check + V + 1, 0);
        // fill(match + 1, match + V + 1, 0);
        for(int i = 1; i <= V; ++i)
            if(!match[i])
                if(bfs(i)) ++ans;
        return ans;
    }
};

/*================================================================================*/
// tarjan算法
// 复杂度O(V+E)
namespace S
{
int data[MAXV], t;
inline void push(int x) { data[t++] = x; }
inline int top() { return data[t - 1]; }
}

struct TARJAN : Graph
{
    int dfn[MAXV], low[MAXV], dfs_num, sz[MAXV];
    bool ins[MAXV];

    void dfs(int fr)
    {
        dfn[fr] = low[fr] = ++dfs_num;
        ins[fr] = 1, S::push(fr);
        for(int i = head[fr], to; ~i; i = edges[i].last)
        {
            to = edges[i].to;
            if(!dfn[to])
            {
                dfs(to);
                low[fr] = min(low[fr], low[to]);
            } else if(ins[to])
                low[fr] = min(low[fr], dfn[to]);
        }
        if(dfn[fr] == low[fr])
        {
            sz[dfn[fr]] = 1;
            while(S::top() != fr)
            {
                ++sz[dfn[fr]];
                low[S::top()] = dfn[fr];
                ins[S::top()] = 0;
                --S::t;
            }
            ins[fr] = 0;
            --S::t;
        }
    }

    void tarjan()
    {
        // fill(dfn + 1, dfn + 1 + V, 0);
        // fill(ins + 1, ins + 1 + V, 0);
        dfs_num = S::t = 0;
        for(int i = 1; i <= V; ++i)
            if(!dfn[i]) dfs(i);
    }

    int times[MAXV], head2[MAXV], in[MAXV];

    void shrink()
    { // 直接在原图上缩点成DAG并去重边,需要两个辅助数组times和head2,in用来保存DAG的入度
        tarjan();
        fill(head2 + 1, head2 + 1 + V, -1);
        // fill(in + 1, in + 1 + V, 0);
        for(int fr = 1, i, j; fr <= V; ++fr) // 缩点
            for(i = head[fr]; ~i && (j = edges[i].last, 1); i = j)
                if(low[edges[i].to] != low[fr])
                {
                    edges[i].set(low[edges[i].to], head2[low[fr]], edges[i].l);
                    head2[low[fr]] = i;
                }
        // fill(times + 1, times + 1 + V, 0);
        for(int fr = 1, to, i, j; fr <= V; ++fr) // 去重
            for(i = head2[fr], head[fr] = -1; ~i && (j = edges[i].last, 1); i = j)
                if(times[to = edges[i].to] != fr)
                {
                    times[to] = fr;
                    edges[i].set(to, head[fr], edges[i].l);
                    head[fr] = i;
                    ++in[to];
                }
    }
};

int main()
{
    scanf("%d", &V);
    int fr, to;
    // G::init();
    for(int i = 1; i < V; ++i)
    {
        scanf("%d %d", &fr, &to);
        // G::add(fr, to), G::add(to, fr);
    }
    return 0;
}