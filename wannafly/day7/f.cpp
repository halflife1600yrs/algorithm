#include <bits/stdc++.h>

#define DEBUG
#define debug1(x) std::cout << #x " = " << x << std::endl
#define debug2(x, y) std::cout << #x " = " << x << " ," #y " = " << y << std::endl
#define disp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }

using namespace std;

typedef long long ll;
const int MAXN=1e3+5,mode=998244353;
int num[MAXN];

ll diff_pos(int a,int b)
{
    ll pos=0;
    for(ll i=1,j=0;i<=max(a,b);i<<=1,++j)
    {
        if((a&i)!=(b&i)) pos=j;
    }
    // debug1(pos);
    return pos;
}

int search(int m,int pos,bool digit)
{
    int front=m>>(pos+1),after=m&((1<<pos)-1);
    bool mid=m&(1<<pos)?1:0;
    int ans=front*(1<<pos);
    if(mid==digit) ans+=after+1;
    else if(mid>digit) ans+=(1<<pos);
    // debug2(front,after);
    // debug1(mid);
    // debug1(ans);
    return ans;
}

int main()
{
    int n,m;
    while(~scanf("%d %d",&n,&m))
    {
        // search(n,m,1);
        for(int i=0;i<n;++i) scanf("%d",&num[i]);
        ll pos;
        bool need;
        ll ans=0;
        for(int i=0;i<n-1;++i)
            for(int j=i+1;j<n;++j)
            {
                // debug2(num[i],num[j]);
                if(num[i]>num[j]) ans=(ans-1+mode)%mode;
                pos=diff_pos(num[i],num[j]);
                need=num[i]&(1<<pos)?0:1;
                // debug2(pos,need);
                ans=(ans+search(m,pos,need))%mode;
            }
        printf("%lld\n",ans);
    }
    return 0;
}