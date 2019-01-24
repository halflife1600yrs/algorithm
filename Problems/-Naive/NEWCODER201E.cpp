#include <bits/stdc++.h>

using namespace std;

int val[1000005], n, m;

int main()
{
    while(~scanf("%d %d",&n,&m))
    {
        for(int i = 0; i < n; i++) scanf("%d", &val[i]);
        sort(val, val + n);
        int ans = n;
        for(int i = 1; i < n; i++)
            if(val[i] - val[i - 1] <= m) ans--;
        printf("%d\n", ans);
    }
}