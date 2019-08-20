#include <bits/stdc++.h>

using namespace std;

const int MAXV = 2005, MAXE = 2 * MAXV * MAXV;
int v, e;

namespace G
{
struct Edge
{
    int to, last;
    void set(int _to, int _last) { to = _to, last = _last; }
} edges[MAXE << 1]; // 边记得开两倍!!!

int top, head[MAXV];

void init() { top = 0, memset(head, -1, sizeof(head)); }

void add(int fr, int to)
{
    edges[top].set(to, head[fr]);
    head[fr] = top++;
}

int check[MAXV], match[MAXV], pre[MAXV]; // check->bfs的时间戳,match->匹配点,pre->bfs祖先

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
                {
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
    // memset(check,0,sizeof(check));
    // memset(match,0,sizeof(match));
    for(int i = 1; i <= v; ++i)
        if(!match[i])
            if(bfs(i)) ++ans;
    return ans;
}
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int n, m;
    scanf("%d %d %d", &n, &m, &e);
    v = n + m;
    G::init();
    for(int i = 0, fr, to; i < e; ++i)
    {
        scanf("%d %d", &fr, &to);
        if(fr > n || to > m) continue;
        G::add(fr + n, to), G::add(to, fr + n);
    }
    printf("%d\n", G::hungarian());
    return 0;
}