#include <bits/stdc++.h>

using namespace std;

int main()
{
    int a, b, c, d, e, f;
    while(~scanf("%d %d %d",&a,&b,&c))
    {
        scanf("%d %d %d", &d, &e, &f);
        int ans = min(a, e) + min(b, f) + min(c, d);
        printf("%d\n", ans);
    }
}