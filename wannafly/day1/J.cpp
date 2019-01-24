#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pII;
int item[1000][1000];
pII head[1000];

bool cmp(pII a, pII b) { return a.first > b.first; }

int main()
{
    int n, m;
    while (~scanf("%d %d", &n, &m))
    {
        int a, b;
        memset(head, 0, sizeof(head));
        for (int i = 0; i < m; ++i)
        {
            scanf("%d %d", &a, &b);
            item[a][head[a].first++] = b, head[a].second = i;
        }
        for (int i = 0; i < a; ++i)
            sort(item[i][0], item[i][head[i].first]);
        sort(head, head + n, cmp);
    }
}