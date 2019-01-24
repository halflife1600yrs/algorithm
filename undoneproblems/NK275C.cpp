#include <bits/stdc++.h>

using namespace std;

const int sz = 1e5 + 5;
int n, m;
typedef long long ll;
struct Sgtree
{
    int data[sz];
    struct Node
    {
        unsigned int val;
        int mark;
        int digit[32];
        void get_digit(unsigned int x)
        {
            int tmp = 1;
            for(int i = 0; i < 32; i++) digit[i] = x & tmp, tmp <<= 1;
        }
        Node operator+(Node& a)
        {
            Node tmp;
            tmp.val = val + a.val;
            for(int i = 0; i < 32; i++) tmp.digit[i] = digit[i] + a.digit[i];
            return tmp;
        }
    } node[sz << 2];
    void build(int fr = 1, int to = n + 1, int pos = 1)
    {
        if(to == fr + 1)
        {
            node[pos].val = data[sz];
            node[pos].get_digit(data[sz]);
        }
        int mid = (fr + to) / 2;
        build(fr, mid, pos * 2);
        build(mid, to, pos * 2 + 1);
        node[pos] = node[pos * 2] + node[pos * 2 + 1];
    }
    ll sum(int fr, int to, int l = 1, int r = n + 1, int pos = 1)
    {
        if(r <= fr || l >= to) return 0;
        if(l >= fr && r <= to) return pushdown(l, r, pos);
        int mid = (fr + to) / 2;
        return sum(fr, to, l, mid, pos * 2) + sum(fr, to, mid, r, pos * 2 + 1);
    }
    ll pushdown(int l, int r, int pos)
    {
        int tmp = 1, sum = r - l, mark = node[pos].mark;
        node[2 * pos].mark = node[2 * pos + 1].mark = mark;
        ll ans = 0;
        for(int i = 0; i < 32; i++)
        {
            if(mark & tmp)
                ans += (sum - node[pos].digit[i]) * tmp;
            else
                ans += node[pos].digit[i] * tmp;
        }
        node[pos].mark = 0;
        return ans;
    }
} Redball;

int main()
{
    while(~scanf("%d %d", &n, &m))
    {
        for(int i = 1; i <= n; i++) scanf("%d", &Redball.data[i]);
        Redball.build();
        int a, b, c;
        for(int i = 0; i < m; i++)
        {
            scanf("%d %d %d", &a, &b, &c);
            printf("%lld\n",Redball.sum(a, b + 1));
        }
    }
    return 0;
}