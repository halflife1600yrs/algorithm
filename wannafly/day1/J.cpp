#include <bits/stdc++.h>

using namespace std;

#define DEBUG
#define debug1(x) std::cout << #x " = " << x << std::endl
#define debug2(x, y) std::cout << #x " = " << x << " ," #y " = " << y << std::endl
#define disp(arry, fr, to) \
    std::cout << #arry " : "; \
    for(int i = fr; i < to; i++) std::cout << arry[i] << " "; \
    std::cout << std::endl;


const int MAXN=1005;
typedef pair<int,int> pII;
pII ctzn[MAXN];
int items[MAXN][MAXN];

bool cmp(pII a,pII b) { return a.second>b.second; }

int main()
{
    int n,m;
    while(~scanf("%d %d",&n,&m))
    {
        for(int i=0;i<n;++i)
            ctzn[i]=pII(i,0);
        int a,b;
        for(int i=0;i<m;++i)
        {
            scanf("%d %d",&a,&b);
            items[b][ctzn[b].second++]=a;
        }
        for(int i=0;i<n;++i)
        {
            sort(items[i],items[i]+ctzn[i].second);
            disp(items[i],0,ctzn[i].second)
        }
        sort(ctzn,ctzn+n,cmp);

    }
    return 0;
}