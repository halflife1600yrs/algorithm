#include <bits/stdc++.h>

using namespace std;

int land[60][60];

int main()
{
    int n,k;
    while(~scanf("%d%d",&n,&k))
    {
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
            scanf("%d",&land[i][j]);
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                land[i][j]+=land[i][j-1];
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                land[j][i]+=land[j-1][i];
        int maxi=0;
        for(int i=k;i<=n;++i)
            for(int j=k;j<=n;++j)
                maxi=max(maxi,land[i][j]-land[i-k][j]-land[i][j-k]+land[i-k][j-k]);
        printf("%d\n",maxi);
    }
    return 0;
}