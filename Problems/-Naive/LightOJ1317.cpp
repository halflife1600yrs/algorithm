#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n,m,k;
    double p;
    for(int T,_=scanf("%d",&T);T--;_++)
    {
        scanf("%d %d %d %lf",&n,&m,&k,&p);
        printf("Case %d: %.8lf\n",_,n*k*p);
    }
    return 0;
}