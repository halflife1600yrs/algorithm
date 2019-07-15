#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e3+5;
typedef pair<int,int> pii;
pii st,en;
int n,m;
char land[4*MAXN+3][6*MAXN+3];
bool vis[4*MAXN+3][6*MAXN+3];
int dp[4*MAXN+3][6*MAXN+3];

void read()
{
    char c;
    while(c=getchar(),c!='\n');
    for(int i=0;i<4*n+3;++i)
    {
        for(int j=0;;++j)
        {
            land[i][j]=getchar();
            if(land[i][j]=='\n'||land[i][j]==-1) break;
        }
    }
}

namespace q
{
    #define top 2*MAXN*MAXN
    pii data[top];
    int s,t;
    void push(pii x)
    {
        data[t++]=x;
        if(t==top) t=0;
    }
    pii pop()
    {
        if(s==top-1)
        {
            s=0;
            return data[top-1];
        }
        return data[s++];
    }
    #undef top
}
int bfs()
{
    pii fr,to;
    int x,y;
    while(q::s!=q::t)
    {
        fr=q::pop();
        x=fr.first,y=fr.second;
        if(land[x-1][y-3]==' '&&!vis[x-2][y-6])
        {
            dp[x-2][y-6]=dp[x][y]+1;
            vis[x-2][y-6]=1;
            q::push(pii(x-2,y-6));
        }
        if(land[x-1][y+3]==' '&&!vis[x-2][y+6])
        {
            dp[x-2][y+6]=dp[x][y]+1;
            vis[x-2][y+6]=1;
            q::push(pii(x-2,y+6));
        }
        if(land[x+1][y-3]==' '&&!vis[x+2][y-6])
        {
            dp[x+2][y-6]=dp[x][y]+1;
            vis[x+2][y-6]=1;
            q::push(pii(x+2,y-6));
        }
        if(land[x+1][y+3]==' '&&!vis[x+2][y+6])
        {
            dp[x+2][y+6]=dp[x][y]+1;
            vis[x+2][y+6]=1;
            q::push(pii(x+2,y+6));
        }
        if(land[x-2][y]==' '&&!vis[x-4][y])
        {
            dp[x-4][y]=dp[x][y]+1;
            vis[x-4][y]=1;
            q::push(pii(x-4,y));
        }
        if(land[x+2][y]==' '&&!vis[x+4][y])
        {
            dp[x+4][y]=dp[x][y]+1;
            vis[x+4][y]=1;
            q::push(pii(x+4,y));
        }
        if(dp[en.first][en.second]!=-1)
            return dp[en.first][en.second];
    }
    return dp[en.first][en.second];
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        read();
        q::s=q::t=0;
        for(int i=0;i<4*n+3;i+=2)
        {
            for(int j=4;j<6*m+3;j+=6)
            {
                vis[i][j]=0;
                if(land[i][j]=='S')
                {
                    st=pii(i,j);
                    dp[i][j]=1,vis[i][j]=1;
                    q::push(st);
                } else if(land[i][j]=='T')
                {
                    en=pii(i,j);
                    dp[i][j]=-1;
                }
            }
        }
        printf("%d\n",bfs());
    }
    return 0;
}

/*==================================================================
added at 2019-07-11 16:53:37 gym102028F
尽量不要用memset初始化冗余度大的数组
对于输入比较复杂的可以不用直接转换为抽象的模型,而是直接保存为字符串数组
==================================================================*/