#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e2+5;
char land[MAXN][MAXN];
bool able[MAXN][MAXN];

int main()
{
    int T,n,m;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(int i=0;i<n;++i)
            scanf("%s",land[i]);
        memset(able,0,sizeof(able));
        for(int i=0;i<n;++i)
        {
            for(int j=0;j<m;++j)
            {
                if(!i||able[i][j])
                {
                    if(j>0&&land[i][j]=='L'&&land[i][j-1]=='L')
                    {
                        able[i+1][j-1]=1;
                    }
                    if(j<m-1&&land[i][j]=='R'&&land[i][j+1]=='R')
                    {
                        able[i+1][j+1]=1;
                    }
                }
            }
            // for(int j=0;j<m;++j) printf("%d ",able[i+1][j]);
            // printf("\n");
        }
        bool ans=0;
        for(int i=0;i<m;++i)
            if(able[n][i])
            {
                ans=1;
                break;
            }
        if(ans) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}