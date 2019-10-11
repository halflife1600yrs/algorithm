#include <bits/stdc++.h>

using ul = std::uint32_t;
using li = std::int32_t;
using ll = std::int64_t;
using ull = std::uint64_t;
using llf = long double;
using lf = double;
using pulul = std::pair<ul, ul>;
using vpulul = std::vector<pulul>;
using vul = std::vector<ul>;
using vli = std::vector<li>;
using vvli = std::vector<vli>;
using vlf = std::vector<lf>;
using vvlf = std::vector<vlf>;
using vb = std::vector<bool>;
using vull = std::vector<ull>;
using vvull = std::vector<vull>;

const ull base = 9223372036854775783ull;
//const ull base = 998244353;

const ul deg = 5;
const ul n = deg * deg;

vvull eq(n, vull(n + 1, 0));

ull plus(ull a, ull b)
{
	return a + b < base ? a + b : a + b - base;
}

ull minus(ull a, ull b)
{
	return a < b ? a + base - b : a - b;
}

ll mul(ll a, ll b)
{
	ll temp = a * b - ll(llf(a) * llf(b) / llf(base)) * ll(base);
	return temp < 0 ? temp + ll(base) : temp;
}

void exgcd(ll a, ll b, ll& x, ll& y)
{
	if (b) {
		exgcd(b, a % b, y, x);
		y -= x * (a / b);
	} else {
		x = 1;
		y = 0;
	}
}

ull inverse(ull a)
{
	ll x, y;
	exgcd(a, base, x, y);
	return x < 0 ? x + ll(base) : x;
}

ull devide(ull a, ull b)
{
	return mul(a, inverse(b));
}

bool solve(vvull& eq, ul n)
{
	for (ul i = 0; i != n; ++i) {
		for (ul j = i; j != n; ++j) {
			if (eq[j][i]) {
				std::swap(eq[i], eq[j]);
				break;
			}
		}
		if (!eq[i][i]) {
			return false;
		}
		for (ul j = i + 1; j <= n; ++j) {
			eq[i][j] = devide(eq[i][j], eq[i][i]);
		}
		eq[i][i] = 1;
		for (ul j = i + 1; j != n; ++j) {
			for (ul k = i + 1; k <= n; ++k) {
				eq[j][k] = minus(eq[j][k], mul(eq[j][i], eq[i][k]));
			}
			eq[j][i] = 0;
		}
	}
	for (ul i = n - 1; ~i; --i) {
		for (ul j = i + 1; j != n; ++j) {
			eq[i][n] = minus(eq[i][n], mul(eq[j][n], eq[i][j]));
			eq[i][j] = 0;
		}
	}
	return true;
}

ull deal(li L, li R)
{
	ull ret = 0;
	for (li x0 = 0; x0 <= R; ++x0) {
		for (li y0 = std::max(L - x0, 0); y0 <= R - x0; ++y0) {
			for (li x1 = 0; x1 <= R; ++x1) {
				for (li y1 = std::max(L - x1, 0); y1 <= R - x1; ++y1) {
					if (x0 == x1 && y0 == y1) {
						continue;
					}
					li x2 = x0 + y0 - y1;
					li y2 = x1 + y1 - x0;
					if (x2 >= 0 && y2 >= 0 && x2 + y2 >= L && x2 + y2 <= R) {
						++ret;
					}
				}
			}
		}
	}
	return ret / 3;
}

ull big[deg][deg];
ull small[deg][deg];
ull num[deg][deg];

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	for (li L = 0; L <= deg - 1; ++L) for (li R = 2 * L; R <= 2 * L + deg - 1; ++R) {
		ul id = L * deg + R - 2 * L;
		eq[id][n] = deal(L, R);
		eq[id][0] = 1;
		for (ul i = 1; i != n; ++i) {
			if (i % deg) {
				eq[id][i] = mul(eq[id][i - 1], ull(R));
			} else {
				eq[id][i] = mul(eq[id][i - deg], ull(L));
			}
		}
	}
	solve(eq, n);
	for (ul i = 0; i != n; ++i) {
		big[i / deg][i % deg] = eq[i][n];
	}
	for (li L = deg - 1; L <= 2 * deg - 2; ++L) for (li R = L; R <= L + deg - 1; ++R) {
		ul id = (L - deg + 1) * deg + R - L;
		eq[id][n] = deal(L, R);
		eq[id][0] = 1;
		for (ul i = 1; i != n; ++i) {
			if (i % deg) {
				eq[id][i] = mul(eq[id][i - 1], ull(R));
			} else {
				eq[id][i] = mul(eq[id][i - deg], ull(L));
			}
		}
	}
	solve(eq, n);
	for (ul i = 0; i != n; ++i) {
		small[i / deg][i % deg] = eq[i][n];
	}
	ul T;
	std::scanf("%u", &T);
	for (ul Case = 1; Case <= T; ++Case) {
		ull L, R;
		std::scanf("%llu%llu", &L, &R);
		--L;
		--R;
		num[0][0] = 1;
		for (ul j = 1; j != deg; ++j) {
			num[0][j] = mul(num[0][j - 1], R);
		}
		for (ul i = 1; i != deg; ++i) {
			num[i][0] = mul(num[i - 1][0], L);
			for (ul j = 1; j != deg; ++j) {
				num[i][j] = mul(num[i][j - 1], R);
			}
		}
		if (R >= L + L) {
			ull ans = 0;
			for (ul i = 0; i != deg; ++i) {
				for (ul j = 0; j != deg; ++j) {
					ans = plus(ans, mul(num[i][j], big[i][j]));
				}
			}
			std::printf("Case #%u: %llu\n", Case, ans);
		} else {
			ull ans = 0;
			for (ul i = 0; i != deg; ++i) {
				for (ul j = 0; j != deg; ++j) {
					ans = plus(ans, mul(num[i][j], small[i][j]));
				}
			}
			std::printf("Case #%u: %llu\n", Case, ans);
		}
	}
	return 0;
}