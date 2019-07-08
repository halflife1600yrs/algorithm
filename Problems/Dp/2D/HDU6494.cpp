#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
const int MAXN=1e4+5;
char str[MAXN];
int dp[MAXN][11][11];

struct triad
{
    int x,y,z;
    triad():x(0),y(0),z(0) {}
    triad(int _x,int _y,int _z):x(_x),y(_y),z(_z) {}
};

triad nextState(triad p)
{
    if(max(p.x,p.y)<=9) return p;
    if(p.x>=11&&p.y<p.x)
    {   
        if(p.x-p.y>=2) return triad(0,0,p.z+1);
        return triad(10,9,p.z);
    }
    if(p.y>=11&&p.x<p.y)
    {
        if(p.y-p.x>=2) return triad(0,0,p.z+1);
        return triad(9,10,p.z);
    }
    if(p.x==p.y) return triad(min(9,p.x),min(9,p.y),p.z);
    return p;
}

int main()
{
    int t;
    scanf("%d",&t);
    char clear[10];
    while(t--)
    {
        scanf("%5[ \n]%10005[AB?]",clear,str);
        int lenz=strlen(str);
        memset(dp[0],-1,sizeof(dp[0]));
        if(str[0]!='A') dp[0][0][1]=0;
        if(str[0]!='B') dp[0][1][0]=0;
        bool pos=1;
        int state;
        for(int i=1;i<lenz;++i,pos=!pos)
        {
            memset(dp[pos],-1,sizeof(dp[pos]));
            for(int j=0;j<11;++j)
            {
                for(int k=0;k<11;++k)
                {
                    state=dp[!pos][j][k];
                    if(state!=-1)
                    {
                        if(str[i]!='A')
                        {
                            triad p=nextState(triad(j,k+1,state));
                            dp[pos][p.x][p.y]=max(p.z,dp[pos][p.x][p.y]);
                        }
                        if(str[i]!='B')
                        {
                            triad p=nextState(triad(j+1,k,state));
                            dp[pos][p.x][p.y]=max(p.z,dp[pos][p.x][p.y]);
                        }
                    }
                }
            }
        }
        int maxi=0;
        for(int i=0;i<11;++i)
            for(int j=0;j<11;++j)
                if(dp[!(lenz&1)][i][j]>maxi)
                    maxi=dp[!(lenz&1)][i][j];
        printf("%d\n",maxi);
    }
    return 0;
}

/*=======================================
added at 2019.Apr20 14:55:57	problem:2050乒乓球
对当前分数进行dp，同时将超过10的分数转移为小于等于10的分数
=======================================*/