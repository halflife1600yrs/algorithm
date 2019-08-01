#include <bits/stdc++.h>

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
    for(int i=1;i<30;++i) pows[i]=(1<<i)-1;
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
        }
    }
    return 0;
}

/*==================================================================
added at 2019-08-01 21:07:20 2019HDU多校第四场A
一组数中对每个数找到和它按位与最小的数,并且要字典序最小
直接找第一个0就行
==================================================================*/