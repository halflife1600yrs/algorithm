#include <bits/stdc++.h>

using namespace std;

#define DEBUG
#define debug1(x) std::cout << #x " = " << x << std::endl
#define debug2(x, y) std::cout << #x " = " << x << " ," #y " = " << y << std::endl

const int mode = 1e9 + 7;
typedef pair<int, int> pii;
typedef long long ll;
bool state[20], used[20];
int poses[4][4] = { { 1, 2, 4, 8 }, { 3, 6, 12 }, { 5, 10 }, { 7, 14 } };
int top[4] = { 0, 0, 0, 0 };
pii dfs_pos[15];
int num_itv, num_dfs;
pii itv[10];

inline int isDou(int a, int b)
{
    if(a == 2 * b)
        return 1;
    else if(2 * a == b)
        return -1;
    return 0;
}

void read(int x)
{
    int num = 0;
    char c;
    while(num < x)
    {
        c = getchar();
        if(c == '1')
            state[num++] = 1;
        else if(c == '0')
            state[num++] = 0;
    }
    return;
}

void calcu()
{
}

void dfs2(int itv_pos)
{
    if(itv_pos == num_itv)
    {
        calcu();
        return;
    }
    int pos1, pos2, lenz;
    int multi;
    bool ok;
    for(int i = 0; i < num_dfs; ++i)
    {
        pos1 = dfs_pos[i].first, pos2 = dfs_pos[i].second, lenz = itv[itv_pos].first;
        if(used[i] || used[i + 1]) continue;
        multi = isDou(poses[pos1][pos2 + 1], poses[pos1][pos2 + 1]);
        if(!multi) continue;
        ok = 1;
        for(int j = 1; j < lenz && j + pos2 < top[pos1]; ++j)
            if(!used[i])
                if(isDou(poses[pos1][j], poses[pos1][j - 1]) != multi)
                {
                    ok = 0;
                    break;
                }
        if(ok) dfs(itv_pos + 1);
    }
    return;
}

void dfs(int x)
{
    if(x == 4)
    {
        dfs2(0);
        return;
    }
    do
    {
        dfs(x + 1);
    } while(next_permutation(&poses[x][0], &poses[x][top[x]]));
}

ll inv(int x)
{
    ll base = x, ans = 1, up = mode - 2;
    while(up)
    {
        if(up & 1) ans = ans * base % mode;
        base = base * base % mode;
        up >>= 1;
    }
    return ans;
}

int main()
{
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
    int n;
    scanf("%d", &n);
    num_dfs = 0;
    for(int i = 0; i < 4; ++i)
    {
        if(poses[i][0] <= n)
        {
            dfs_pos[num_dfs++] = pii(i, top[i]);
            // debug2(i, top[i]);
            top[i]++;
        }
        for(int j = 1; j < 4; ++j)
            if(poses[i][0] << j <= n)
            {
                dfs_pos[num_dfs++] = pii(i, top[i]);
                // debug2(i, top[i]);
                top[i]++;
            }
    }
    // debug2(top[0], top[1]);
    // debug2(top[2], top[3]);
    read(n - 1);
    num_itv = 0;
    int conti = 0;
    for(int i = 0; i < n - 1; ++i)
    {
        if(conti > floor(log2(n)))
        {
            printf("0\n");
            return 0;
        }
        if(state[i])
            conti++;
        else if(conti)
            itv[num_itv++] = pii(conti + 1, i), conti = 0;
    }
    if(conti) itv[num_itv++] = pii(conti + 1, n - 1);
    for(int i = 0; i < num_itv; ++i) printf("%d(%d) ", itv[i].first, itv[i].second);
    dfs(0);
    return 0;
}