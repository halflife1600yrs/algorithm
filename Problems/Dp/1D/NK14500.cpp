#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN=1e5+5,INF=0x3f3f3f3f,L=31;
typedef pair<int,int> pii;
int dp[2*MAXN][2];
pii num[MAXN];

bool cmp(const pii& a,const pii& b)
{
    return a.second==b.second?a.first<b.first:a.second<b.second;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;++i)
        scanf("%d %d",&num[i].second,&num[i].first);
    if(!m)
    {
        puts("0");
        return 0;
    }
    sort(num,num+m,cmp);
    vector<int> dig[31];
    int pos[31];
    for(int i=0;i<31;++i) pos[i]=0;
    for(int i=0;i<m;++i)
        for(int j=num[i].first,k=0;k<31;++k)
        {
            if(pos[k]<num[i].second-1) // 不连续的话插入一个-1
                dig[k].push_back(-1);
            dig[k].push_back((j&(1ll<<k))>0);
            pos[k]=num[i].second;
        }
    for(int i=0;i<31;++i)
        if(pos[i]<n) dig[i].push_back(-1);
    ll ans=0;
    for(int i=0;i<31;++i)
    {
        if(dig[i].size())
        {
            memset(dp,0x3f,sizeof(dp));
            if(dig[i][0]==-1) dp[0][1]=1,dp[0][0]=0;
            else dp[0][dig[i][0]]=dig[i][0];
            for(int j=1;j<dig[i].size();++j)
            {
                if(dig[i][j]==-1)
                {
                    dp[j][0]=min(dp[j-1][1],dp[j-1][0]);
                    dp[j][1]=min(dp[j-1][0]+1,dp[j-1][1]+1);
                } else
                {
                    dp[j][0]=dp[j-1][dig[i][j]];
                    dp[j][1]=dp[j-1][1^dig[i][j]]+1;
                }
            }
            ans+=min(dp[dig[i].size()-1][1],dp[dig[i].size()-1][0])*(1ll<<i);
        }
    }
    printf("%lld\n",ans);
    return 0;
}

/*==================================================================
added at 2019-08-22 17:05:24 NK14500
7 3
2 1000000000
4 24
6 19
其实应该是一道具有dp性质的题目但是分类在贪心里面就一直想贪心这么搞
然后分情况,一个格子两个格子,然后反映过来要按位操作,然后又发现不仅是1还有0要扔到队列里面
显得很麻烦,最后一想,才发现用dp思想是最简单的
然后边界问题也没有搞清楚,前面后面的-1刚开始没加
==================================================================*/