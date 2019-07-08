#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e5+5;
struct Node
{
    int v,id,nxt,hash;
    bool operator<(const Node& x) const
    {
        return nxt<x.nxt;
    }
} ns[MAXN];

bool inq[MAXN];

priority_queue<Node> q;

inline bool cmp1(const Node& a,const Node& b) { return a.v<b.v; }
inline bool cmp2(const Node& a,const Node& b) { return a.id<b.id; }

int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;++i)
    {
        scanf("%d",&ns[i].v);
        ns[i].id=i;
    }
    sort(ns,ns+n,cmp1);
    ns[0].hash=0;
    for(int i=1;i<n;++i)
    {
        if(ns[i].v==ns[i-1].v) ns[i-1].nxt=ns[i].id,ns[i].hash=ns[i-1].hash;
        else ns[i-1].nxt=0x7f7f7f7f,ns[i].hash=ns[i-1].hash+1;
    }
    sort(ns,ns+n,cmp2);
    // for(int i=0;i<n;++i)
    // {
    //     cout<<ns[i].v<<" "<<ns[i].nxt<<" "<<ns[i].hash<<endl;
    // }
    int ans=0,top,count=0;
    for(int i=0;i<n;++i)
    {
        if(!inq[ns[i].hash])
        {
            ++ans;
            if(count==m)
            {
                // cout<<ns[i].v<<" "<<q.top().v<<endl;
                while(1)
                {
                    top=q.top().hash;
                    q.pop();
                    --count;
                    if(inq[top])
                    {
                        inq[top]=0;
                        break;
                    }
                }
            }
            inq[ns[i].hash]=1;
        }
        q.push(ns[i]);
        ++count;
    }
    printf("%d\n",ans);
    return 0;
}
/*
10 3 1 3 4 2 5 3 1 4 5 6
 */