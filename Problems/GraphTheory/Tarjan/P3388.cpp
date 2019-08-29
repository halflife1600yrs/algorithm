#include <bits/stdc++.h>

using namespace std;

const int MAXV = 2e4 + 5, MAXE = 2e5 + 5;
int v, e, ans;

bool iscut[MAXV];

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
            if(low[to] >= dfn[fr]) iscut[fr] = 1; // 只要一颗子树里面没有回边,就是割点
        } else
            low[fr] = min(low[fr], dfn[to]);
    }
    if(iscut[fr]) ++ans;
}

void tarjan()
{
    dfs_num = ans = 0;
    // memset(dfn,0,sizeof(dfn));
    for(int i = 1; i <= v; ++i)
        if(!dfn[i])
        {
            dfn[i] = low[i] = ++dfs_num;
            int child = 0;
            for(int j = head[i]; ~j; j = edges[j].last)
                if(!dfn[edges[j].to]) // 根节点需要特殊判断
                    dfs(edges[j].to, i), ++child;
            if(child >= 2) iscut[i] = 1, ++ans;
        }
}
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    scanf("%d %d", &v, &e);
    G::init();
    for(int i = 0, fr, to; i < e; ++i)
    {
        scanf("%d %d", &fr, &to);
        G::add(fr, to), G::add(to, fr);
    }
    G::tarjan();
    printf("%d\n", ans);
    for(int i = 1; i <= v; ++i)
        if(iscut[i]) printf("%d ", i);
    puts("");
    return 0;
}

/*==================================================================
added at 2019-08-13 21:07:03 P3388
tarjan割点模板
还是喜欢特判根节点而不是写在一起的
==================================================================*/