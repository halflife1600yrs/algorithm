#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, ll> pil;

int main()
{
    ll n, x;
    scanf("%lld %lld", &n, &x);
    pil op[105];
    for(int i = 0; i < n; ++i)
        scanf("%d %lld", &op[i].first, &op[i].second);
    for(int i = n; i >= 0; --i)
    {
        if(op[i].first == 1) x -= op[i].second;
        else if(op[i].first==2)
            x += op[i].second;
        else if(op[i].first==3)
            x /= op[i].second;
        else if(op[i].first==4)
            x *= op[i].second;
    }
    printf("%lld\n", x);
    return 0;
}