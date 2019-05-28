#include <bits/stdc++.h>
int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        int sg = 0, x;
        for(int i = 0; i < n; i++)
        {
            scanf("%d", &x);
            if(x == 1) continue;
            if(x & 1)
                sg += 2;
            else
                sg += 1;
        }
        if(sg > 0) sg--;
        if(sg&1)
            printf("Alice\n");
        else
            printf("Bob\n");
    }
    return 0;
}

/*=======================================
added at 2018年10月05日 16:03:08	problem:NEWCODER186A
sg函数的思想,但结论是只和数量的奇偶有关
=======================================*/