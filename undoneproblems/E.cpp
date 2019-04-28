#include <bits/stdc++.h>

#define DEBUG
#define debug1(x) std::cout << #x " = " << (x) << std::endl
#define debug2(x, y) std::cout << #x " = " << (x) << " ," #y " = " << (y) << std::endl
#define disp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }

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
                // debug1(i);
                ans+=1;
                for(int j=i+2;j<n;++j)
                {
                    if(num[j].first==num[i+1].first)
                    {
                        // debug1(j);
                        if(num[j].second<num[i].second) continue;
                        else ++ans;
                    }
                    else
                    {
                        // debug2(j,ans);
                        ans+=n-j;
                        // debug1(ans);
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
=======================================*/