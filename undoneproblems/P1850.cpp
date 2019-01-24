#include <bits/stdc++.h>
using namespace std;

#define DEBUG
#define debug1(x) std::cout << #x " = " << x << std::endl;
#define debug2(x, y) std::cout << #x " = " << x << " ," #y " = " << y << std::endl;

int n, m, v, e;
int room[2005], room2[2005];
const float INF = 1e38;
float rate[2005], expact[2005];
float dis[305][305];
bool cmp(float a, float b) { return a < b; }
void floyed()
{
    for(int k = 1; k <= v; ++k)
        for(int i = 1; i <= v; ++i)
            for(int j = 1; j <= v; ++j)
                if(dis[i][k] + dis[k][j] < dis[i][j])
                    dis[i][j] = dis[i][k] + dis[k][j];
}
int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    scanf("%d%d%d%d", &n, &m, &v, &e);
    for(int i = 0; i < n; i++) scanf("%d", &room[i]);
    for(int i = 0; i < n; i++) scanf("%d", &room2[i]);
    for(int i = 0; i < n; i++) scanf("%f", &rate[i]);
    for(int i = 1; i <= v; i++)
        for(int j = 1; j <= v; j++)
            if(i == j)
                dis[i][j] = 0;
            else
                dis[i][j] = INF;
    int from, to;
    float w;
    for(int i = 0; i < e; i++)
    {
        scanf("%d %d %f", &from, &to, &w);
        if(from != to) dis[to][from] = dis[from][to] = min(dis[from][to], w);
    } 
    // printmap();
    floyed();
    // printmap();
    float distance = 0;
    for(int i = 0; i < n - 1; i++)
        distance += dis[room[i]][room[i + 1]];
    // debug1(distance);
    expact[0] = rate[0] * (dis[room2[0]][room[1]] - dis[room[0]][room[1]]);
    for(int i = 1; i < n - 1; i++)
        expact[i] = rate[i] * (dis[room[i - 1]][room2[i]] + dis[room2[i]][room[i + 1]] - dis[room[i - 1]][room[i]] - dis[room[i]][room[i + 1]]);
    expact[n - 1] = rate[n - 1] * (dis[room[n - 2]][room2[n - 1]] - dis[room[n - 2]][room[n - 1]]);
    sort(expact, expact + n, cmp);
    // for(int i = 0; i < n; i++) printf("%.2f ", expact[i]);
    // printf("\n");
    for(int i = 0; i < m; i++)
        if(expact[i] < 0)
            distance += expact[i];
        else
            break;
    printf("%.2f\n", distance);
    return 0;
}

/*=======================================
added at 2018年9月28日 11:54:03	problem:P1850
void printmap()
{
    for(int i = 1; i <= v; i++)
    {
        for(int j = 1; j <= v; j++)
            printf("%.2f ", dis[i][j]);
        printf("\n");
    }
    printf("\n");
}
没有考虑到相邻的点同时取到的问题

=======================================*/