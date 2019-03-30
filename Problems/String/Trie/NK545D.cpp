#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN=25,MAXSTATE=1e7;
int m[MAXN][MAXN],n,maxi;
struct Tree
{
    int top,root[MAXN];
    int nodes[MAXSTATE][2];
    void init() { top=1; }
    void add(ll x,int pos)
    {
        if(!root[pos]) root[pos]=top++;
        int node=root[pos];
        bool state;
        for(ll i=(1ll<<31);i;i>>=1)
        {
            state=(x&i)>0;
            if(!nodes[node][state]) nodes[node][state]=top++;
            node=nodes[node][state];
        }
    }
    int check(int x,ll pos)
    {
        int node=root[pos],ans=0;
        bool state;
        for(ll i=(1ll<<31);i;i>>=1)
        {
            state=(x&i)>0;
            if(nodes[node][!state]) node=nodes[node][!state],ans|=i;
            else node=nodes[node][state];
        }
        return ans;
    }
} T;

void dfs(int y,int x,int tag,ll val)
{
    if(tag==1&&x+y==n-1)
    {
        T.add(val^m[y][x],x);
        return;
    }
    if(tag==-1&&x+y==n-1)
    {
        maxi=max(T.check(val,x),maxi);
        return;
    }
    val^=m[y][x];
    if(y+tag>=0&&y+tag<n) dfs(y+tag,x,tag,val);
    if(x+tag>=0&&x+tag<n) dfs(y,x+tag,tag,val);
}

int main()
{
    int e;
    scanf("%d %d",&n,&e);
    T.init();
    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            scanf("%d",&m[i][j]);
    if(n==1)
    {
        printf("%d\n",e^m[0][0]);
        return 0;
    }
    maxi=0;
    dfs(0,0,1,e);
    dfs(n-1,n-1,-1,0);
    printf("%d\n",maxi);
    return 0;
}

/*=======================================
added at 2019.Mar30 09:49:20	problem:NK545D
dfs+01字典树
=======================================*/