#include <bits/stdc++.h>

using namespace std;

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    long long n;
    char c,clear[5];
    scanf("%lld%3[ \n\r]",&n,clear);
    int x,get;
    while(1)
    {
        get=scanf("%c%d",&c,&x);
        if(get<2) break;
        switch (c)
        {
            case '+': n+=x; break;
            case '-': n-=x; break;
            case '*': n*=x; break;
            case '%': n%=x; break;
            case '^': n*=n; break;
            default: break;
        }
    }
    printf("%lld\n",abs(n));
    return 0;
}