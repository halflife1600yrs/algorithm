#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    int n;
    for(int T,_=scanf("%d",&T);T--;_++)
    {
        scanf("%d",&n);
        ll x=0,y=0,dir=0;
        ll d;
        for(int i=0;i<n;++i)
        {
            scanf("%I64d",&d);
            switch (dir)
            {
                case 0:
                    y+=d;
                    break;
                case 1:
                    x+=d;
                    break;
                case 2:
                    y-=d;
                    break;
                case 3:
                    x-=d;
                    break;
            }
            dir=(dir+1)%4;
        }
        printf("Case #%d:%I64d\n",_,x*x+y*y);
    }
    return 0;
}