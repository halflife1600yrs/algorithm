#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

const int MAXV = 1e4 + 5, MAXE = 2 * MAXV, INF = 0x7f7f7f7f;
int V, Q, ans;

namespace G
{
struct Edge
{
    int to, last, l;
    void set(int _to, int _last, int _l = 0) { to = _to, last = _last, l = _l; }
} edges[MAXE];

int top, head[MAXV];
int sz[2][MAXV], mini, heart; // sz[0]是包含该点为根的子树大小,sz[1]是该点最大的子树
bool vis[MAXV]; // vis标记有没有被选为根节点

void init()
{
    top = 0;
    fill(head + 1, head + V + 1, -1);
    fill(vis + 1, vis + V + 1, 0);
}

void add(int fr, int to, int l = 0)
{
    edges[top].set(to, head[fr], l);
    head[fr] = top++;
}

int get_heart(int fr, int fa, int sum)
{
    sz[0][fr] = 1, sz[1][fr] = 0;
    for(int i = head[fr], to; ~i; i = edges[i].last)
    {
        to = edges[i].to;
        if(vis[to] || to == fa) continue;
        get_heart(to, fr, sum);
        sz[0][fr] += sz[0][to];
        sz[1][fr] = max(sz[1][fr], sz[0][to]);
    }
    if(max(sz[1][fr], sum - sz[0][fr]) < mini)
        mini = max(sz[1][fr], sum - sz[0][fr]), heart = fr;
    return heart;
}
int dis[MAXV], t_;
void get_dis(int fr, int fa, int d)
{ // 这是check的附属操作,只用来暂存节点信息,不进行其他操作
    if(d > Q) return;
    dis[t_++] = d;
    for(int i = head[fr], to; ~i; i = edges[i].last)
    {
        to = edges[i].to;
        if(vis[to] || to == fa) continue;
        get_dis(to, fr, d + edges[i].l);
    }
}
int exist[MAXV], e_;
void check(int fr)
{ // 检查答案,点分治的核心操作
    for(int i = head[fr], to; ~i; i = edges[i].last)
    {
        to = edges[i].to;
        if(vis[to]) continue;
        t_ = 0; // 清空dis队列
        get_dis(to, fr, edges[i].l); // 统计子树信息
        ans += t_; // 加上每条边到根的距离
        sort(dis, dis + t_);
        for(int i = 0; i < t_; ++i)
            ans += upper_bound(exist, exist + e_, Q - dis[i]) - exist;
        int x = t_ - 1, y = e_ - 1, z = x + y + 1;
        while(x >= 0 && y >= 0)
            exist[z--] = dis[x] > exist[y] ? dis[x--] : exist[y--];
        while(x >= 0) exist[z--] = dis[x--];
        e_ += t_;
    }
    e_ = 0;
}
void divide(int fr)
{
    vis[fr] = 1;
    check(fr);
    for(int i = head[fr], to; ~i; i = edges[i].last)
    {
        to = edges[i].to;
        if(vis[to] || sz[0][to] <= 1) continue;
        divide(get_heart(to, -1, mini = sz[0][to]));
    }
}
}

int main()
{
    while(~scanf("%d %d", &V, &Q), V | Q)
    {
        G::init();
        int fr, to, l;
        for(int i = 1; i < V; ++i)
        {
            scanf("%d %d %d", &fr, &to, &l);
            G::add(fr, to, l), G::add(to, fr, l);
        }
        ans = 0;
        G::divide(G::get_heart(1, -1, G::mini = V));
        printf("%d\n", ans);
    }
    return 0;
}

/*==================================================================
added at 2019-08-25 11:43:15 P4178
点分治模板题,求树上距离小于等于k的点对数量,因为k较小所以可以使用权值树状数组
==================================================================*/