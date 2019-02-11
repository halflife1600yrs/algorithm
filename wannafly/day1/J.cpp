#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pII;
const int MAXN=1005;
int items[MAXN][MAXN],head[MAXN];

struct _cmp
{
    bool operator()(pII a,pII b) { return items[a.first][a.second]>items[b.first][b.second]; }
};
bool cmp(int a,int b) { return a>b; }

int main()
{
    int n,m;
    while(~scanf("%d %d",&n,&m))
    {
        int a,b;
        for(int i=0;i<m;++i)
            scanf("%d %d",&a,&b),items[b][head[b]++]=a;
        int begin=1e9,end=0;
        for(int i=1;i<=n;++i)
        {
            if(head[i]>end) end=head[i];
            if(head[i]<begin) begin=head[i];
            sort(items[i],items[i]+head[i],cmp);
            // disp(items[i],0,head[i])
        }
        ll ans1=0,ans2,minAns=1e18;
        int left,chosen=0;
        for(int num=end+1;num>=begin>>1;--num)
        { //考虑只有一堆物品，最少是begin/2+1
            left=num-chosen;
            for(int i=1;i<=n;++i)
                while(head[i]>=num)
                    ans1+=items[i][--head[i]],--left,++chosen;
            if(left<0) break;
            priority_queue<pII,vector<pII>,_cmp> q;
            for(int i=1;i<=n;++i)
                if(head[i]>0) q.push(pII(i,head[i]-1));
            ans2=0;
            int pos1,pos2;
            while(left>0)
            {
                if(q.empty())
                {
                    ans2=1e18;
                    break;
                }
                pos1=q.top().first,pos2=q.top().second,q.pop();
                ans2+=items[pos1][pos2],--left;
                if(pos2>0) q.push(pII(pos1,pos2-1));
            }
            if(ans1+ans2<minAns) minAns=ans1+ans2;
        }
        printf("%lld\n",minAns);
    }
    return 0;
}

/*=======================================
added at 2019.Jan28 19:08:53	problem:J
枚举答案
一些细节没抠好wa了很多发
优先队列真的机器好用
=======================================*/