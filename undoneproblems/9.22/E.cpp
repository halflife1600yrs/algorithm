#include <assert.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

int n, r, c;
char str[1001];
int num[1001][1001];
const int yy[4] = { 0, 1, 0, -1 }, xx[4] = { 1, 0, -1, 0 };
void init()
{
    for(int i = 1; i <= r; i++)
        for(int j = 1; j <= c; j++)
            num[i][j] = -1;
    for(int i = 1; i <= r; ++i) num[i][0] = num[i][c + 1] = 2;
    for(int i = 1; i <= c; ++i) num[0][i] = num[r + 1][i] = 2;
}
void read()
{
    int i = 0;
    char c;
    bool get = 0;
    while(c = getchar())
    {
        if(('A' <= c && c <= 'Z') || c == ' ')
            str[i++] = c;
        else
			break;
    }
    str[i++] = 0;
}
int main()
{
    scanf("%d", &n);
    for(int t = 1; t <= n; t++)
    {
        scanf("%d %d", &r, &c);
        getchar();
        read();
        queue<int> Q;
        int l = strlen(str);
        for(int i = 0; i < l; i++)
        {
            int x = str[i] - 'A' + 1;
            if(str[i] < 'A' || str[i] > 'Z') x = 0;
            for(int j = 4; j >= 0; --j)
                Q.push((x & (1 << j)) > 0);
        }
        printf("%d ", t);
        init();
        int x = 1, y = 1, k = 0;
        while(!Q.empty())
        {
            num[y][x] = Q.front(), Q.pop();
            if(Q.empty()) break;
            int flag = 0;
            while(num[y + yy[k]][x + xx[k]] >= 0)
                k = (k + 1) % 4;//,debug1(k);
            y += yy[k], x += xx[k];
        }
        for(int i = 1; i <= r; i++)
            for(int j = 1; j <= c; j++)
                printf(num[i][j] > 0 ? "1" : "0");
        printf("\n");
    }
    return 0;
}