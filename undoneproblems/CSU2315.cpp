#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
const int MAXN=5005;
pii ask[MAXN];
double ans[MAXN];

bool cmp(const pii& a,const pii& b) { return a.first<b.first; }

int main()
{
    int n,tot,sum=0;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&ask[i].first);
        ask[i].second=i;
        sum+=ask[i].first;
    }
    scanf("%d",&tot);
    bool flag=0;
    if(2*tot>sum) tot=sum-tot,flag=1;
    sort(ask+1,ask+n+1,cmp);
    double x;
    for(int i=1;i<=n;++i)
    {
        x=
        if()
    }
    return 0;
}
