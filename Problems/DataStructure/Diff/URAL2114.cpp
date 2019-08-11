#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN=505;
int n,m,land[MAXN][MAXN];
ll sum_lin[MAXN][MAXN],sum_col[MAXN][MAXN],sum_lu[MAXN][MAXN];
// 每行前缀和,每列前缀和,反对角线前缀和
inline ll get_lin(int lin,int x,int y)
{
    if(lin>n||lin<1) return 0;
    if(x>y) swap(x,y);
    return sum_lin[lin][min(y,m)]-sum_lin[lin][max(1,x)-1];
}

inline ll get_col(int col,int x,int y)
{
    if(col>m||col<1) return 0;
    if(x>y) swap(x,y);
    return sum_col[min(y,n)][col]-sum_col[max(1,x)-1][col];
}

inline ll get_lu(int y,int x,int l)
{ // 从y,x位置向斜上方长度为l的和
    if(y>n) x+=y-n,l-=y-n,y=n;
    if(x>m) return 0;
    int x2=x+l,y2=y-l;
    ll ans=sum_lu[y][x];
    if(x2>m||y2<1) return ans;
    return ans-sum_lu[y2][x2];
}

ll dp[MAXN][MAXN];

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
        {
            scanf("%d",&land[i][j]);
            sum_lin[i][j]=sum_lin[i][j-1]+land[i][j];
            sum_col[i][j]=sum_col[i-1][j]+land[i][j];
        }
    for(int i=1;i<=n;++i)
        for(int j=m;j>=1;--j)
            sum_lu[i][j]=sum_lu[i-1][j+1]+land[i][j];
    int q,k,x,y;
    scanf("%d",&q);
    ll ans;
    for(int qq=0;qq<q;++qq)
    {
        scanf("%d",&k);
        dp[1][1]=0;
        for(int j=1;j<=k+1;++j)
            dp[1][1]+=get_lin(j,1,k+2-j);
        ans=dp[1][1],y=1,x=1;
        for(int j=2;j<=m;++j)
        {
            dp[1][j]=dp[1][j-1]-get_col(j-1,1,k+1)+get_lu(k+1,j,k+1);
            if(dp[1][j]>ans) ans=dp[1][j],x=j;
        }
        for(int i=2;i<=n;++i)
            for(int j=1;j<=m;++j)
            {
                dp[i][j]=dp[i-1][j]-get_lin(i-1,j,j+k)+get_lu(i+k,j,k+1);
                if(dp[i][j]>ans) ans=dp[i][j],y=i,x=j;
            }
        printf("%lld %d %d\n",ans,y,x);
    }
    return 0;
}

/*==================================================================
added at 2019-08-09 11:10:37	URAL2114
计算三种前缀和
这种要看坐标边界情况的真的很烦,然后地图上又很容易弄反x和y
==================================================================*/