#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int MAXV=205;
const unsigned int INF=0x7f7f7f7f;
int val[MAXV];
unsigned int dis[MAXV][MAXV];

inline unsigned int cube(int x) { return x*x*x; }

int main()
{
    int v,e,q;
    for(int T,_=scanf("%d",&T);T--;_++)
    {
        scanf("%d",&v);
        for(int i=1;i<=v;++i) scanf("%d",&val[i]);
        scanf("%d",&e);
        memset(dis,0x7f,sizeof(dis));
        for(int i=0,fr,to;i<e;++i)
        {
            scanf("%d %d",&fr,&to);
            dis[fr][to]=dis[to][fr]=min(dis[fr][to],cube(abs(val[fr]-val[to])));
        }
        for(int k=1;k<=v;++k)
            for(int i=1;i<=v;++i)
                for(int j=1;j<=v;++j)
                    dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
        // for(int i=1;i<=v;++i)
        // {
        //     for(int j=1;j<=v;++j) printf("%d ",dis[i][j]);
        //     printf("\n");
        // }
        scanf("%d",&q);
        printf("Case #%d:\n",_);
        for(int i=0,end;i<q;++i)
        {
            scanf("%d",&end);
            unsigned int ans=dis[1][end];
            if(ans==INF||ans<3) printf("?\n");
            else printf("%u\n",ans);
        }
    }
    return 0;
}