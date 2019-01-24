#include <bits/stdc++.h>

using namespace std;

#define DEBUG
#define debug1(x) std::cout<<#x" = "<<x<<std::endl
#define debug2(x,y) std::cout<<#x" = "<<x<<" ,"#y" = "<<y<<std::endl

const int sz = 1e5 + 5;
int pos[sz], ans[sz];
bool chosen[sz];

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int n;
    while(~scanf("%d", &n))r
    {
        for(int i = 1; i <= n; ++i) scanf("%d", &pos[i]);
        memset(ans, 0, sizeof(ans));
        memset(chosen, 0, sizeof(chosen));
        int last = 1e9, mini = 1;
        for(int i = 1; i <= n; ++i)
        {
            if(pos[i] < last)
                ans[pos[i]] = mini, chosen[mini] = 1, ++mini;
            last = pos[i];
        }
        // for(int i = 1; i <= n; ++i)
        // {
        //     printf("%d ", ans[i]);
        // }
        // printf("\n");
        int i = 1, j = 1;
        while(i <= n && j <= n)
        {
            // printf("%d %d\n", i, j);
            while(i <= n && ans[i]) i++;
            while(j <= n && chosen[j]) j++;
            ans[i] = j;
            i++, j++;
        }
        for(int p = 1; p <= n; ++p) printf("%d ", ans[p]);
        printf("\n");
    }
    return 0;
}