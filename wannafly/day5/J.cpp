#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef struct P{
    ll x,y;
}P;
struct Line
{
    ll x1,x2,y1,y2;
}a[2009];
ll cross(P a,P b,P c)//计算叉积
{
    return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}
ll f(ll n,ll m)
{
    P a1,a2,b1,b2;
    a1.x=a[n].x1;a1.y=a[n].y1;
    a2.x=a[n].x2;a2.y=a[n].y2;
    b1.x=a[m].x1;b1.y=a[m].y1;
    b2.x=a[m].x2;b2.y=a[m].y2;
    if(cross(a1,a2,b1)==0&&cross(a1,a2,b2)==0){
        ll x1,x2;
        x1=min(a1.x,a2.x);
        x2=max(a1.x,a2.x);
        if((b1.x>x1&&b1.x<x2)||((b2.x>x1&&b2.x<x2))){
            return 1;
        }
    }
    double q=(a[n].x2-a[n].x1)*(a[m].y1-a[n].y1)-(a[n].y2-a[n].y1)*(a[m].x1-a[n].x1);
    double w=(a[n].x2-a[n].x1)*(a[m].y2-a[n].y1)-(a[n].y2-a[n].y1)*(a[m].x2-a[n].x1);
    double e=(a[m].x2-a[m].x1)*(a[n].y1-a[m].y1)-(a[m].y2-a[m].y1)*(a[n].x1-a[m].x1);
    double r=(a[m].x2-a[m].x1)*(a[n].y2-a[m].y1)-(a[m].y2-a[m].y1)*(a[n].x2-a[m].x1);
    if(q*w<0&&r*e<0) return 1;
    return 0;
}

ll cnt=0;

vector<pair<ll,ll>> edg;
vector<pair<ll,ll>> poi;

int main()
{
    ll n,m,tmp1,tmp2;
    scanf("%lld%lld",&n,&m);
    for(ll i=0;i<m;i++){
        scanf("%lld%lld",&tmp1,&tmp2);
        edg.push_back(make_pair(tmp1,tmp2));
    }
    poi.push_back(make_pair(-1,-1));
    for(ll i=0;i<n;i++){
        scanf("%lld%lld",&tmp1,&tmp2);
        poi.push_back(make_pair(tmp1,tmp2));
    }
    for(ll i=0;i<edg.size();i++){
        a[i].x1=poi[edg[i].first].first;
        a[i].y1=poi[edg[i].first].second;
        a[i].x2=poi[edg[i].second].first;
        a[i].y2=poi[edg[i].second].second;
    }

    ll flag=1;
    //for(ll i=0;i<edg.size();i++)
    //    printf("line%d %lf %lf %lf %lf\n",i,a[i].x1,a[i].y1,a[i].x2,a[i].y2);

    for(ll i=0;i<edg.size();i++){
        for(ll j=i+1;j<edg.size();j++) {
            if (f(i, j)) cnt++;
        }
    }
    cout<<cnt;
    return 0;
}
