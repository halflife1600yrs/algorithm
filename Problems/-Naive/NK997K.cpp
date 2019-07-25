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

typedef pair<int,int> pii;
int xx[205],yy[205];

struct cmp
{
    bool operator()(const pii& a,const pii& b)
    {
        return a.first==b.first?a.second<b.second:a.first<b.first;
    }
};

set<pii,cmp> s;

int gcd(int x,int y)
{
    if(y==0) return x;
    return gcd(y,x%y);
}

inline void add(int x,int y)
{
    // debug2(x,y);
    int z=gcd(x,y);
    x/=z,y/=z;
    s.insert(pii(x,y));
    // debug2(x,y);
}

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0,x,y;i<n;++i)
        scanf("%d %d",&xx[i],&yy[i]);
    for(int i=0;i<n-1;++i)
        for(int j=i+1;j<n;++j)
            add(xx[i]-xx[j],yy[i]-yy[j]);
    printf("%d\n",s.size());
    return 0;
}