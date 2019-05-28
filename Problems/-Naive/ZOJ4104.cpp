#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
const int MAXN=1e5+5;
pii num[MAXN];

bool cmp(const pii& a,const pii& b)
{
    return a.first==b.first?a.second>b.second:a.first>b.first;
}

int main()
{
    int T,n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;++i) scanf("%d",&num[i].first),num[i].second=i;
        sort(num,num+n,cmp);
        int ans=0;
        for(int i=0;i<n-1;++i)
        {
            if(num[i].second<num[i+1].second)
            {
                ans+=1;
                for(int j=i+2;j<n;++j)
                {
                    if(num[j].first==num[i+1].first)
                    {
                        if(num[j].second<num[i].second) continue;
                        else ++ans;
                    }
                    else
                    {
                        ans+=n-j;
                        break;
                    }
                }
                break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*=======================================
added at 2019.Apr27 14:35:41	problem:E
30
11
1 2 8 5 8 6 9 7 8 5 8
13
1 8 8 1 9 1 8 2 9 3 8 8 4
9
9 9 9 9 9 9 9 9 9
5
9 9 9 9 8
5
9 8 9 9 9
事实上只要判断和原序列有几个是一样的就行了
=======================================*/