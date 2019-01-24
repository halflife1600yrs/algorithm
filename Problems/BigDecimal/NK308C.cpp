#include <bits/stdc++.h>

using namespace std;

char str[105];
int vhash[256] = {}, num[10];
int init[130][10] = {};
int _8xs[125] = { 0, 200, 120, 112,
    320, 32, 312, 232,
    400, 40, 104, 240, 24, 224, 304, 432, 440, 144, 424, 344,
    520, 512, 152, 352, 504, 544, 552,
    600, 160, 16, 216, 360, 136, 632, 336, 640, 64, 416, 624, 264, 464, 560, 56, 256, 536, 456, 616, 664, 656,
    720, 72, 712, 272, 704, 472, 744, 752, 760, 176, 672, 736, 376, 576, 776,
    800, 80, 8, 280, 208, 128, 832, 328, 840, 480, 408, 48, 184, 824, 248, 384, 448, 528, 584, 680, 608, 816, 168, 368, 864, 648, 856, 568, 872, 728, 784, 768, 880, 808, 88, 288, 848, 488, 688, 888,
    920, 912, 192, 392, 904, 944, 952, 592, 960, 96, 296, 936, 496, 696, 792, 976, 928, 984, 968, 896, 992 };

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    for(int i = '0', j = 0; i <= '9'; i++, j++) vhash[i] = j;
    int _8x;
    for(int i = 0; i < 125; i++)
    {
        _8x = _8xs[i];
        init[i][_8x % 10]++;
        init[i][(_8x % 100) / 10]++;
        init[i][_8x / 100]++;
    }
    for(int cas, _ = scanf("%d", &cas); cas--;)
    {
        scanf("%s", str);
        int lenz = strlen(str);
        if(lenz == 1)
        {
            if(str[0] == '8')
                printf("8\n");
            else if(str[0] == '0')
                printf("0\n");
            else
                printf("-1\n");
            continue;
        }
        if(lenz == 2)
        {
            _8x = 0;
            for(int i = lenz - 1, j = 1; i >= 0; i--, j *= 10) _8x += vhash[str[i]] * j;
            int reve = (_8x % 10) * 10 + _8x / 10;
            if(_8x % 8 == 0)
                printf("%d\n", _8x);
            else if(reve % 8 == 0)
                printf("%d\n", reve);
            else
                printf("-1\n");
            continue;
        }
        memset(num, 0, sizeof(num));
        for(int i = 0; i < lenz; i++) num[vhash[str[i]]]++;
        bool able;
        int i;
        for(i = 0; i < 125; i++)
        {
            able = 1;
            for(int j = 0; j < 10; j++)
                if(num[j] < init[i][j])
                {
                    able = 0;
                    break;
                }
            if(able == 1) break;
        }
        if(able)
        {
            _8x = _8xs[i];
            for(int j = 0; j < 10; j++) num[j] -= init[i][j];
            for(int j = 9; j >= 0; j--)
            {
                for(int k = 0; k < num[j]; k++) printf("%d", j);
            }
            printf("%d%d%d\n", _8x / 100, (_8x / 10) % 10, _8x % 10);
        } else
            printf("-1\n");
    }
    return 0;
}

/*=======================================
added at 2018年12月08日 15:45:24	problem:NK308C
比较麻烦需要考虑几个小细节
=======================================*/