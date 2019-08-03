#include <bits/stdc++.h>

using namespace std;

const double EPS=1e-12;
const int MAXN=105;
int stop[MAXN];

int main()
{
    int n,vb,vs;
    scanf("%d %d %d",&n,&vb,&vs);
    for(int i=1;i<=n;++i) scanf("%d",&stop[i]);
    int x,y,pos=1;
    scanf("%d %d",&x,&y);
    double mini=1e100,ds=1e100;
    for(int i=2;i<=n;++i)
    {
        double t=1.0*stop[i]/vb+hypot(x-stop[i],y)/vs;
        if(t<mini)
            mini=t,pos=i;
        else if(abs(t-mini)<EPS&&hypot(x-stop[i],y)/vs<ds)
            mini=t,pos=i;
    }
    printf("%d\n",pos);
    return 0;
}

/*==================================================================
added at 2019-08-03 12:48:29 D
3 2 1
0 6 10
10 3
==================================================================*/