#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
const int sz = 6005;
pii num[sz];
char sum[sz * 9];
int top;
struct inv
{
    int data, fr, lenz;
} invs[sz];

void add_sum(int x)
{
    int tmp = x, lenz = 0, multi = 1;
    while(tmp) tmp /= 10, lenz++, multi *= 10;
    multi /= 10;
    return;
}

bool cmp(inv a, inv b)
{
    return a.data < b.data;
}

int compare(int fr1, int fr2, int lenz)
{
    for(int i = fr1, j = fr2; i < lenz; ++i, ++j)
    {
        if(sum[i] < sum[j])
            return -1;
        else if(sum[j] < sum[i])
            return 1;
    }
    return 0;
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int n;
    for(int time, _ = scanf("%d", &time); time--; _++)
    {
        printf("Case #%d: ", _);
        scanf("%d", &n);
        top = 0;
        for(int i = 0; i < n; ++i)
        {
            scanf("%d", &invs[i].data);
            invs[i].fr = top;
            add_sum(invs[i].data);
            invs[i].to = top;
        }
        sort(invs, invs + n, cmp);
        // for(int i = 0; i < n; ++i) printf("%d ", num[i].first);
        // printf("\n");
        int pos1 = -1, pos2 = -1;
        for(int i = 0; i < n - 1; ++i)
        {
            if(invs[i].to - invs[i].fr < invs[i + 1].to - invs[i + 1].fr)
            {
                if(pos1 < 0)
                    pos1 = i;
                else if(pos2 < 0)
                {
                    pos2 = i;
                    break;
                }
            }
        }
        if(pos1 < 0) pos1 = n - 1;
        if(pos2 < 0) pos2 = n - 1;
        // printf("%d %d\n", pos1, pos2);
        if(pos1 == 0)
        { //只有一个最小的
        }
    }
    return 0;
}