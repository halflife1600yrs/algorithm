#include <bits/stdc++.h>

using namespace std;

const int sz = 1e5 + 5;
char job[sz][12];
bool face[sz];

int main()
{
    int n, m;
    while(~scanf("%d %d", &n, &m))
    {
        for(int i = 0; i < n; i++)
            scanf("%d%s", &face[i], job[i]);
        int pos = 0;
        int dire, count;
        for(int i = 0; i < m; i++)
        {
            scanf("%d%d", &dire, &count);
            if(dire == face[pos])
                pos = (pos - count + n) % n;
            else
                pos = (pos + count) % n;
        }
        printf("%s\n", job[pos]);
    }
    return 0;
}