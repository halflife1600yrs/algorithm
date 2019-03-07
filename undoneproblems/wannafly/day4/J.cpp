#include <bits/stdc++.h>

using namespace std;

struct Triad
{
    int x, y, id1, id2;
};
Triad points[505];
int var[505][6];

#define DEBUG
#define debug1(x) std::cout << #x " = " << x << std::endl
#define debug2(x, y) std::cout << #x " = " << x << " ," #y " = " << y << std::endl

// bool cmp(Triad a, Triad b)
// {
//     return a.id < b.id;
// }

int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        for(int i = 0; i < n; ++i)
            scanf("%d %d", &points[i].x, &points[i].y);
        int mark, x, y;
        for(int i = 0; i < n; ++i)
        {
            scanf("%d", &mark);
            points[i].id1 = mark;
            x = points[i].x, y = points[i].y;
            var[mark][0]++, var[mark][1] -= x, var[mark][2] += x * x;
            var[mark][3]++, var[mark][4] -= y, var[mark][5] += y * y;
        }
        for(int i = 0; i < n; ++i)
        {
            scanf("%d", &mark);
            points[i].id2 = mark;
            x = points[i].x, y = points[i].y;
            var[mark][0]++, var[mark][1] -= x, var[mark][2] += x * x;
            var[mark][3]++, var[mark][4] -= y, var[mark][5] += y * y;
        }
        // sort(points, points + n, cmp);


        printf("%.6f\n", ans);
    }
    return 0;
}