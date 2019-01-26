#include <bits/stdc++.h>

using namespace std;

#define DEBUG
#define debug1(x) std::cout << #x " = " << x << std::endl
#define debug2(x, y) std::cout << #x " = " << x << " ," #y " = " << y << std::endl
#define disp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }

typedef long long ll;
typedef pair<int,int> pII;
const int MAXN=1005;
pII ctzn[MAXN];
int items[MAXN][MAXN],tmp[2000];

bool cmp(pII a,pII b) { return a.second>b.second; }

int main()
{
    int n,m;
    while(~scanf("%d %d",&n,&m))
    {
        for(int i=1;i<=n;++i)
            ctzn[i]=pII(i,0);
        int a,b;
        for(int i=0;i<m;++i)
        {
            scanf("%d %d",&a,&b);
            items[b][ctzn[b].second++]=a;
        }
        for(int i=1;i<=n;++i)
        {
            sort(items[i],items[i]+ctzn[i].second);
            disp(items[i],0,ctzn[i].second)
        }
        sort(ctzn+1,ctzn+1+n,cmp);
        for(int i=1;i<=n;++i) printf("%d(%d) ",ctzn[i].first,ctzn[i].second);
        printf("\n");
        ll ans1=0,ans2,maxi=0;
        for(int i=ctzn[1].second;i>=ctzn[n].second;--i)
        {
            ans2=0;
            int left=i;
            for(int j=1;j<=n;++j)
            {
                if(ctzn[j].second<i) break;
                while(ctzn[j].second>=i)
                    ans1+=items[ctzn[j].first][ctzn[j].second--],--left;
            }
            if(left<0) break;
            debug2(ans1,left);
        }
        printf("%d\n",maxi);
    }
    return 0;
}