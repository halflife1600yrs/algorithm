#include <bits/stdc++.h>

using namespace std;

const int MAXV = 155, MAXE = 1e4 + 5;
typedef pair<int, int> pii;
int v, e;

struct cmp
{
    bool operator()(const pii& a, const pii& b)
    {
        return a.first == b.first ? a.second > b.second : a.first > b.first;
    }
};

priority_queue<pii, vector<pii>, cmp> ans;

namespace G
{
struct Edge
{
    int to, last;
    void set(int _to, int _last) { to = _to, last = _last; }
} edges[MAXE]; // 边记得开两倍!!!

int top, head[MAXV];

void init() { top = 0, memset(head, -1, sizeof(head)); }

void add(int fr, int to)
{
    edges[top].set(to, head[fr]);
    head[fr] = top++;
}

int low[MAXV], dfn[MAXV], dfs_num;

void dfs(int fr, int fa)
{
    dfn[fr] = low[fr] = ++dfs_num;
    for(int i = head[fr], to; ~i; i = edges[i].last)
    {
        to = edges[i].to;
        if(to == fa) continue;
        if(!dfn[to])
        {
            dfs(to, fr);
            low[fr] = min(low[fr], low[to]);
            if(low[to] > dfn[fr]) ans.push(pii(fr, to)); // 只要一颗子树里面没有回边,就是割点
        } else
            low[fr] = min(low[fr], dfn[to]);
    }
}

void tarjan()
{
    dfs_num = 0;
    for(int i = 1; i <= v; ++i)
        if(!dfn[i]) dfs(i, i);
}
}

int main()
{
    scanf("%d %d", &v, &e);
    G::init();
    for(int i = 0, fr, to; i < e; ++i)
    {
        scanf("%d %d", &fr, &to);
        G::add(fr, to), G::add(to, fr);
    }
    G::tarjan();
    while(!ans.empty())
    {
        printf("%d %d\n", ans.top().first, ans.top().second);
        ans.pop();
    }
    return 0;
}

/*==================================================================
added at 2019-08-13 21:44:46 P1656
割边模板
==================================================================*/