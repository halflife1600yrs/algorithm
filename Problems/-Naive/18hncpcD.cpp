#include <bits/stdc++.h>

using namespace std;
#define debug1(x) cout << #x "=" << x << endl;
#define debug2(x, y) cout << #x "=" << x << "," #y "=" << y << endl;
const int sz = 1005;
char pic[sz][sz];
bool vis[sz][sz];
const char emoji[5] = "^v<>";
int n, m;

int dfs1(int y,int x)
{
    // debug2(y, x);
    // debug1(pic[y][x]);
    if(pic[y][x]==emoji[0])
    {
        vis[y][x] = 1;
        if(y+1<n&&x+1<m&&pic[y+1][x+1]==emoji[1])
            return dfs1(y + 1, x + 1) + 1;
        else
            return 1;
    }
    if(pic[y][x]==emoji[1])
    {
        vis[y][x] = 1;
        if(y>0&&x+1<m&&pic[y-1][x+1]==emoji[0])
            return dfs1(y - 1, x + 1) + 1;
        else
            return 1;
    }
    return 0;
}

int dfs2(int y,int x)
{
    // debug2(y, x);
    // debug1(pic[y][x]);
    if(pic[y][x]==emoji[2])
    {
        vis[y][x] = 1;
        if(y+1<n&&x+1<m&&pic[y+1][x+1]==emoji[3])
            return dfs2(y + 1, x + 1) + 1;
        else
            return 1;
    }
    if(pic[y][x]==emoji[3])
    {
        vis[y][x] = 1;
        if(y+1<n&&x>0&&pic[y+1][x-1]==emoji[2])
            return dfs2(y + 1, x - 1) + 1;
        else
            return 1;
    }
    return 0;
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    while(~scanf("%d%d",&n,&m))
    {
        // debug2(n, m);
        for (int i = 0; i < n;i++)
        {
            getchar();
            for (int j = 0; j < m;j++)
                scanf("%c",&pic[i][j]);
        }
        // for (int i = 0; i < n;i++)
        // {
        //     for (int j = 0; j < m;j++)
        //         printf("%c ", pic[i][j]);
        //     printf("\n");
        // }
        int ans = 0;
        memset(vis, 0, sizeof(vis));
        for (int j = 0; j < m;j++)
        {
            for (int i = 0; i < n;i++) if(!vis[i][j])
            {
                int state=dfs1(i, j);
                // debug1(state);
                ans += state / 3;
            }
        }
        for (int i = 0; i < n;i++)
        {
            for (int j = 0; j < m;j++) if(!vis[i][j])
            {
                int state=dfs2(i, j);
                // debug1(state);
                ans += state / 3;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

/*=======================================
added at 2018年9月12日 14:25:57	problem:18hncpcD
卖萌表情
纯贪心+dp   简单写了一下还没过
=======================================*/
/*=======================================
added at 2018年9月14日 23:08:21	problem:18hncpcD
横向的表情需要竖向遍历，否则会出现重复
=======================================*/