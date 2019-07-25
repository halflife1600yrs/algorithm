#include <bits/stdc++.h>

typedef long long ll;
const int MAXN=40;
int land[MAXN][MAXN],n;
int in[MAXN],top;
ll sum[MAXN],maxi=0;

void dfs(int st,ll ans)
{ // 从第几个人开始搜起,还需要加几个人,当前答案
    if(top==n)
    {
        maxi=std::max(ans,maxi);
        return;
    }
    ll provide=0;
    for(int i=st;i<(n<<1);++i)
    {
        for(int j=provide=0;j<top;++j) provide+=land[i][in[j]];
        in[top++]=i; // 放进去
        dfs(i+1,ans+sum[i]-(provide<<1));
        --top; // 回溯
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=0;i<(n<<1);++i)
        for(int j=0;j<(n<<1);++j)
            scanf("%d",&land[i][j]),sum[i]+=land[i][j];
    dfs(top=1,sum[0]);
    printf("%lld\n",maxi);
    return 0;
}

/*==================================================================
added at 2019-07-20 13:47:08	NK882F
2
0 2 3 4
2 0 7 5
3 7 0 1
4 5 1 0
3
0 2 3 4 5 6
2 0 4 5 6 7
3 4 0 3 2 1
4 5 3 0 5 7
5 6 2 5 0 5
6 7 1 7 5 0
这题用网络流的问题不在于是否在限制下达到最大值，而是是否正好达到限制
实际选少几个可能比全选大
==================================================================*/