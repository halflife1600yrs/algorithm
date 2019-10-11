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

const int MAXN=2e5+5;
int num[MAXN];

int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        for(int i=0;i<=n;++i) scanf("%d",&num[i]);
        int ans=min(num[n],n);
        for(int i=n-1;i>=0;--i)
        {
            num[i]+=num[i+1];
            ans=max(ans,min(i,num[i]));
        }
        printf("%d\n",ans);
    }
    return 0;
}