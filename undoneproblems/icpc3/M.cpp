#include<iostream>
#include<algorithm>
#include<map>
#include<set>
using namespace std;


const int maxn = 1e6 + 10;
int dp[maxn][30];
int n, m;
char s[maxn], t[maxn];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)cin >> s[i];
	for (int j = 1; j <= m; ++j)cin >> t[j];
	for (int i = n; i >= 1; --i)
	{
		for (int j = 25; j >= 0; --j)
			dp[i][j] = dp[i + 1][j];
		dp[i][s[i] - 'a'] = i;
	}
	int ans = -1, inx = 0;
	for (int i = 1; i <= m; ++i) {
		for (int j = t[i] - 'a'+1; j <= 25; ++j) {
			if (dp[inx + 1][j]) {
				ans = max(ans, i + n - dp[inx + 1][j]);
			}
		}
		inx = dp[inx+1][t[i] - 'a'];
		//cerr << "debug " << inx << endl;
		if (!inx)break;
	}
	if(inx&&n!=inx)ans = max(ans, m + n - inx);
	cout << ans << endl;
	return 0;
}
