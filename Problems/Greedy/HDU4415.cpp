#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN=1e5+5;

int main()
{
    for(int T,n,m,_=scanf("%d",&T);T--;++_)
    {
        printf("Case %d: ",_);
        scanf("%d %d",&n,&m);
        vector<int> armed,unarmd;
        int knife=0,mini=0x7f7f7f7f,a,b;
        for(int i=0;i<n;++i)
        {
            scanf("%d %d",&a,&b);
            if(b)
            {
                armed.push_back(a);
                mini=min(mini,a);
                knife+=b;
            } else unarmd.push_back(a);
        }
        if(knife&&mini<=m&&knife+1>=n)
        { // 能杀光
            printf("%d %d\n",n,mini);
            continue;
        }
        int ans=0,cost=0;
        sort(unarmd.begin(),unarmd.end());
        for(int i:unarmd)
        {
            if(cost+i>m) break;
            cost+=i,++ans;
        }
        if(mini>m||!knife)
        { // 不杀有刀的人
            printf("%d %d\n",ans,cost);
            continue;
        }
        int ans2=knife+1,cost2=mini,left=knife+1-armed.size();
        while(left--) unarmd.pop_back();
        sort(armed.begin(),armed.end());
        armed.erase(armed.begin());
        int i=0,j=0;
        while(i<armed.size()&&j<unarmd.size())
        {
            if(unarmd[j]<=armed[i]&&cost2+unarmd[j]<=m)
            {
                cost2+=unarmd[j++],++ans2;
                continue;
            } else if(cost2+armed[i]<=m)
            { // 更小的用自己的刀杀,大的的用拿来的杀
                cost2+=armed[i++],++ans2;
                unarmd.pop_back();
                continue;
            }
            break;
        }
        while(j<unarmd.size())
        {
            if(cost2+unarmd[j]>m) break;
            cost2+=unarmd[j++],++ans2;
        }
        if(ans2==ans) printf("%d %d\n",ans,min(cost,cost2));
        else if(ans2>ans) printf("%d %d\n",ans2,cost2);
        else printf("%d %d\n",ans,cost);
    }
    return 0;
}
/*==================================================================
added at 2019-10-09 21:55:28 HDU4415
没有想到杀不完的时候应该杀所有人里面费用最小的,而不是没武器的人

==================================================================*/