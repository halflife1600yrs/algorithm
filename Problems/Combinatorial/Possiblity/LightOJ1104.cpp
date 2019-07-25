#include <bits/stdc++.h>

using namespace std;

int main()
{
    for(int T,n,_=scanf("%d",&T);T--;++_)
    {
        scanf("%d",&n);
        double ans=1;
        printf("Case %d: ",_);
        for(int i=1;i<=n;++i)
        {
            ans*=1.0*(n-i)/n;
            if(ans<=0.5)
            {
                printf("%d\n",i);
                break;
            }
        }
    }
    return 0;
}