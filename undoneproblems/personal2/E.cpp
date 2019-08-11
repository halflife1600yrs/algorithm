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
char str[MAXN];
pii num[26];
bool vis[26];

bool cmp(const pii& a,const pii& b)
{
    return a.first==b.first?a.second<b.second:a.first<b.first;
}

int main()
{
    scanf("%s",str);
    int m,k,l;
    scanf("%d",&k);
    l=strlen(str);
    for(int i=0;i<26;++i) num[i]=pii(0,i);
    for(int i=0;i<l;++i)
        ++num[(int)(str[i]-'a')].first;
    sort(num,num+26,cmp);
    int ans=0;
    for(int i=0;i<26;++i)
    {
        if(num[i].first)
        {
            if(k>=num[i].first) k-=num[i].first,vis[num[i].second]=1;//,debug2(num[i].first,num[i].second);
            else ++ans;
        }
    }
    printf("%d\n",ans);
    for(int i=0;i<l;++i)
    {
        if(!vis[(int)(str[i]-'a')]) printf("%c",str[i]);
    }
    puts("");
    return 0;
}

/*==================================================================
added at 2019-08-06 12:18:18	E
askldfjkashfdasdhgwewjfbhdgfahdjfafj
20
cccddddbba
6
ddcabcdcb
6
==================================================================*/