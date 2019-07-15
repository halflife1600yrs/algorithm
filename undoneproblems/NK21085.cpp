#include <bits/stdc++.h>
#define debug1(x) std::cout<<#x"="<<x<<std::endl
#define debug2(x,y) std::cout<<#x"="<<x<<","#y"="<<y<<std::endl
using namespace std;

const int MAXN=2e5+5;

struct Node
{
    int v,id,nxt,hash;
    bool operator<(const Node& b) const
    {
        return nxt==b.nxt?id<b.id:nxt<b.nxt; // 优先出nxt最大的
    }
} ns[MAXN];
priority_queue<Node> q;
bool inq[MAXN];

inline bool cmp1(const Node& a,const Node& b)
{
    return a.v==b.v?a.id<b.id:a.v<b.v;
}
inline bool cmp2(const Node& a,const Node& b) { return a.id<b.id; }

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;++i)
    {
        scanf("%d",&ns[i].v);
        ns[i].id=i;
    }
    sort(ns,ns+n,cmp1);
    ns[0].hash=0;
    for(int i=1;i<n;++i)
    {
        if(ns[i].v==ns[i-1].v)
        {
            ns[i].hash=ns[i-1].hash;
            ns[i-1].nxt=ns[i].id;
        } else 
        {
            ns[i].hash=ns[i-1].hash+1;
            ns[i-1].nxt=0x7f7f7f7f;
        }
    }
    // for(int i=0;i<n;++i)
    //     printf("%d %d %d %d\n",ns[i].id,ns[i].v,ns[i].nxt,ns[i].hash);
    sort(ns,ns+n,cmp2);
    int ans=0,count=0;
    for(int i=0;i<n;++i)
    {
        int hash=ns[i].hash;
        // debug2(i,hash);
        if(!inq[hash])
        { // 不在队列中产生缺少
            ++ans;
            if(count==m)
            { // 换出
                while(!inq[q.top().hash]&&!q.empty()) q.pop();
                inq[q.top().hash]=0;
                q.pop();
            } else ++count;
        }
        q.push(ns[i]);
        inq[hash]=1;
    }
    printf("%d\n",ans);
    return 0;
}
/*
10 3 1 3 4 2 5 3 1 4 5 6
 */

/*==================================================================
added at 2019-07-10 21:39:40 NK21085
10 10
1 2 3 1 2 3 1 2 3 1
10 10000
1 2 3 4 5 6  7 8 9 1000000000
==================================================================*/