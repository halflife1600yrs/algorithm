#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;

const int MAXN=300;
double dis[MAXN][MAXN];
int x[MAXN],y[MAXN];

inline int square(int x) { return x*x; }

int main()
{
    int n,T=0;
    while(scanf("%d",&n),n)
    {
        ++T;
        for(int i=0;i<n;++i) scanf("%d %d",&x[i],&y[i]);
        for(int i=0;i<n-1;++i)
            for(int j=i+1;j<n;++j) dis[i][j]=dis[j][i]=sqrt(square(x[i]-x[j])+square(y[i]-y[j]));
        for(int k=0;k<n;++k)
            for(int i=0;i<n;++i)
                for(int j=0;j<n;++j)
                    dis[i][j]=min(dis[i][j],max(dis[i][k],dis[j][k]));
        printf("Scenario #%d\nFrog Distance = %.3f\n\n",T,dis[0][1]);
    }
    return 0;
}

/*=======================================
added at 2019.Apr07 19:51:47	problem:POJ2253
最短路变式
路径最大边最小值
=======================================*/