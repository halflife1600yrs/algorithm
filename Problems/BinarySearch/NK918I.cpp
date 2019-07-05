#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e5+5;
int t[MAXN];
int n,m,c;

int check(int limit)
{
    int first=0,num=0;
    for(int i=0;i<n;++i)
    {
        if(t[i]-t[first]>limit||i-first>=c)
        {
            ++num;
            first=i;
        }
    }
    ++num;
    return num;
}

int main()
{
    scanf("%d %d %d",&n,&m,&c);
    for(int i=0;i<n;++i)
    {
        scanf("%d",&t[i]);
    }
    sort(t,t+n);
    int maxi=t[n-1],mini=t[0];
    int fr=0,frv=n,to=maxi-mini+1,tov=ceil(1.0*n/c),mid,midv;
    while(to-fr>1)
    {
        mid=(fr+to)>>1;
        midv=check(mid);
        if(midv<=m) to=mid,tov=midv;
        else fr=mid,frv=midv;
    }
    if(frv>m) printf("%d\n",fr+1);
    else printf("%d\n",fr);
    return 0;
}

/*=======================================
added at 2019.Jun09 10:04:15	problem:NK918I
二分枚举答案，判断需要车数是否满足条件
很简单的思路但是一开始没有反应过来。
=======================================*/