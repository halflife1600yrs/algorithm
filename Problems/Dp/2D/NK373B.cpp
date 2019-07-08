#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN=2*300*666+5;
const int MODE=1e8+7;
struct Quee
{
    int data[MAXN],top;
    void add(int x) { data[top++]=x; }
    int& operator[](int x) { return data[x]; }
} Q[2];
ll dp[2][MAXN][2];
//dp[i][0]表示此时乘-1结果为i的方法数
//dp[i][1]表示此时选择加数结果为i的方法数
//Q用来保存目前可以得到的数
int num[305];
bool vis[MAXN];

inline int vhash(int x) { return x+300*666; }
// 因为数字可能为负，但是最小是300*-666，所以下标统一+300*666
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i) scanf("%d",&num[i]);
    // 初始化
    Q[0].top=Q[1].top=0;
    Q[0].add(0),dp[0][vhash(0)][0]=1;
    if(num[0]!=666)
        Q[0].add(num[0]),dp[0][vhash(num[0])][1]=1;
    //Q和dp都只有两层，一层存当前的一层存上次的，pos保存当前的存在哪一层
    bool pos=1;
    for(int i=1;i<n;++i)
    {
        memset(dp[pos],0,sizeof(dp[pos]));
        memset(vis,0,sizeof(vis)); //vis用来记录当前数有没有入队
        for(int j=Q[pos].top=0,last,kind;j<Q[!pos].top;++j)
        {
            last=Q[!pos][j];
            kind=(dp[!pos][vhash(last)][0]+dp[!pos][vhash(last)][1])%MODE;
            if(last!=-666)
            {
                if(!vis[vhash(last*-1)])
                    Q[pos].add(last*-1),vis[vhash(last*-1)]=1;
                dp[pos][vhash(last*-1)][0]+=kind;
                dp[pos][vhash(last*-1)][0]%=MODE;
            }
            if(last+num[i]!=666)
            {
                if(!vis[vhash(last+num[i])])
                    Q[pos].add(last+num[i]),vis[vhash(last+num[i])]=1;
                dp[pos][vhash(last+num[i])][1]+=kind;
                dp[pos][vhash(last+num[i])][1]%=MODE;
            }
        }
        dp[pos][vhash(666)][0]=dp[pos][vhash(666)][1]=0;
        pos=!pos;
    }
    printf("%lld\n",(dp[!pos][vhash(-666)][0]+dp[!pos][vhash(-666)][1])%MODE);
    return 0;
}