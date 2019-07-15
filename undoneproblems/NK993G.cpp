#include <bits/stdc++.h>
#define debug1(x) std::cout<<#x"="<<x<<std::endl
#define debug2(x,y) std::cout<<#x"="<<x<<","#y"="<<y<<std::endl
using namespace std;

int pows[25];
int state[(1<<20)+5];
int query[25][10];
char str[50];

int main()
{
    for(int i=0;i<25;++i) pows[i]=1<<i;
    int n,s,q;
    scanf("%d %d %d",&n,&s,&q);
    for(int i=0,a,b,c;i<q;++i)
    {
        scanf("%s",str);
        for(int j=0,en=strlen(str);j<en;j+=4)
        {
            query[i][str[j+2]-'0']=str[j]-'0';
            // debug2(str[j+2]-'0',str[j]-'0');
        }
    }
    int kind,ans=0,tmp,limit[10];
    for(int i=1;i<(1<<q);++i)
    {
        kind=tmp=0;
        memset(limit,0,sizeof(limit));
        for(int j=0;j<q;++j)
        {
            if(i&pows[j])
            {
                for(int k=1;k<=8;++k) limit[k]=max(query[j][k],limit[k]);
                ++kind;
            }
        }
        for(int k=1;k<=8;++k)
        {
            tmp+=limit[k];
            debug2(k,limit[k]);
        }
        if(tmp>n) continue;
        tmp=pow(s,n-tmp);
        debug1(tmp);
        if(kind&1) ans+=tmp;
        else ans-=tmp;
    }
    printf("%d\n",ans);
    return 0;
}