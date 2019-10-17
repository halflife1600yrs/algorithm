#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <tuple>
#include <queue>
#include <set>
#include <map>
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
const int MAXN=3e6+5,MODE=1e9+7;
int inv[MAXN],mul[MAXN],imul[MAXN];

void pre()
{
    inv[0]=inv[1]=mul[1]=mul[0]=imul[1]=imul[0]=1;
    for(int i=2;i<MAXN;i++)
    {
        inv[i]=((MODE-MODE/i)*(ll)inv[MODE%i])%MODE;
        mul[i]=i*(ll)mul[i-1]%MODE;
        imul[i]=inv[i]*(ll)imul[i-1]%MODE;
    }
}

inline int add(int x,int y)
{
    return (x+=y)>=MODE?x-MODE:x;
}

ll quickpow(int base,int ind)
{
    ll ans=1;
    for(;ind;base=base*(ll)base%MODE,ind>>=1)
        if(ind&1) ans=ans*base%MODE;
    return ans;
}

int C(int x,int n)
{
    return mul[n]*(ll)imul[x]%MODE*imul[n-x]%MODE;
}

int get(int x,int n,int t)
{
    // debug2(x,t);
    int ans=(quickpow(n,t)*quickpow(x,n+1)+MODE-x)%MODE;
    // debug1(ans);
    for(int i=0,tmp;i<t;++i)
    {
        tmp=C(i,t)*(ll)add(get(x,n,i),MODE-x)%MODE;
        // debug1(tmp);
        ans=add(ans,(t-i)&1?MODE-tmp:tmp);
    }
    return ans*quickpow(x-1,MODE-2)%MODE;
}

int main()
{
    int T,n,k,r;
    scanf("%d",&T);
    while(T--)
}