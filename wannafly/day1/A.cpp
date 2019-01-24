#include <bits/stdc++.h>
using namespace std;
#define MAX 1000010

vector<int> spe, up, down;

int main()
{
    spe[0] = 1;
    spe[1] = 10;
    int n, r, m, k, s, p, x, y;
    scanf("%d%d%d%d%d", &n, &r, &m, &k, &s);
    for(int i = 0; i < r; i++)
    {
        scanf("%d%d", &x, &y);
        if(y)
            up.push_back(x);
        else
            down.push_back(x);
    }
    for(int i = 0; i < m; i++)
    {
        scanf("%d", &p);
        spe.push_back(p);
    }
    sort(spe.begin(), spe.end());
    sort(up.begin(), up.end());
    sort(down.begin(), down.end());
    int left1, left2, right1, right2, left, right, len;
    left1 = *(upper_bound(up.begin(), up.end(), *(spe.begin())));
    left2 = *(upper_bound(down.begin(), down.end(), *(spe.begin())));
    right1 = *(lower_bound(up.begin(), up.end(), *(spe.begin())));
    right2 = *(lower_bound(down.begin(), down.end(), *(spe.begin())));
    left = min(left1, left2);
    right = max(right1, right2);
    len = right - left;
    int cost = len * 2 + k * 2;
    cout << cost;
}
