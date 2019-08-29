#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7, MAXN = 3000;

ll quick_pow(ll a, ll b)
{
    ll x = 1;
    a %= MOD;
    while(b)
    {
        if(b & 1) x = x * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return x;
}
namespace linear_seq
{
vector<int> BM(vector<int> x)
{
    vector<int> ls, cur;
    int pn = 0, lf, ld;
    for(int i = 0; i < int(x.size()); ++i)
    {
        ll t = -x[i] % MOD;
        for(int j = 0; j < int(cur.size()); ++j)
            t = (t + x[i - j - 1] * (ll)cur[j]) % MOD;
        if(!t) continue;
        if(!cur.size())
        {
            cur.resize(i + 1);
            lf = i;
            ld = t;
            continue;
        }
        ll k = -t * quick_pow(ld, MOD - 2) % MOD;
        vector<int> c(i - lf - 1);
        c.push_back(-k);
        for(int j = 0; j < int(ls.size()); ++j) c.push_back(ls[j] * k % MOD);
        if(c.size() < cur.size()) c.resize(cur.size());
        for(int j = 0; j < int(cur.size()); ++j)
            c[j] = (c[j] + cur[j]) % MOD;
        if(i - lf + (int)ls.size() >= (int)cur.size())
            ls = cur, lf = i, ld = t;
        cur = c;
    }
    vector<int>& o = cur;
    for(int i = 0; i < int(o.size()); ++i)
        o[i] = (o[i] % MOD + MOD) % MOD;
    return o;
}
int N;
ll a[MAXN], h[MAXN], t_[MAXN], s[MAXN], t[MAXN];
void mull(ll* p, ll* q)
{
    for(int i = 0; i < N + N; ++i) t_[i] = 0;
    for(int i = 0; i < N; ++i)
        if(p[i])
            for(int j = 0; j < N; ++j)
                t_[i + j] = (t_[i + j] + p[i] * q[j]) % MOD;
    for(int i = N + N - 1; i >= N; --i)
        if(t_[i])
            for(int j = N - 1; ~j; --j)
                t_[i - j - 1] = (t_[i - j - 1] + t_[i] * h[j]) % MOD;
    for(int i = 0; i < N; ++i) p[i] = t_[i];
}
ll calc(ll K)
{
    for(int i = N; ~i; --i) s[i] = t[i] = 0;
    s[0] = 1;
    if(N != 1)
        t[1] = 1;
    else
        t[0] = h[0];
    for(; K; mull(t, t), K >>= 1)
        if(K & 1) mull(s, t);
    ll su = 0;
    for(int i = 0; i < N; ++i) su = (su + s[i] * a[i]) % MOD;
    return (su % MOD + MOD) % MOD;
}
int work(vector<int> x, ll n)
{
    if(n < int(x.size())) return x[n];
    vector<int> v = BM(x);
    N = v.size();
    if(!N) return 0;
    for(int i = 0; i < N; ++i) h[i] = v[i], a[i] = x[i];
    return calc(n);
}
}

int main()
{
    vector<int> a;
    a.push_back(1);
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(5);
    a.push_back(8);
    cout<<linear_seq::work(a, 10);
    return 0;
}
/*==================================================================
added at 2019-08-28 14:54:34 BM

==================================================================*/