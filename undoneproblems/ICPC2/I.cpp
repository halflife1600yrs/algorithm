#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
const int MAXN=1e6+5;
int ti[MAXN];
pii dif[MAXN];

int main()
{
    int n,y,x;
    while(~scanf("%d %d",&n,&y))
    {
        for(int i=1;i<=n;++i)
            scanf("%d",&ti[i]);
        sort(ti+1,ti+1+n);
        multiset<pii> ss;
        for(int i=1;i<n;++i) dif[i]=pii(ti[i+1]-ti[i],i);
        sort(dif+1,dif+n);
        for(int i=1;i<=y;++i)
        {
            int pos=ss.lower_bound(pii(i,))
        }
    }
    return 0;
}