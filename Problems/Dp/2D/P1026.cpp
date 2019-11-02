#include <algorithm>
#include <iostream>
#include <cstring>
#include <bitset>
#include <cstdio>
#include <vector>
#include <cmath>
#include <tuple>
#include <queue>
#include <set>
#include <map>

using namespace std;

const int MAXN=205,INF=0x7f7f7f7f;
char str[MAXN],word[10][MAXN];

bool isprefix(char* s1,char* s2)
{
    int i=0;
    for(;s1[i]&&s2[i]&&s1[i]==s2[i];++i);
    return s2[i]==0;
}

int lenz[MAXN],d[MAXN][MAXN],dp[MAXN][MAXN];

int main()
{
    int K,p,s,l;
    scanf("%d %d",&p,&K);
    char ss[25];
    for(int i=0;i<p;++i)
    {
        scanf("%s",ss);
        strcpy(str+i*20,ss);
    }
    l=strlen(str);
    scanf("%d",&s);
    for(int i=0;i<s;++i)
        scanf("%s",word[i]);
    memset(lenz,0x7f,sizeof(lenz));
    int ans=0;
    for(int i=0;i<l;++i)
    {
        for(int j=0;j<s;++j)
            if(isprefix(str+i,word[j]))
                lenz[i]=min(lenz[i],(int)strlen(word[j]));
        if(lenz[i]<INF)
        {
            ++ans;
            for(int j=0;j<lenz[i]-1;++j) ++d[i][i+j];
        }
    }
    if(K==1)
    {
        printf("%d\n",ans);
        return 0;
    }
    memset(dp,0x7f,sizeof(dp));
    for(int j=0;j<l-1;++j)
    {
        for(int i=j-1;i>=0;--i)
            d[i][j]+=d[i+1][j];
        dp[j][1]=d[0][j];
    }
    for(int i=1;i<K-1;++i)
        for(int j=i-1;j<l-2;++j)
            for(int k=j+1;k<l-1;++k)
                dp[k][i+1]=min(dp[k][i+1],dp[j][i]+d[j+1][k]);
    for(int j=ans,i=ans=0;i<l;++i) ans=max(ans,j-dp[i][K-1]);
    printf("%d\n",ans);
    return 0;
}

/*==================================================================
added at 2019-11-02 11:12:30 P1026
数据太弱了
==================================================================*/