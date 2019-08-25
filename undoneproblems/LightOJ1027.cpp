#include <bits/stdc++.h>

using namespace std;

int main()
{
    for(int T,n,_=scanf("%d",&T);T--;++_)
    {
        scanf("%d",&n);
        int x,p=0,q=0,lp=0,lq=0;
        for(int i=0;i<n;++i)
        {
            scanf("%d",&x);
            if(x>0) ++p,lp+=x;
            else ++q,lq-=x;
        }
        printf("Case #%d: ",_);
        if(p) printf("%d/1",lp+lq);
        else puts("inf");
    }
    return 0;
}