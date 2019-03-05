#include <bits/stdc++.h>
int main()
{
    int a, b;
    while(~scanf("%d %d", &a, &b))
    {
        int tot = 2 * a * b - a - b;
        int r = a % 2 + b % 2;
        if(r == 0 || std::min(a, b) == 2)
            tot += a + b - 4;
        else if(r >= 1)
            tot += a + b - 2;
        printf("%d\n", tot);
    }
    return 0;
}

/*=======================================
added at 2019.Mar04 19:47:19	problem:D
产生欧拉回路要求图上只有偶结点，然后只要找奇点加边即可
=======================================*/