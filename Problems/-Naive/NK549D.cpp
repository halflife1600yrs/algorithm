#include <bits/stdc++.h>

using namespace std;

typedef unsigned int ui;
const int MAXN=5e6+5;
int digit[32];
bool num[MAXN][32];

ui read()
{
    ui ans=0;
    char c;
    bool get=0;
    while(c=getchar())
    {
        if('0'<=c&&c<='9') ans*=10,ans+=c-'0',get=1;
        else if(get) break;
        else continue;
    }
    return ans;
}

int main()
{
    int n;
    scanf("%d",&n);
    memset(digit,0,sizeof(digit));
    int sum=0;
    ui a;
    for(int i=0;i<n;++i)
    {
        a=read();
        sum|=a;
        for(int j=0;j<32;++j)
        {
            if(a&(1<<j)) ++digit[j],num[i][j]=1;
            else num[i][j]=0;
        }
    }
    ui ans=0,tmp;
    for(int i=0;i<n;++i)
    {
        tmp=sum;
        for(int j=0;j<32;++j)
            if(num[i][j]&&digit[j]==1) tmp-=(1<<j);
        if(tmp>ans) ans=tmp;
    }
    printf("%u\n",ans);
    return 0;
}