#include <bits/stdc++.h>

using namespace std;

int a[205],b[205];
int n;

bool check()
{
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(a[i]+b[i]==a[j]&&a[j]+b[j]==a[i])
            {
                return 1;
            }
        }
    }
    return 0;
}

int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;++i) scanf("%d %d",&a[i],&b[i]);
    if(check()) printf("YE5\n");
    else printf("N0\n");
    return 0;
}