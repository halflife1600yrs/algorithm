#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
const int sz = 6005;
pii num[sz];
int lenz[sz];

bool cmp(pii a, pii b)
{
    return a.first == b.first ? a.second > b.second : a.first < b.first;
}

int get_lenz(int x)
{
    for(int i = 1, j = 0;; i *= 10, ++j)
        if(i > x) return j;
}

int main()
{
    int n;
    for(int time, _ = scanf("%d", &time); time--; _++)
    {
        printf("Case #%d: ", _);
        scanf("%d", &n);
        for(int i = 0; i < n; ++i)
        {
            scanf("%d", &num[i].first);
            lenz[i] = get_lenz(num[i].first);
            num[i].second = i;
        }
        sort(num, num + n, cmp);
        int pos1 = -1, pos2 = -1;
        for(int i = 0; i < n - 1; ++i)
        {
            if(lenz[num[i].second] < lenz[num[i + 1].second])
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
    }
    return 0;
}