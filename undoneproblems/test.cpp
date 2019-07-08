#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
char a[110],b[110];
int dp[110][110][110];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>a+1;
    cin>>b+1;
    int la=strlen(a+1);
    int lb=strlen(b+1);
    dp[0][0][0]=1;
    for(int i=1; i<=la; i++)
    {
        for(int j=1; j<=lb; j++)
        {
            for(int k=0; k<=la; k++)
            {
                if (!k && a[i] == b[j])
                    dp[i][j][k] |= dp[i - 1][j - 1][k];
                if (a[i] == '(' && k > 0)
                    dp[i][j][k] |= dp[i - 1][j][k - 1];
                if (a[i] == ')')
                    dp[i][j][k] |= dp[i - 1][j][k + 1];
                if(dp[i][j][k])
                    cout<<i<<" "<<j<<" "<<k<<endl;
            }
        }
    }
    if(dp[la][lb][0]) cout<<"Possible"<<endl;
    else cout<<"Impossible"<<endl;
    return 0;
}
/**
(()(()))
()()
*/