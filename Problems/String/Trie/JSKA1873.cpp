#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int maxn=1e6+7,mode=1e9+7;
int n,k;
char str[maxn];
vector<int> ans;

namespace s
{
    int data[maxn],t;
    void push(int x) { data[t++]=x; }
    int pop() { return data[--t]; }
}

namespace trie
{
    int tree[maxn][26],tot=0,dfn[maxn],tpos[maxn];
    int dfs_num=0;
    void build(int now)
    {
        int l=strlen(str),root=0;
        for(int i=0;i<l;i++)
        {
            int id=str[i]-'a';
            if(!tree[root][id])
            {
                tree[root][id]=++tot;
                memset(tree[tot],0,sizeof(tree[tot]));
                tpos[tot]=0;
            }
            root=tree[root][id];
        }
        tpos[root]=now;
    }

    void bfs(int root)
    {
        s::t=0;
        s::push(root);
        int fr;
        while(s::t)
        {
            fr=s::pop();
            if(tpos[fr])
            {
                dfn[tpos[fr]]=++dfs_num;
                continue;
            }
            for(int i=25;i>=0;--i)
                if(tree[fr][i])
                    s::push(tree[fr][i]);
        }
    }

    void query()
    {
        int l=strlen(str),root=0;
        for(int i=0;i<l;++i)
        {
            int id=str[i]-'a';
            root=tree[root][id];
            if(tpos[root])
            {
                ans.push_back(dfn[tpos[root]]);
                root=0;
                continue;
            }
        }
    }
}

namespace T
{
    int c[maxn];
    int lowbit(int x)
    {
        return x&-x;
    }

    void add(int pos)
    {
        for(;pos<=n;pos+=lowbit(pos))
            c[pos]++;
    }

    int findsum(int pos)
    {
        int ans=0;
        for(;pos;pos-=lowbit(pos))
            ans+=c[pos];
        return ans;
    }
}

ll quick_pow(ll base,ll ind)
{
    ll ans=1;
    while(ind)
    {
        if(ind&1) ans=ans*base%mode;
        (base*=base)%=mode;
        ind>>=1;
    }
    return ans;
}

ll multi[maxn];

void init()
{
    trie::tot=trie::dfs_num=0;
    memset(trie::tree[0],0,sizeof(trie::tree[0]));
    ans=vector<int>();
    fill(T::c,T::c+n,0);
}

int main(){
    for(int i=multi[0]=1;i<maxn;++i)
        multi[i]=multi[i-1]*i%mode;
    while(~scanf("%d %d",&n,&k))
    {
        init();
        for(int i=1;i<=n;i++)
        {
            scanf("%s",str);
            trie::build(i);
        }
        trie::bfs(0);
        scanf("%s",str);
        trie::query();
        ll sum=0;
        for(int i=0;i<ans.size();++i)
        {
            int used=T::findsum(ans[i]-1);
            sum+=(ans[i]-1-used)*(multi[n-i-1]*quick_pow(multi[n-k],mode-2)%mode)%mode;
            sum%=mode;
            T::add(ans[i]);
        }
        printf("%lld\n",(sum+1)%mode);
    }
}

/*==================================================================
added at 2019-08-22 20:17:24 JSKA1873
使用trie统计字符串字典序大小
+
使用树状数组求给定全排列求字典序大小
==================================================================*/