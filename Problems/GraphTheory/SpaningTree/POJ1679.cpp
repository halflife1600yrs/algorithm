#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int MAXN = 120, INF = 0x7f7f7f7f;
int v, e;
int graph[MAXN][MAXN], maxe[MAXN][MAXN];
int fa[MAXN], dis[MAXN];
bool use[MAXN][MAXN], vis[MAXN];
// fa[i]记录已经在MST中的点到i距离最近的点是哪个
// 当i点加入MST中时,它的父亲节点就是fa[i]
// maxe[i][j]表示MST上i到j路径最长边

inline void add(int fr, int to, int l)
{
    graph[fr][to] = graph[to][fr] = l;
}

int prim()
{
    memset(dis, 0x7f, sizeof(dis));
    memset(vis, false, sizeof(vis)); // 记录点有没有在MST内
    memset(use, false, sizeof(use)); // 记录边有没有在MST内
    memset(maxe, 0, sizeof(maxe));
    fa[1] = 1, vis[1] = 1, dis[1] = 0;
    int ans = 0, last = 1, lenz = 0;
    for(int i = 0; i < v; ++i)
    { // 每次加一个点进入MST,加v-1次,但是我们要多跑一次处理好最后一个加入的点
        int mini = INF, next = -1;
        for(int j = 1; j <= v; ++j)
        {
            if(!vis[j])
            { // 对于没有加入MST的点,更新距离并选择下一个要加入的
                if(graph[last][j] < dis[j]) dis[j] = graph[last][j], fa[j] = last;
                if(dis[j] < mini) mini = dis[j], next = j;
            } else if(j != last)
            { // 对于已经加入MST的点更新最大边
                maxe[j][last] = maxe[last][j] = max(maxe[fa[last]][j], dis[last]);
                // 最长边要不就是last到它父结点的边要不就是j到last父亲节点的最长边
            }
        }
        if(next == -1) break;
        ans += mini, ++lenz;
        vis[next] = 1;
        use[fa[next]][next] = use[next][fa[next]] = 1;
        last = next;
    }
    if(lenz != v - 1) return -1;
    return ans;
}

int sprim()
{ // 这里记录次小生成树和MST的差
    int mini = INF;
    for(int i = 1; i < v; ++i)
    {
        for(int j = i + 1; j <= v; ++j)
        {
            if(use[i][j] || graph[i][j] == INF) continue;
            if(graph[i][j] - maxe[i][j] < mini) mini = graph[i][j] - maxe[i][j];
        }
    }
    if(mini == INF) return -1;
    return mini;
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d %d", &v, &e);
        memset(graph, 0x7f, sizeof(graph));
        for(int i = 0, fr, to, l; i < e; ++i)
        {
            scanf("%d %d %d", &fr, &to, &l);
            add(fr, to, l);
        }
        if(e == 0)
        {
            printf("0\n");
            continue;
        }
        int mini = prim();
        if(mini == -1)
        {
            printf("0\n");
            continue;
        }
        int diff = sprim();
        if(!diff)
            printf("Not Unique!\n");
        else
            printf("%d\n", mini);
    }
    return 0;
}

/*=======================================
added at 2019.Apr22 20:43:23	problem:POJ1679
次小生成树模板题
=======================================*/