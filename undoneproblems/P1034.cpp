#include <bits/stdc++.h>

using namespace std;

struct Point
{
    int id, x, y;
} points[55];

bool cmp1(Point a, Point b) { return a.x < b.x; }
bool cmp2(Point a, Point b) { return a.y < b.y; }

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    int minx = 500, miny = 500, maxx = 0, maxy = 0;
    int a, b;
    for(int i = 0; i < n; ++i)
    {
        scanf("%d %d", &a, &b);
        points[i].x = a, points[i].y = b;
        if(a < minx) minx = a;
        if(a > maxx) maxx = a;
        if(b < minx) minx = b;
        if(b > maxy) maxy = b;
    }
    int best = 0;
    if(k == 1)
        printf("%d\n", (maxx - minx) * (maxy - miny));
    else if(k == 2)
    {
        sort(points, points + n, cmp1);
        int pos = 0, x = points[0].x, ans, mini = 500, maxi = 0;
        while(x < maxx)
        {
            while(points[pos + 1].x == points[pos].x)
            {
                if(points[pos].y < mini) mini = points[pos].y;
                if(points[pos].y > maxi) maxi = points[pos].y;
                ++pos;
            }
            ans = (points[pos].x - points[0].x) * (maxi - mini);
            mini = 500, maxi = 0;
            for(int i = pos + 1; i < n; ++i)
            {
                if(points[i].y < mini) mini = points[i].y;
                if(points[i].y > maxi) maxi = points[i].y;
            }
            ans += (points[n - 1].x - points[pos + 1].x) * (maxi - mini);
            if(ans > best) best = ans;
        }
        pos = 0, ans, mini = 500, maxi = 0;
        int y = points[0].y;
        while(x < maxx)
        {
            while(points[pos + 1].y == points[pos].y)
            {
                if(points[pos].y < mini) mini = points[pos].y;
                if(points[pos].y > maxi) maxi = points[pos].y;
                ++pos;
            }
            ans = (points[pos].x - points[0].x) * (maxi - mini);
            mini = 500, maxi = 0;
            for(int i = pos + 1; i < n; ++i)
            {
                if(points[i].y < mini) mini = points[i].y;
                if(points[i].y > maxi) maxi = points[i].y;
            }
            ans += (points[n - 1].x - points[pos + 1].x) * (maxi - mini);
            if(ans > best) best = ans;
        }
        printf("%d\n", best);
    }else if(k==3)
    {

    }
    return 0;
}