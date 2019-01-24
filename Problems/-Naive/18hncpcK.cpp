#include <bits/stdc++.h>

using namespace std;
#define debug1(x) cout << #x "=" << x << endl;
#define debug2(x, y) cout << #x "=" << x << " " #y "=" << y << endl;
typedef long long ll;
const int sz = 5e5 + 5;
const int mode = 1e9 + 7;
int A[sz], B[sz];
ll preB[sz];

int main()
{
    int a, b, L, R;
    ll ans;
    while(~scanf("%d%d%d%d",&a,&b,&L,&R))
    {
        for (int i = 0; i <= a;i++)
            scanf("%d", &A[i]);
        scanf("%d", &B[0]);
        preB[0] = B[0];
        for (int i = 1; i <= b;i++)
        {
            scanf("%d", &B[i]);
            preB[i] = (preB[i - 1] + B[i]) % mode;
        }
        ans = 0;
        for (int i = max(0,L - b); i <= min(a,R); i++)
        {
            // debug1(i);
            int l = L - i - 1, r = min(b, R - i);
            // debug2(l, r);
            ans = (ans + A[i] * (preB[r] - (l < 0 ? 0 : preB[l])) % mode + mode) % mode;
            // debug1(ans);
        }
        printf("%lld\n", ans);
    }
    return 0;
}