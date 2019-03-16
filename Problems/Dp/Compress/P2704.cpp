#include <bits/stdc++.h>

using namespace std;

const int MAXSTATE=1<<10;
int plat[105];
int dp[2][70][70];
int num[MAXSTATE];

struct Quee
{
    int data[MAXSTATE],top;
    void add(int x) { data[top++]=x; }
    int& operator[](int x) { return data[x]; }
} able;

char read()
{
    char c;
    while(c=getchar())
    {
        if(c==' '||c=='\n') continue;
        if(c=='P'||c=='H') return c;
    }
    return -1;
}

void init(int m)
{
    for(int i=able.top=0;i<(1<<m);++i)
    {
        num[i]=0;
        if(!(i&(i<<1))&&!(i&(i<<2))) able.add(i);
        else continue;
        for(int j=0;j<m;++j)
            if(i&(1<<j)) num[i]++;
    }
    for(int i=0,state;i<able.top;++i)
    {
        state=able[i];
        for(int j=0,state1;j<able.top;++j)
        {
            state1=able[j];
            if((state&plat[1])||(state1&plat[0])||(state&state1)) continue;
            dp[1][i][j]=num[state]+num[state1];
        }
    }
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    for(int i=0,state;i<n;++i)
    {
        state=0;
        for(int j=0;j<m;++j)
        {
            state<<=1;
            if(read()=='H') state+=1;
        }
        plat[i]=state;
    }
    init(m);
    int pos,last;
    for(int layer=2;layer<n;++layer)
    {
        pos=layer&1,last=(layer-1)&1;
        for(int i=0,state;i<able.top;++i)
        {
            state=able[i];
            if(state&plat[layer]) continue;
            for(int j=0,state1;j<able.top;++j)
            {
                state1=able[j];
                if(state1&state) continue;
                for(int k=0,state2,ans;k<able.top;++k)
                {
                    state2=able[k];
                    if(!dp[last][j][k]||(state2&state)) continue;
                    ans=dp[last][j][k]+num[state];
                    if(ans>dp[pos][i][j]) dp[pos][i][j]=ans;
                }
            }
        }
    }
    int maxi=0;
    for(int i=0;i<able.top;++i)
        for(int j=0;j<able.top;++j)
            if(dp[(n-1)&1][i][j]>maxi) maxi=dp[(n-1)&1][i][j];
    printf("%d\n",maxi);
    return 0;
}

/*=======================================
added at 2019.Mar07 16:34:00	problem:P2704
写错了一个小地方查了很久才查出来
第一遍做的时候只用了一维数组
=======================================*/