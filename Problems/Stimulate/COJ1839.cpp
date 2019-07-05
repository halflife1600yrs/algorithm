#include <bits/stdc++.h>

using namespace std;

const int MAXN=2e5+5;
int heights[MAXN];

int main()
{
    int n;
    scanf("%d",&n);
    int ans=0;
    scanf("%d",&heights[0]);
    int dir=-1; // -1向下1向上
    for(int i=1;i<n;++i)
    {
        scanf("%d",&heights[i]);
        if((heights[i]-heights[i-1])*dir<=0) ++ans,dir*=-1;
    }
    printf("%d\n",(ans+1)>>1);
    return 0;
}