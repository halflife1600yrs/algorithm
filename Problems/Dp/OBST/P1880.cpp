#include <bits/stdc++.h>

using namespace std;

const int MAXN=2*105;
int mini[MAXN][MAXN],maxi[MAXN][MAXN];
int val[MAXN];

int main()
{
    int n;
    scanf("%d",&n);
    memset(mini,0x7f,sizeof(mini));
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&val[i]);
        val[i+n]=val[i];
        mini[i][i]=maxi[i][i]=0;
        mini[i+n][i+n]=maxi[i+n][i+n]=0;        
    }
    val[0]=0;
    for(int i=1;i<=2*n+1;++i) val[i]=val[i-1]+val[i];
    for(int l=1;l<n;++l)
    {
        for(int i=1,j=l+1;j<=2*n-1;++i,++j)
        {
            for(int k=i;k<j;++k)
            {
                mini[i][j]=min(mini[i][j],mini[i][k]+mini[k+1][j]+val[j]-val[i-1]);
                maxi[i][j]=max(maxi[i][j],maxi[i][k]+maxi[k+1][j]+val[j]-val[i-1]);
            }
        }
    }
    int ans1=0x7f7f7f7f,ans2=0;
    for(int i=1;i<=n;++i)
    {
        if(mini[i][i+n-1]<ans1) ans1=mini[i][i+n-1];
        if(maxi[i][i+n-1]>ans2) ans2=maxi[i][i+n-1];
    }
    printf("%d\n%d\n",ans1,ans2);
    return 0;
}

/*==================================================================
added at 2019-07-08 10:42:18 P1880
OBST
循环的情况只要翻倍就可了
==================================================================*/