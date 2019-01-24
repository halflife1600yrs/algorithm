#include <bits/stdc++.h>

const int sz = 6005;
struct inv
{
    int data, fr, to;
} invs[sz];
int main()
{
    int n;
    for(int time, _ = scanf("%d", &time); time--;)
    {
        scanf("%d", &n);
        int first = 0, second = 0, top1 = 0, top2 = 0, l;
        bool maxi = 0;
        for(int i = 0; i < n; ++i)
        {
            scanf("%s", num[i]);
            l = strlen(num[i]);
            if(l > first)
                first = l, maxi = !maxi, top1 = 1, data[maxi][0] = i;
            else if(l == first)
                data[maxi][top1++] = i;
            else if(l > second)
                second = l, top2 = 1, data[!maxi][0] = i;
            else if(l == second)
                data[!maxi][top2++] = i;
        }
        if(top1 >= 2)
        {
            int maxc1 = top1 - 2, maxc2 = top1 - 1;
            for(int i = 1; i < top1 - 1; ++i)
            {
                for(int j = 0; j < first; ++j)
                { //对每位进行比较
                    if(num[data[maxi][i]][j] > num[data[maxi][maxc1]][j])
                    {
                        maxc1 = i;
                        break;
                    } else if(maxc2 < maxc1 || num[data[maxi][i]][j] > num[data[maxi][maxc1]][j])
                    {
                        maxc2 = i;
                        break;
                    }
                }
            }
            if(maxc2 <= maxc1) maxc2 = maxc1 + 1;
            printf("%s%s\n", num[data[maxi][maxc1]], num[data[maxi][maxc2]]);
        } else
        { //有一个最长，要选一个第二长
            int maxc = -1;
            int max_pos = data[maxi][0];
            int pos;
            int i = 0;
            for(; i < top2 && data[!maxi][i] < max_pos; ++i)
            { //位置在最长串之前
                pos = data[!maxi][i];
                for(int j = 0; j < second; ++j)
                {
                    if(maxc < 0)
                    {
                        if(num[pos][j] > num[max_pos][j])
                        {
                            maxc = i;
                            break;
                        }
                        if(j == second - 1 && num[max_pos][second] < num[pos][0])
                        {
                            maxc = i;
                            break;
                        }
                    } else
                    {
                        if(num[pos][j] > num[data[!maxi][maxc]][j])
                        {
                            maxc = i;
                            break;
                        }
                    }
                }
            }
            //最长串在最后面而且最大
            if()
            if(maxc < 0)
            {
                maxc = i++;
                for(; i < top2; ++i)
                {

                }
            }
            printf();
        }
    }
    return 0;
}