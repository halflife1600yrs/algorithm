#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned int ui;

int main()
{
    // ull a=0;
    int a1;
    scanf("%d",&a1);
    if(a1==-1)
    {
        printf("No solution\n");
        return 0;
    }
    ll a=a1+(1ll<<32);
    int b=a-(1ll<<31)+1,c=a-b;
    printf("%lld %lld\n",b,c);
    printf("%d",b+c);
    return 0;
}