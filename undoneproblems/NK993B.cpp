#include <bits/stdc++.h>

using namespace std;

const int MAXN=2e5+5;
int cow[MAXN];

int main()
{
    int n,h;
    scanf("%d%d",&n,&h);
    for(int i=0;i<n;++i)
        scanf("%d",&cow[i]);
    sort(cow,cow+n,greater<int>());
    int ans=0,sum=0;
    for(int i=0;i<n;++i)
    {
        sum+=cow[i],++ans;
        if(sum>=h) break;
    }
    printf("%d",ans);
    return 0;
}