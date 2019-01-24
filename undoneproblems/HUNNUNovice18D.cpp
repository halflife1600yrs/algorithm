#include <bits/stdc++.h>

using namespace std;

#define DEBUG
#define debug1(x) std::cout << #x " = " << x << std::endl;
#define debug2(x, y) std::cout << #x " = " << x << " ," #y " = " << y << std::endl;

typedef long long ll;
const int sz = 2e5 + 5;
char range[sz], aim[sz];
int state[sz], incrz[sz], l1, l2;

void get_state()
{
    for(int i = 1; i < l2; i++)
    {
        int a = 0, b = 0;
        while(i + a < l2)
        {
            if(range[i + a] == range[a])
                a++;
            else
            {
                if(range[i + a] < range[a]) state[i + a + 1] += a;
                break;
            }
        }
    }
    for(int i = 1; i < l2; i++)
        state[i] += state[i - 1];
}

ll check(int x, int& next)
{
    ll ans = 0;
    for(int j = 0; j < l2; j++)
    {
        if(range[x + j] > aim[j])
        {
            while(range[next + j] > aim[0] && next < l1) next++;
            return ans;
        } else if(range[x + j] < aim[j])
            return ans + l1 - x - j;
        else if(range[x + j] == aim[j])
        {

            if(j < l2 - 1)
                ans++;
            else
                return ans;
        }
    }
    return ans;
}

int main()
{
    while(~scanf("%s %s", &range, &aim))
    {
        l1 = strlen(range), l2 = strlen(aim);
        ll ans = 0;
        int next = 0;
        memset(state, 0, sizeof(state));
        memset(incrz, 0, sizeof(incrz));
        get_state();
        for(int i = 0; i < l1; i = next)
            ans += check(i, next);
        printf("%lld\n", ans);
    }
}