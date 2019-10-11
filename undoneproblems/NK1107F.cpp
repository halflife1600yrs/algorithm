#include <bits/stdc++.h>

using namespace std;

const int MAXN=1005;
typedef unsigned long long ull;
typedef pair<ull,ull> puu;
typedef pair<puu,int> pui;
pui trid[MAXN];

bool cmp(const pui& a,const pui& b)
{
    ull x=a.first.second*(b.first.first+b.first.second);
    ull y=b.first.second*(a.first.first+a.first.second);
    return x==y?a.second<b.second:x>y;
}

int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        ull a,b,c;
        for(int i=0;i<n;++i)
        {
            scanf("%llu %llu %llu",&a,&b,&c);
            trid[i]=pui(puu(a+b,c),i);
        }
        sort(trid,trid+n,cmp);
        for(int i=0;i<n-1;++i) printf("%d ",trid[i].second+1);
        printf("%d\n",trid[n-1].second+1);
    }
    return 0;
}