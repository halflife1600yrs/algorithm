#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool resolve(ll up,ll down,ll& b,ll& c)
{
    bool ans=0;
    ll k=down/up,a0=down%up,x;
    b=9e18,c=9e18;
    for(int i=1,end=sqrt(down)+1;i<end;++i)
    {
        if(down%i==0)
        {
            if((i+a0)%up==0)
            {
                x=(i+a0)/up;
                if(k+x<b)
                {
                    b=k+x;
                    c=down/(up*x-a0)*b;
                    ans=1;
                }
            } else if((down/i+a0)%up==0)
            {
                x=(down/i+a0)/up;
                if(k+x<b)
                {
                    b=k+x;
                    c=down/(up*x-a0)*b;
                    ans=1;
                }
            }
        }
    }
    return ans;
}

int main()
{
    int n;
    for(int T,_=scanf("%d",&T);T--;)
    {
        scanf("%d %d",&_,&n);
        int k=n/4,a0=n&0x03;
        ll a,b,c;
        for(int i=1;;++i)
        {
            a=k+i;
            ll up=4*i-a0,down=(4*k+a0)*a;
            if(resolve(up,down,b,c)) break;
        }
        printf("%d %lld %lld %lld\n",_,a,b,c);
    }
    return 0;
}

/*=======================================
added at 2019.Mar19 20:45:46	problem:CSU2276
=======================================*/
/*=======================================
added at 2019.Mar20 14:04:50	problem:CSU2276
第一次wa的原因：
resolve里的i应该是从1开始枚举而不是从2开始
=======================================*/