#include <iostream>
#include <cstdio>

using namespace std;

const int MAXV=105;
bool graph[MAXV][MAXV];
int in[MAXV],out[MAXV];

int main()
{
    int v,e;
    scanf("%d %d",&v,&e);
    for(int i=0,fr,to;i<e;++i)
    {
        scanf("%d %d",&fr,&to);
        graph[fr][to]=1;
        ++out[fr],++in[to];
    }
    for(int k=1;k<=v;++k)
        for(int i=1;i<=v;++i)
            for(int j=1;j<=v;++j)
                if(graph[i][k]&&graph[k][j]&&!graph[i][j])
                {
                    graph[i][j]=1;
                    ++out[i],++in[j];
                }
    int ans=0;
    for(int i=1;i<=v;++i)
        if(out[i]+in[i]==v-1)
            ++ans;
    printf("%d\n",ans);
    return 0;
}

/*=======================================
added at 2019.Apr09 19:19:59	problem:POJ3660
floyed最小传递闭包
=======================================*/