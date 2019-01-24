#include <bits/stdc++.h>

const int sz = 1e5 + 5;
int data[sz], num[sz], need[sz], need2[sz];
bool fail[sz];
int n;

int get_ans(int x)
{
    if(x > n) return 0;
    if(fail[x]) return 0;
    if(num[x] > 0) return 1;
    if(get_ans(x + 1))
    {
        if(get_ans(x + 1))
        {
            need[x + 1]++, num[x + 1]--;
            return 1;
        } else
        {
            fail[x] = 1;
            return 0;
        }
    } else
    {
        fail[x] = 1;
        return 0;
    }
}

int main()
{
    int cas;
    scanf("%d", &cas);
    for(int time = 1; time <= n; time++)
    {
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
        {
            scanf("%d", &data[i]);
            if(data[i] <= n) need[data[i]]++;
        }
        printf("Case %d: ", time);
        if(get_ans(1))
        {
            for(int i = 0; i < n; i++) need2[i] = need[i];
            if(get_ans(1))
            {
                printf("YES\n");
                for(int i = 0; i < n; i++)
                {
                    if(data[i] > n)
                        printf("0");
                    else if(need2[data[i]])
                        printf("1"), need2[data[i]];
                    else
                        printf("0");
                }
            } else
                printf("NO\n");
        } else
            printf("NO\n");
    }
    return 0;
}

/*=======================================
added at 2018年10月19日 20:30:41	problem:JILINC
吉林区域赛C题
=======================================*/