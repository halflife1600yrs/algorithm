#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> Pii;
Pii items[105];

bool cmp(Pii a,Pii b) { return a.first>b.first; }

int main()
{
    int n,limit;
    scanf("%d %d",&n,&limit);
    for(int i=0;i<n;++i) scanf("%d %d",&items[i].first,&items[i].second);
    sort(items,items+n,cmp);
    int start=0,maxi=0;
    
    return 0;
}