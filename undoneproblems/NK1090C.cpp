#include <bits/stdc++.h>

using namespace std;

const int MAXN=5005;
int num[MAXN];

int main()
{
    int n;
    scanf("%d",&n);
    int x=0;
    for(int i=0;i<n;++i)
    {
        scanf("%d",&num[i]);
        x=max(x,num[i]);
    }
    if(x==1) puts("1");
    else if(x==0) puts("0");
    else
    {
        int ans=0;
        for(int i=0;i<n;++i)
        {
            int maxi=num[i],mini=num[i],sum=0;
            for(int j=i;j<n;++j)
            {
                sum^=num[j];
                ans=max(ans,sum^maxi^mini);
                maxi=max(num[j],maxi),mini=min(num[j],mini);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}