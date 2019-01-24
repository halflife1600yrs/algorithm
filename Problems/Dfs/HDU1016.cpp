#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int n;
char flag[20]={};
char ans[20]={};
char prime[42]={0,0,2,3,0,5,0,7,0,0,0,1,0,3,0,0,0,7,0,9,0,0,0,3,0,0,0,0,0,9,0,1,0,0,0,0,0,7,0,0};

void dfs(int next)
{
    //printf("\n");
    if(next==n&&prime[ans[n-1]+ans[0]])
        {
            for(int i=0;i<n-1;i++)
            printf("%d ",ans[i]);
            printf("%d\n",ans[n-1]);
            return;
            }
    for(int i=2;i<=n;i++)
    {
        if(prime[ans[next-1]+i]&&!flag[i])
        {
            flag[i]=1;
            ans[next]=i;
            //printf("%d ",i);
            dfs(next+1);
            flag[i]=0;
            ans[next]=0;
        }
    }
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    flag[0]=1;
    ans[0]=1;
    int cas=0;
    while(~scanf("%d",&n))

    {
        cas++;
        if(n==1) continue;
        printf("Case %d:\n",cas);
        dfs(1);
        printf("\n");
    }
    return 0;
}
