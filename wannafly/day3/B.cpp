#include <bits/stdc++.h>

using namespace std;

#define DEBUG
#define debug1(x) std::cout << #x " = " << x << std::endl
#define debug2(x, y) std::cout << #x " = " << x << " ," #y " = " << y << std::endl

typedef pair<double, double> Dir;
const double pi = acos(-1);

int main()
{
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
    for(int time, _ = scanf("%d", &time); time--;)
    {
        double x1, x2, y1, y2;
        double x0, y0, r;
        scanf("%lf%lf%lf%lf%lf%lf%lf", &x1, &y1, &x2, &y2, &x0, &y0, &r);
        double tmp1 = x2 - x1, tmp2 = y2 - y1;
        double d1 = sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)),
               d1 = sqrt((x2 - x0) * (x2 - x0) + (y2 - y0) * (y2 - y0));
        double dis = sqrt(tmp1 * tmp1 + tmp2 * tmp2);
        debug2(tmp1, tmp2);
        double d1 = abs(tmp2 * (x0 - x1) - tmp1 * (y0 - y1)) / dis;
        double d2 = abs(tmp1 * (x0 - (x1 + x2) / 2) + tmp2 * (y0 - (y1 + y2) / 2)) / dis;
        double c = dis / 2;
        x1 = -c, x2 = c;
        y1 = 0, y2 = 0;
        x0 = d2, y0 = d1;
        //转换坐标系
        if(abs(x0) < x1 && y0 < r)
        {
            double l1 = sqrt(d1 * d1 - r * r), l2 = sqrt(d2 * d2 - r * r);
            double theta1 = acos(r / d1), theta2 = acos(r / d2);
            double theta3 = y0 ? 2 * atan(c / y0) : pi;
            double l3 = r * (theta3 - theta2 - theta1);
        } else
        {
            double fr = c / 2, to = (d1 + d2) / 2;
            while(1)
            {
                
            }
        }
    }
    return 0;
}