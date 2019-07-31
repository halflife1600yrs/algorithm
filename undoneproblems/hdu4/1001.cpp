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

typedef long long ll;
int pows[32]={};
int val[MAXN];

inline int get(int y)
{
    if(val[y]) return val[y];
    int x=y, ans=1;
    while(x&1) x>>=1,ans<<=1;
    return val[y]=ans;
}

int main()
{
    // cout<<get(2);
    for(int i=1;i<30;++i) pows[i]=(1<<i)-1;
    // disp(pows,1,30)
    int T,n;
    scanf("%d",&T);
    for(int i=0;i<T;++i)
    {
        scanf("%d",&n);
        int l=1;
        for(;l<31;++l)
            if(pows[l+1]>n) break;
        printf("%c\n",n==pows[l]?'1':'0');
        char c=' ';
        for(int i=2;i<=n;++i)
        {
            if(i==n) c='\n';
            if(get(i)>n) printf("1%c",c);
            else printf("%d%c",get(i),c);
            // else printf("1%c",c);
        }
    }
    return 0;
}