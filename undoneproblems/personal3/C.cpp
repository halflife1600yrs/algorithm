#include <bits/stdc++.h>
#define DEBUG
#define debug1(x) std::cout << #x " = " << (x) << std::endl
#define debug2(x, y) std::cout << #x " = " << (x) << " ," #y " = " << (y) << std::endl
#define heightp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }

using namespace std;

typedef pair<int,int> pii;
const int MAXN=105,INF=0x7f7f7f7f;
const int xx[4]={1,-1,0,0},yy[4]={0,0,1,-1};
int n,m,land[MAXN][MAXN];
int dw[MAXN][MAXN],dr[MAXN][MAXN];
int height[MAXN][MAXN][5*MAXN];
bool inq[MAXN][MAXN];

#define nxt a+xx[i]][b+yy[i]
void bfs(int x,int y)
{
    memset(dw,0x7f,sizeof(dw));
    queue<pii> q;
    dw[x][y]=0;
    q.push(pii(x,y));
    int a,b;
    while(!q.empty())
    {
        a=q.front().first,b=q.front().second;
        q.pop();
        for(int i=0;i<4;++i)
        {
            if(land[nxt]<=land[a][b]&&dw[nxt]>dw[a][b]+1)
            {
                dw[nxt]=dw[a][b]+1;
                q.push(pii(a+xx[i],b+yy[i]));
            }
        }
    }
}

void bfs2(int x,int y)
{
    memset(dr,0x7f,sizeof(dr));
    memset(height,0x7f,sizeof(height));
    queue<pii> q;
    dr[x][y]=0;
    height[x][y]=0;
    q.push(pii(x,y));
    int a,b;
    while(!q.empty())
    {
        a=q.front().first,b=q.front().second;
        inq[a][b]=0;
        q.pop();
        for(int i=0;i<4;++i)
        {
            if(dw[nxt]>dr[a][b]+1) // 走过去就被水淹了
            {
                if(max(height[a][b],land[nxt]-land[a][b])<height[nxt])
                {
                    dr[nxt]=dr[a][b]+1;
                    height[nxt]=max(height[a][b],land[nxt]-land[a][b]);
                    if(!inq[nxt]) inq[nxt]=1,q.push(pii(a+xx[i],b+yy[i]));
                }
            }
        }
    }
}

int main()
{
    scanf("%d %d",&n,&m);
    memset(land,0x7f,sizeof(land));
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            scanf("%d",&land[i][j]);
        }
    }
    int xr,yr,xw,yw;
    scanf("%d %d",&xr,&yr);
    scanf("%d %d",&xw,&yw);
    bfs(xw,yw);
    // for(int i=1;i<=n;++i)
    // {
    //     for(int j=1;j<=m;++j)
    //     {
    //         printf("%d ",dw[i][j]);
    //     }
    //     puts("");
    // }
    // puts("");
    bfs2(xr,yr);
    // for(int i=1;i<=n;++i)
    // {
    //     for(int j=1;j<=m;++j)
    //     {
    //         printf("%d ",dr[i][j]);
    //     }
    //     puts("");
    // }
    // puts("");
    // for(int i=1;i<=n;++i)
    // {
    //     for(int j=1;j<=m;++j)
    //     {
    //         printf("%d ",height[i][j]);
    //     }
    //     puts("");
    // }
    // puts("");
    int ans=INF;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(dw[i][j]==INF&&height[i][j]<ans)
            {
                ans=height[i][j];
            }
        }
    }
    if(ans==INF) puts("-1");
    else printf("%d\n",ans);
    return 0;
}