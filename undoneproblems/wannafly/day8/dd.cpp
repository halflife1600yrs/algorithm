#include <bits/stdc++.h>

#define DEBUG
#define debug1(x) std::cout << #x " = " << x << std::endl
#define debug2(x, y) std::cout << #x " = " << x << " ," #y " = " << y << std::endl
#define disp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }

using namespace std;

int state[40];
int n;
long long ans;
const int MODE=998244353;

bool check()
{
    // disp(state,0,n)
    int conti[3]={0,0,0};
    for(int i=0;i<n;++i)
    {
        if(state[i]==0)
        {
            if((++conti[0])>=3) {
                // debug1(i);
                return 0;
            }
        } else
        {
            if(conti[0]>2||conti[0]&1==1) {
                // printf("1\n");
                // debug1(conti[0]);
                return 0;
            }
            conti[0]=0;
            ++conti[state[i]];
            if(i<2) continue;
            if(state[i]==1&&state[i-1]==2) {
                // printf("2\n");
                return 0;
            }
            if(state[i]==2&&state[i-1]==1) {
                // printf("3\n");
                return 0;
            }
        }
    }
    if(conti[1]!=conti[2]) return 0;
    return 1;
}

void dfs(int pos)
{
    // debug2(pos,state[pos - 1]);
    if(pos>=n)
    {
        if(check())
        {
            ++ans;
            if(ans==MODE)
            {
                printf("!!!\n");
                ans=0;
            }
            // disp(state,0,n)
        }
        return;
    }
    if(state[pos-1]==1||state[pos-1]==0)
    {
        state[pos]=1;
        dfs(pos+1);
    }
    if(state[pos-1]==2||state[pos-1]==0)
    {
        state[pos]=2;
        dfs(pos+1);
    }
    if(pos==1||(state[pos-2]!=0||state[pos-1]!=0))
    {
        state[pos]=0;
        dfs(pos+1);
    }
    return;
}

int main()
{
    // freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
    // n=6;
    // cout<<check();
    while(~scanf("%d",&n))
    {
        n*=2;
        ans=0;
        memset(state,0,sizeof(state));
        for(int i=0;i<3;++i)
        {
            state[0]=i;
            dfs(1);
        }
        printf("%lld\n",ans);
    }
    return 0;
}

/*=======================================
added at 2019年Jan27日 16:44:47	problem:dd
6 14 38 100 268 726 1974 5404 14852 40972 113388 __

=======================================*/