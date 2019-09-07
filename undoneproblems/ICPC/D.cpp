#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n,m;
    for(int T,_=scanf("%d",&T);T--;++_)
    {
        scanf("%d %d",&n,&m);
        printf("Case #%d: %.6f %.6f\n",_,n==1?1:0.5,m==1?1:(m+1.0)/2.0/m);
    }
    return 0;
}