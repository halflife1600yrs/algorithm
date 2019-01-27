#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    ll a[200];
    a[1]=1,a[2]=1;
    for(int i=3;i<200;++i)
    {
        a[i]=a[i-1]+a[i-2];
        if(a[i]%2==0)
        {
            
        }
        printf("%lld\n",a[i]&(a[i]-1));
    }
    return 0;
    
}