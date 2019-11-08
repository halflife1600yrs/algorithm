#include <bits/stdc++.h>

using namespace std;

const int MAXN=6e6+5,MODE=998244353;
typedef long long ll;
int g[MAXN],x[MAXN];

inline char nc()
{
    static char buf[10000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 10000000, stdin), p1 == p2) ? EOF : *p1++;
}

template<typename t>
inline t read()
{
    t res = 0;
    char ch;
    do ch = nc(); while (ch < 48 || ch > 57);
    do res = res * 10 + ch - 48, ch = nc(); while (ch >= 48 && ch <= 57);
    return res;
}

int main()
{
    int n=read<int>(),m=read<int>(),k=read<int>();
    for(int i=0;i<n;++i) x[i]=read<int>();
    for(int i=0;i<=m;++i) g[i]=read<int>();
    ll ans1=1,ans2=0,power=1,tmp;
    for(int i=0;i<n;++i)
    {
        ans1*=k-x[i];
        if(k-x[i]<0) ans1=ans1%MODE+MODE;
        else if(ans1>MODE) ans1%=MODE;
    }
    for(int i=0;i<=m;++i)
    {
        tmp=power*g[i]%MODE;
        if(tmp<0) tmp=tmp+MODE; // 防止加的是负的
        ans2+=tmp;
        if(ans2>=MODE) ans2%=MODE;
        power*=k;
        if(power>=MODE) power%=MODE;
    }
    printf("%lld\n",(ans1+ans2)%MODE);
    return 0;
}