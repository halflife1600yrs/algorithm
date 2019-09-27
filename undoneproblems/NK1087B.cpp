#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
const int MAXN=230000;
int num[MAXN],cnt[MAXN];
const int val[8]={1,2,31,62,1847,3694,57257,114514};
ull ans;

ull dfs(int x)
{
    if(x==1) return 1;
    return cnt[x]*1ull*dfs(114514/x);
}

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        scanf("%d",&num[i]);
        for(int j=0;j<8;++j)
            if(num[i]==val[j])
                ++cnt[i];
    }
    ans=0;
    cnt[1]=cnt[1]?1:0;
    return 0;
}