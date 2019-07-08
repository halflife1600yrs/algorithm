#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
int mini; //记录物品最小价值
ll dp[2][405][305]; //这里设400是因为mini=1的情况下最大费用为400，是mini的400倍
//dp[i][j][k]表示前i个物品放到背包大小为j*mini+k下产生最大价值
//这样就不用对300以下讨论了
int w[105],v[105]; //费用，价值

ll* get_pos(bool i,ll used)
{ //通过费用得到dp对应点的位置
    return &dp[i][used/mini][used%mini];
}

int main()
{
    int n,limit;
    scanf("%d %d",&n,&limit);
    mini=1e9+7;
    for(int i=0;i<n;++i)
    {
        scanf("%d %d",&w[i],&v[i]);
        if(mini>w[i]) mini=w[i];
    }
    memset(dp,-1,sizeof(dp));
    bool pos=0;
    ll sum=0,ans=0;
    dp[0][0][0]=0;
    if(w[0]<limit) dp[0][w[0]/mini][w[0]%mini]=v[0],ans=v[0];
    for(int i=0;i<n-1;pos=!pos,++i)
    { //因为背包中用较少的物品可能得到的体积在物品变多之后一定也能取到，因此不要每次都把dp的一层初始化为-1
        sum+=w[i];
        ll *cur,last,used;
        for(int j=0,_endJ=min(1ll*limit/mini,sum/mini);j<=_endJ;++j)
        {
            for(int k=0,_endK=min(mini,i*3+4);k<_endK;++k)
            {
                last=dp[pos][j][k];
                if(dp[pos][j][k]<0) continue; //当前这个体积不可能取到，跳过
                if(dp[!pos][j][k]<last) dp[!pos][j][k]=last; //不取当前物品的情况
                used=1ll*j*mini+k+w[i+1]; //取当前物品后的费用
                if(used>limit) continue; //超过限制就不要
                cur=get_pos(!pos,used);
                if(*cur<last+v[i+1]) *cur=last+v[i+1];
                if(*cur>ans) ans=*cur; //如果当前最大就记为答案
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}