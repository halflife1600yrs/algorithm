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

const int MAXSTATE=1<<10;
int plat[105];
int dp[3][MAXSTATE];
int num[MAXSTATE];

struct Quee
{
    int data[MAXSTATE],top;
    void add(int x) { data[top++]=x; }
    int& operator[](int x) { return data[x]; }
    void show() { disp(data,0,top); }
} able,Q[3];

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
    able.show();
    for(int i=Q[0].top=0,state;i<able.top;++i)
    {
        state=able[i];
        if(state&plat[0]) continue;
        Q[0].add(state);
        dp[0][state]=num[state];
    }
    Q[0].show();
    for(int i=Q[1].top=0,state;i<able.top;++i)
    {
        state=able[i];
        if(state&plat[0]) continue;
        for(int j=0,state1,k;j<Q[0].top;++j)
        {
            state1=Q[0][j];
            if(state&state1) continue;
            Q[1].add(state);
            k=dp[0][state1]+num[state];
            if(dp[1][state]<k) dp[1][state]=k;
        }
    }
    Q[1].show();
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
        printf("%d\n",state);
    }
    init(m);
    int pos,last1,last2;
    for(int i=2;i<n;++i)
    {
        pos=i%3,last1=(pos+2)%3,last2=(pos+1)%3;
        for(int j=Q[pos].top=0,state;j<able.top;++j)
        {
            state=able[j];
            if(state&plat[i]) continue;
            for(int k=0,state2;k<Q[last2].top;++k)
            {
                state2=Q[last2][k];
                if(able[j]&state2) continue;
                for(int l=0,state1,ans;l<Q[last1].top;++l)
                {
                    state1=Q[last1][l];
                    if(state&state1||state1&state2) continue;
                    Q[pos].add(state);
                    ans=dp[last2][state2]+num[state1]+num[state];
                    if(dp[pos][state]<m) dp[pos][state]=m;
                }
            }
        }
        // Q[pos].show();
    }
    int maxi=0;
    for(int i=0,state;i<able.top;++i)
    {
        state=able[i];
        if(maxi<dp[n-1][state]) maxi=dp[n-1][state];
    }
    printf("%d\n",maxi);
    return 0;
}