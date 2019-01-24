#include <bits/stdc++.h>
using namespace std;

const int sz = 57500;
int legal[30] = {2, 3, 5, 7, 11, 13, 17, 23, 27, 31, 37, 53, 71, 73, 113, 131, 311, 317};
int ans[318] = {0, 0, 2, 3, 3, 5, 5, 7, 7, 7, 7, 11};
int val[256];

int main()
{
    for (char c = '1', i = 1; c <= '9'; c++, i++)
    {
        val[c] = i;
    }
    for (int i = 4; i < 17;i++)
    {
        for (int j = legal[i]; j < legal[i + 1]; j++)
        {
            ans[j] = legal[i];
        }
    }
    char n[105];
    int cas = 0;
    while(~scanf("%s",n))
    {
        cas++;
        int lenz = strlen(n);
        if (lenz > 3)
            printf("317\n");
        else
        {
            int m = 0;
            for (int i = lenz - 1, j = 1; i >= 0; i--, j *= 10)
                m += j * val[n[i]];
            if (m >= 317)
                printf("Case #%d : 317\n",cas);
            else
                printf("Case #%d : \n", cas, ans[m]);
        }
    }
    return 0;
}

/*=======================================
added at 2018年9月12日 14:11:42	problem:shenyangk
纯思维题
其实很简单仔细想就会发现最大的数是317
=======================================*/