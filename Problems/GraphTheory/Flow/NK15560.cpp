#include <bits/stdc++.h>
using namespace std;
const int Ni = 200005;
const int MAX = 1 << 28;

struct Quee
{
    int data[Ni],s,t;
    void add(int x) { data[t++]=x; }
    int& operator[](int x) { return data[x]; }
    int front() { return data[s]; }
} q;

struct Edge
{
    int u, v, c;
    int next;
} edge[2000005];
int n, m;
int edn; //边数
int p[Ni]; //父亲
int d[Ni];
int sp, tp; //原点，汇点

inline void addedge(int u, int v, int c)
{
    edge[edn].u = u;
    edge[edn].v = v;
    edge[edn].c = c;
    edge[edn].next = p[u];
    p[u] = edn++;

    edge[edn].u = v;
    edge[edn].v = u;
    edge[edn].c = 0;
    edge[edn].next = p[v];
    p[v] = edn++;
}
int bfs()
{
    q.t=q.s=0;
    memset(d, -1, sizeof(d));
    d[sp] = 0;
    q.add(sp);
    while(q.s!=q.t)
    {
        int cur = q.front();
        ++q.s;
        for(int i = p[cur]; i != -1; i = edge[i].next)
        {
            int u = edge[i].v;
            if(d[u] == -1 && edge[i].c > 0)
            {
                d[u] = d[cur] + 1;
                q.add(u);
            }
        }
    }
    return d[tp] != -1;
}
int dfs(int a, int b)
{
    int r = 0;
    if(a == tp) return b;
    for(int i = p[a]; i != -1 && r < b; i = edge[i].next)
    {
        int u = edge[i].v;
        if(edge[i].c > 0 && d[u] == d[a] + 1)
        {
            int x = min(edge[i].c, b - r);
            x = dfs(u, x);
            r += x;
            edge[i].c -= x;
            edge[i ^ 1].c += x;
        }
    }
    if(!r) d[a] = -2;
    return r;
}

int dinic(int sp, int tp)
{
    int total = 0;
    while(bfs())
        total += dfs(sp, MAX);
    return total;
}

namespace io
{
const int SIZE = 1e7 + 10;
char inbuff[SIZE];
char *l, *r;
inline void init()
{
    l = inbuff;
    r = inbuff + fread(inbuff, 1, SIZE, stdin);
}
inline char gc()
{
    if(l == r) init();
    return (l != r) ? *(l++) : EOF;
}
void read(int& x)
{
    x = 0;
    char ch = gc();
    while(!isdigit(ch)) ch = gc();
    while(isdigit(ch)) x = x * 10 + ch - '0', ch = gc();
}
}
using io::read;

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int i, u, v, c;
    int T;
    read(T);
    while(T--)
    {
        read(n), read(m);
        edn = 0; //初始化
        memset(p, -1, sizeof(p));
        sp = 0;
        tp = 2 * n + 1;
        for(i = 1; i <= n; i++)
        {
            addedge(sp, i, 1);
            addedge(i + n, tp, 1);
            addedge(i + n, i, MAX);
        }
        for(i = 0; i < m; i++)
        {
            read(u), read(v);
            addedge(u, v + n, MAX);
        }
        printf("%d\n", n - dinic(sp, tp));
    }
    return 0;
}

/*=======================================
added at 2019.May15 19:44:27	problem:NK15560
偏序集最大独立集
转化为偏序集最小链划分/偏序集最小可相交路径划分
跟不可相交路径划分的区别是要在每个点的入点连向每个点的出点
这题卡STL
=======================================*/