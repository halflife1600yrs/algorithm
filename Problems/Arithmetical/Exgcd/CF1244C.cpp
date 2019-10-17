#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

typedef long long ll;

ll exgcd(ll l, ll r, ll& x, ll& y)
{
    if(r == 0)
    {
        x = 1, y = 0;
        return l;
    } else
    {
        ll d = exgcd(r, l % r, y, x);
        y -= l / r * x;
        return d;
    }
}

int main()
{
    ll n,p,d,w,x,y;
    cin>>n>>p>>w>>d;
    ll g=exgcd(w,d,x,y);
    if(p%g) puts("-1");
    else
    {
        ll t=w/g;
        y=y%t;
        if(y<0) y+=t;
        y=y*((p/g)%t)%t;
        x=(p-d*y)/w;
        if(d*y>p||x+y>n) puts("-1");
        else printf("%lld %lld %lld\n",x,y,n-x-y);
    }
    return 0;
}

/*==================================================================
added at 2019-10-13 17:47:39 cf1244C
一开始没有想到最小化平局数量所以比赛的时候想了好久
没有考虑最小化平局数量也比答案大的情况
==================================================================*/