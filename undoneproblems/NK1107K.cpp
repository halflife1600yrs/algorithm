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

typedef long long ll;

int main()
{
    int a,b,c,d;
    while(~scanf("%d %d %d %d",&a,&b,&c,&d))
    {
        --a,--c;
        ll x2=b/2-a/2,x1009=b/1009-a/1009,x2018=b/2018-a/2018;
        ll y2=d/2-c/2,y1009=d/1009-c/1009,y2018=d/2018-c/2018;
        ll ans=x2018*(d-c)+y2018*(b-a)-x2018*y2018
        +(x2-x2018)*(y1009-y2018)+(y2-y2018)*(x1009-x2018);
        printf("%lld\n",ans);
    }
    return 0;
}