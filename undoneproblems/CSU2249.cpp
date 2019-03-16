#include <bits/stdc++.h>

using namespace std;

const int MAXD=2e8+5,MAXN=1e5+5;
int dp[MAXD];
struct Trie
{
    int jump,weight,height;
} frogs[MAXN];

bool cmp(Trie a,Trie b) { return a.weight>b.weight; }

int main()
{
    int n,depth;
    scanf("%d%d",&n,&depth);
    for(int i=0;i<n;++i) scanf("%d %d %d",&frogs[i].jump,&frogs[i].weight,&frogs[i].height);
    sort(frogs,frogs+n,cmp);
    // dp[frogs[0].weight]=0;
    int maxw=frogs[0].weight;
    for(int i=0,w,h;i<n;++i)
    {
        w=frogs[i].weight,h=frogs[i].height;
        for(int j=1;j<w;++j)
        {
            dp[j]=max(dp[j],dp[j+w]+h);
        }
    }
    int ans=0;
    for(int i=n-1;i>=0;--i)
        if(dp[frogs[i].weight]+frogs[i].jump>depth) ++ans;
    printf("%d\n",ans);
    return 0;
}