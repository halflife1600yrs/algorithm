#include <bits/stdc++.h>

using namespace std;

int lenz[12], state[12], tmp[9 + 6 + 3];
int maxi;

inline bool check(int a, int b, int c)
{
    if(a + b > c || a + c > b || b + c > a) return false;
    return true;
}

void dfs(int depth)
{
    int top = 3 * (depth - 1) * depth / 2;
    for(int i = 0; i < 12; ++i)
        if(state[i]) tmp[top++] = i;
    for(int a = ; a < ; ++a)
    {
        state[tmp[a]] = 1;
        for(int b = a+1; b < 12; ++b)
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < 12; ++j)
            scanf("%d", &lenz[j]);
        maxi = 0;
        for(int a = 1; a < 11; ++a)
        {
            state[a] = 1;
            for(int b = a + 1; b < 12; ++b)
            {
                state[b] = 1;
                if(check(lenz[0], lenz[a], lenz[b]))
                    dfs(3);
                state[b] = 0;
            }
            state[a] = 0;
        }
    }
    return 0;
}