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

typedef long long ll;

int main()
{
    // freopen(".in", "r", stdin);
    // freopen("1.out", "w", stdout);
    int n;
    while(~scanf("%d",&n))
    {
        double p,q;
        scanf("%lf %lf",&p,&q);
        double ans=1+2*p,prefix=0;
        for(int i=n-2;i>=0;--i) // 计算从i走到i+1的期望
        {
            prefix+=(2*(n-1-i)+1)*pow(1-q,n-i-2)*q;
            // debug1(prefix);
            ans+=1-p+p*(prefix+(2*(n-i)+1)*pow(1-q,n-i-1));
            // debug1(1-p+p*(prefix+3*(n-i)*pow(1-q,n-i-1)));
        }
        printf("%.8lf\n",ans);
    }
    return 0;
}

/*==================================================================
added at 2019-08-12 15:32:41 2019ccpc江西省赛I
题意真描述得模棱两可
==================================================================*/