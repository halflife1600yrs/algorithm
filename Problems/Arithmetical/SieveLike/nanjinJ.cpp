#include <bits/stdc++.h>

using namespace std;

const int sz = 2e7 + 5;
int F[sz], pri[1300000], num_pri = 0;
long long ans[sz];
bool isCom[sz] = {};

void init()
{
    F[1] = 1;
    for(int i = 2; i < sz; i++)
    {
        if(!isCom[i]) pri[num_pri++] = i, F[i] = 2;
        for(int j = 0; j < num_pri && i * pri[j] < sz; j++)
        {
            isCom[i * pri[j]] = 1;
            if(i % pri[j])
            {
                F[i * pri[j]] = F[i] * 2;   //这里想错了
            } else
            {
                if(i % (pri[j] * pri[j]) == 0)
                    F[i * pri[j]] = 0;
                else
                    F[i * pri[j]] = F[i / pri[j]]; //这里想错了
                break;
            }
        }
    }
}

int main()
{
    init();
    ans[1] = 1;
    for(int i = 2; i < sz; i++)
        ans[i] = ans[i - 1] + F[i];
    int cas, n;
    scanf("%d", &cas);
    while(cas--)
    {
        scanf("%d", &n);
        printf("%lld\n", ans[n]);
    }
}

/*=======================================
added at 2018年9月21日 21:50:05	problem:nanjinJ

=======================================*/