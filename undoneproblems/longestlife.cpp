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
const int MAXN=1e5+5;
int t[MAXN],q[MAXN];
double a[MAXN],b[MAXN];

inline double f(int x,int k)
{
    return -a[k]*x+b[k];
}

inline double up(int i,int j)
{
    return b[i]-b[j];
}

inline double down(int i,int j)
{
    return a[i]-a[j];
}

int main()
{
    freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    ll n;
    int p,c;
    scanf("%lld %d %d",&n,&p,&c);
    for(int i=1,x,y;i<=p;++i)
    {
        scanf("%d %d %d",&t[i],&x,&y);
        a[i]=y/(double)x;
    }
    int head=0,tail=1;
    a[0]=1,b[0]=n;
    double maxi=n;
    for(int i=1;i<=p;++i)
    {
        while(head<tail-1&&f(t[i],q[head])<=f(t[i],q[head+1]))
            ++head; // 维护下凸壳
        // debug2(a[i],f(t[i],q[head]));
        // debug2(a[q[head]],b[q[head]]);
        b[i]=-a[q[head]]*t[i]+b[q[head]]-c+a[i]*t[i];
        double tmp=(-a[q[head]]*t[i]+b[q[head]]-c)/a[i]+t[i];
        // debug2(b[i],tmp);
        maxi=max(maxi,tmp);
        while(head<tail-1&&up(q[tail-1],q[tail-2])*down(q[tail-2],i)>=up(q[tail-2],i)*down(q[tail-1],q[tail-2]))
            --tail;
        q[tail++]=i;
        // for(int i=0;i<tail;++i) printf("%d ",q[i]);
        // puts("");
    }
    printf("%.8lf\n",(double)maxi);
    return 0;
}