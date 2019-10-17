#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;
const int MAXN=1e5+5;
int fish[MAXN];

int main()
{
    int T,n,k;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&k);
        for(int i=0;i<n;++i) scanf("%d",&fish[i]);
        sort(fish,fish+n);
        priority_queue<int> left;
        queue<int> q;
        ll ans=0;
        int t;
        while(n)
        {
            if(q.empty())
            {
                q.push(fish[--n]);
                ans+=k;
                if(!left.empty()) ans-=left.top(),left.pop();
            }
            t=q.front(),q.pop();
            ans+=t;
            while(t>=k&&n) q.push(fish[--n]),t-=k;
            if(t) left.push(t);
        }
        while(!q.empty()) ans+=q.front(),q.pop();
        printf("%lld\n",ans);
    }
    return 0;
}

/*==================================================================
added at 2019-10-11 16:20:42 HDU6709
优先队列符号写反了,WA了两个小时
==================================================================*/