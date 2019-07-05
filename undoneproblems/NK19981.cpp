#include <bits/stdc++.h>

#define DEBUG
#define debug1(x) std::cout << #x " = " << (x) << std::endl
#define debug2(x, y) std::cout << #x " = " << (x) << " ," #y " = " << (y) << std::endl
#define disp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }

using namespace std;

const int MAXN=105;
int fa[MAXN],sz[MAXN],val[MAXN];
int low[MAXN],dfn[MAXN],dp[2][MAXN*1000];
bool ins[MAXN];
int n,m;

inline int get_fa(int x)
{
    if(low[fa[x]]==dfn[fa[x]]) return fa[x];
    return fa[x]=fa[fa[x]];
}

struct Sta
{
    int data[MAXN],t;
    void add(int x) { data[t++]=x; }
    int top() { return data[t-1]; }
} s;
int dfs_num;
void dfs(int cur)
{
    // debug1(cur);
    low[cur]=dfn[cur]=dfs_num++;
    ins[cur]=1,s.add(cur);
    if(fa[cur])
    {
        if(dfn[fa[cur]]==-1)
        {
            dfs(fa[cur]);
            low[cur]=low[fa[cur]];
        } else if(ins[fa[cur]])
            low[cur]=low[fa[cur]];
    }
    if(low[cur]==dfn[cur])
    {
        // debug1(cur);
        while(s.top()!=cur)
        {
            val[cur]+=val[s.top()];
            sz[cur]+=sz[s.top()];
            ins[s.top()]=0;
            fa[s.top()]=cur;
            --s.t;
        }
        --s.t;
        ins[cur]=0;
        fa[cur]=0;
        // debug2(sz[cur],val[cur]);
    }
}
void tarjan()
{
    dfs_num=s.t=0;
    memset(dfn,-1,sizeof(dfn));
    memset(low,-1,sizeof(low));
    for(int i=1;i<=n;++i)
        if(dfn[i]==-1) dfs(i);
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;++i) scanf("%d",&sz[i]);
    for(int i=1;i<=n;++i) scanf("%d",&val[i]);
    for(int i=1;i<=n;++i) scanf("%d",&fa[i]);
    tarjan();
    bool pos=0;
    int sum=0,maxi=0;
    memset(dp,0x7f,sizeof(dp));
    for(int i=1;i<=n;++i)
    {
        if(sz[i]<=m&&low[i]==dfn[i])
        {
            // debug2(low[i],dfn[i]);
            dp[pos][val[i]]=min(dp[!pos][val[i]],sz[i]);
            for(int j=1;j<=sum;++j)
            {
                if(dp[!pos][j]+sz[i]<=m)
                {
                    dp[pos][j+val[i]]=min(dp[!pos][j+val[i]],dp[!pos][j]+sz[i]);
                    if(j+val[i]>maxi) maxi=j+val[i];
                }
            }
            sum+=val[i];
            pos=!pos;
        }
    }
    printf("%d\n",maxi);
    return 0;
}

/*=======================================
added at 2019.Jun04 21:26:12	problem:NK19981
5 10
1 2 3 4 5
1 2 3 4 5
2 3 4 1 4
=======================================*/