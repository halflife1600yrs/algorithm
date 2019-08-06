#include <bits/stdc++.h>
#define DEBUG
#define debug1(x) std::cout << #x " = " << (x) << std::endl
#define debug2(x, y) std::cout << #x " = " << (x) << " ," #y " = " << (y) << std::endl
#define disp(arry, fr, to)                                            \
    {                                                                 \
        std::cout << #arry " : ";                                     \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl;                                       \
    }

using namespace std;

const int MAXN = 1e6 + 5, L = 31;

struct linearbasis
{
    int b[L], pos[L];

    linearbasis& operator=(const linearbasis& x)
    {
        for(int i = 0; i < L; ++i)
            b[i] = x.b[i], pos[i] = x.pos[i];
        return *this;
    }

    void insert(int x, int p)
    {
        for(int i = L - 1; i >= 0; --i)
            if(x & (1 << i))
                if(b[i])
                {
                    if(pos[i] > p)
                        x ^= b[i];
                    else
                    {
                        b[i] ^= x;
                        swap(b[i], x);
                        swap(pos[i], p);
                    }
                } else
                {
                    b[i] = x;
                    pos[i] = p;
                    break;
                }
    }

    int query_max(int l)
    { // 查找能被位置大于等于l的表示的最大值
        int ans = 0;
        for(int i = L - 1; i >= 0; --i)
            if(!(ans & (1 << i)) && b[i] && pos[i] >= l)
                ans ^= b[i];
        return ans;
    }
};

linearbasis val[MAXN];

int main()
{
    int T, n, q;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d %d", &n, &q);
        int op, l, r, x, ans = 0, top = n + 1;
        for(int i = 1; i <= n; ++i)
        {
            scanf("%d", &x);
            val[i] = val[i - 1];
            val[i].insert(x, i);
        }
        for(int i = 0; i < q; ++i)
        {
            scanf("%d", &op);
            if(op)
            {
                scanf("%d", &x);
                x ^= ans;
                val[top] = val[top - 1];
                val[top].insert(x, top);
                ++top, ++n;
            } else
            {
                scanf("%d %d", &l, &r);
                l = (l ^ ans) % n + 1;
                r = (r ^ ans) % n + 1;
                if(l > r) swap(l, r);
                ans = val[r].query_max(l);
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}

/*==================================================================
added at 2019-08-05 10:07:30 b
考虑1000，1001
第0个位置的线性基为1000
第1个位置插入1001,我们要记录尽量靠右的,因此1001代替1000
但是1000^1001表示0001也是前两个的线性基
也就是说对于第j位线性基,用右边的替换左边的之后,要用被替换的值去更新剩下的线性基
==================================================================*/