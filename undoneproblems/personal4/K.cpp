#include <bits/stdc++.h>
#define DEBUG
#define debug1(x) std::cout << #x " = " << (x) << std::endl
#define debug2(x, y) std::cout << #x " = " << (x) << " ," #y " = " << (y) << std::endl
#define disp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }

using namespace std;

const int MAXN=30;
char land[MAXN][MAXN];

int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        for(int i=1;i<=n;++i)
        {
            scanf("%s",land[i]+1);
        }
        bool vis_lin[30],vis_col[30];
        int t;
        for(char c='A';c<='Z';++c)
        {
            t=0;
            memset(vis_col,0,sizeof(vis_col));
            memset(vis_lin,0,sizeof(vis_lin));
            for(int i=1;i<=n;++i)
            {
                for(int j=1;j<=n;++j)
                {
                    if(land[i][j]==c)
                    {
                        // debug2(i,j);
                        vis_col[j]=1;
                        vis_lin[i]=1;
                        ++t;
                    }
                }
            }
            // debug1(t);
            if(t==n-1)
            {
                for(int i=1;i<=n;++i)
                    if(!vis_lin[i])
                    {
                        printf("%d ",i);
                        break;
                    }
                for(int i=1;i<=n;++i)
                    if(!vis_col[i])
                    {
                        printf("%d ",i);
                        break;
                    }
                printf("%c\n",c);
            }
        }
    }
    return 0;
}
/*==================================================================
added at 2019-08-09 13:29:33	K
6
OEYCDK
EYOKCD
KDCEOY
CKHOYE
YOEDKC
DCKYEO
3
IWL
GIW
WLI
==================================================================*/