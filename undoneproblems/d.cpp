#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN=1e6+5;
struct Node
{
    int id,x,y;
} angle[MAXN];
ll ans[MAXN],dp[MAXN];
const double pi=acos(-1);

inline bool cmp(const Node& a,const Node& b)
{
    return cross(a,b)<0;
}

inline ll cross(const Node& a,const Node& b)
{
    return 1ll*a.x*b.y-a.y*b.y;
}

int main()
{
    int n;
    for(int i=0,x,y;i<n;++i)
    {
        scanf("%d %d",&x,&y);
        angle[i].x=x,angle[i].y=y,angle[i].id=i;
    }
    int m;
    scanf("%d",&m);
    ans[m]=0;
    Node angle0=angle[m];
    sort(angle,angle+n,cmp);
    int pos;
    int i=0;
    ll c;
    for(;i<n;++i)
    {
        pos=angle[i].id;
        if(pos==angle0.id) continue;
        c=cross(angle0,angle[i]);
        if(c<=0)
        {
            ans[pos]=-1;
            dp[pos]=0;
            continue;
        } else
        {
            dp[angle[i].id]=ans[angle[i].id]=c;
            break;
        }
    }
    ll c2;
    for(;i<n;++i) // 从开始点向后转的第二个点开始
    {
        pos=angle[i].id;
        c=cross(angle0,angle[i]);
        ans[i]=
        if(dp[i-1]) dp[i]=min(dp[i-1]+cross[])
    }
    return 0;
}