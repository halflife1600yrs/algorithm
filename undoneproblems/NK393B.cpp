#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MODE=1e8+7;

int main()
{
    int n;
    scanf("%d",&n);
    ll ans1=0;
    ll ans2=0,num;
    for(int i=0;i<n;++i)
    {
        scanf("%lld",&num);
        ans1=(ans1+num)%MODE,ans2^=num;
    }
    printf("%lld\n",(ans1+ans2)%MODE);
    return 0;
}