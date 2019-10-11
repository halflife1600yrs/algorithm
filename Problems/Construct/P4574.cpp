#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int INF=0x7f7f7f7f;
int L;

int check(int x)
{
    int ans=0,i=0;
    for(;i<31;++i)
        if(x&(1<<i))
            ++ans,L=max(i+1,L);
    return ans;
}

int lenz(ll x)
{
    for(int i=61;i>=0;--i)
        if(x&(1ll<<i)) return i+1;
    return 0;
}

int main()
{
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    a=check(a),b=check(b),c=check(c);
    if(a<b) swap(a,b);
    if(c>a+b) puts("-1");
    else if(c==a+b)
        printf("%d\n",(1<<c)-1);
    else
    {
        int d=a+b-c;
        ll ans=0;
        if(d>=a)
        {
            ++ans;
            for(int i=0;i<2*d-a-b;++i) ans<<=1;
            for(int i=0;i<a+b-d-1;++i) ans<<=1,++ans;
            ans<<=1;
        } else if(d>=b)
        {
            ++ans;
            for(int i=0;i<d-b;++i) ans<<=1;
            for(int i=0;i<b-1;++i) ans<<=1,++ans;
            ans<<=1;
            for(int i=0;i<a-d;++i) ans<<=1,++ans;
        } else
        {
            for(int i=0;i<d;++i) ans<<=1,++ans;
            ans<<=1;
            for(int i=0;i<a+b-2*d;++i) ans<<=1,++ans;
        }
        // debug2(L,ans);
        if(lenz(ans)<=L) printf("%lld\n",ans);
        else puts("-1");
    }
    return 0;
}

/*==================================================================
added at 2019-09-26 15:51:55 P4574
第一次做自己推了一个60^4的dp公式,后来发现不能把a和b的1混起来用
所以还是换构造的方法重新做一遍
没有考虑到d>=a的那个情况
==================================================================*/