#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MODE=1e9+7;
int n,num[10];
int dp[16][16][16][16][16][6];

int dfs(int t1,int t2,int t3,int t4,int t5,int last)
{
    if(t1+t2+t3+t4+t5==0) return 1;
    if(dp[t1][t2][t3][t4][t5][last]) return dp[t1][t2][t3][t4][t5][last];
    ll ans=0;
    if(t1) ans+=1ll*(t1-(last==1))*dfs(t1-1,t2,t3,t4,t5,0)%MODE;
    if(t2) ans+=1ll*(t2-(last==2))*dfs(t1+1,t2-1,t3,t4,t5,1)%MODE;
    if(t3) ans+=1ll*(t3-(last==3))*dfs(t1,t2+1,t3-1,t4,t5,2)%MODE;
    if(t4) ans+=1ll*(t4-(last==4))*dfs(t1,t2,t3+1,t4-1,t5,3)%MODE;
    if(t5) ans+=1ll*t5*dfs(t1,t2,t3,t4+1,t5-1,4)%MODE;
    dp[t1][t2][t3][t4][t5][last]=(int)(ans%MODE);
    return ans%MODE;
}

int main()
{
    scanf("%d",&n);
    for(int i=0,a;i<n;++i)
    {
        scanf("%d",&a);
        ++num[a];
    }
    printf("%d\n",dfs(num[1],num[2],num[3],num[4],num[5],0));
    return 0;
}

/*==================================================================
added at 2019-07-26 16:28:19 P2476
这种只跟数值每类有几个有关的题目要记得按数值分类压缩状态
==================================================================*/