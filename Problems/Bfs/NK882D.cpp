#include <bits/stdc++.h>

using namespace std;

const int MAXN=105;
typedef long long ll;
typedef __int128_t i128;
typedef pair<i128,ll> pil;
i128 pows[128],conn[MAXN];
int v,k,weight[MAXN];

struct cmp
{
    bool operator()(const pil& a,const pil& b)
    {
        return a.second>b.second;
    }
};
priority_queue<pil,vector<pil>,cmp> q;

ll bfs()
{
    q.push(pil(0,0));
    i128 s;
    ll sz;
    pil fr;
    while(!q.empty())
    {
        fr=q.top(),q.pop();
        s=fr.first,sz=fr.second;
        if(!(--k)) return sz;
        for(int i=0;i<v;++i)
        {
            if(s&pows[i]) break; // 从前面往后找点放，如果这个点已经放过了那么后面都不放，防止重复
            if((s&conn[i])==s) q.push(pil(s|pows[i],sz+weight[i]));
        }
    }
    return -1;
}

int main()
{
    for(int i=pows[0]=1;i<128;++i) pows[i]=pows[i-1]<<1;
    scanf("%d %d",&v,&k);
    char str[MAXN];
    for(int i=0;i<v;++i) scanf("%d",&weight[i]);
    for(int i=0;i<v;++i)
    {
        scanf("%s",str);
        for(int j=0;j<v;++j)
            if(str[j]=='1') conn[i]|=pows[j];
    }
    printf("%lld\n",bfs());
    return 0;
}

/*==================================================================
added at 2019-07-23 22:53:07	NK882D
优先队列优化的bfs
==================================================================*/