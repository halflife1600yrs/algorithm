#include <bits/stdc++.h>

using namespace std;

const int MAXV=1e6+5;

int sz[MAXV],L[MAXV],R[MAXV],V[MAXV],ans;

bool check(int n1,int n2)
{
    if(V[n1]!=V[n2]||sz[n1]!=sz[n2]) return 0;
    if((L[n1]==-1)^(R[n2]==-1)) return 0;
    else if(~L[n1]&&!check(L[n1],R[n2])) return 0;
    if((R[n1]==-1)^(L[n2]==-1)) return 0;
    else if(~R[n1]&&!check(R[n1],L[n2])) return 0;
    return 1;
}

void dfs(int root)
{
    sz[root]=1;
    if(L[root]>0)
    {
        dfs(L[root]);
        sz[root]+=sz[L[root]];
    }
    if(R[root]>0)
    {
        dfs(R[root]);
        sz[root]+=sz[R[root]];
    }
    if(!(L[root]==-1)^(R[root]==-1))
    {
        if(L[root]==-1) ans=max(ans,1);
        else if(check(L[root],R[root]))
            ans=max(ans,sz[root]);
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",&V[i]);
    for(int i=1;i<=n;++i)
        scanf("%d %d",&L[i],&R[i]);
    dfs(1);
    printf("%d\n",ans);
    return 0;
}

/*==================================================================
added at 2019-08-20 15:25:57 NK21472
dfs
==================================================================*/