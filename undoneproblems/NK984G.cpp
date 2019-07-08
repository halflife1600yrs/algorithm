#include <bits/stdc++.h>
#define debug1(x) std::cout<<#x"="<<x<<std::endl
#define debug2(x,y) std::cout<<#x"="<<x<<","#y"="<<y<<std::endl
using namespace std;

const int MAXN=1e5+5;
bool seive[MAXN];
int prime[10000],pt=0;
typedef long long ll;
int d,n,l;
const ll pows[12]={1,10,100,1000,10000,100000,(ll)1e6,(ll)1e7,(ll)1e8,(ll)1e9,(ll)1e10};
const int limit[6]={0,2,22,222,2222,22222};

inline int lenz(int x)
{
    for(int i=1;i<=10;++i)
        if(x<pows[i]) return i;
    return 10;
}

inline int get_part(int x,int l,int r)
{
    return x%pows[l]/pows[r];
}

void init()
{
    for(int i=2;i<MAXN;++i)
    {
        if(!seive[i]) prime[pt++]=i;
        for(int j=0;j<pt&&i*prime[j]<MAXN;++j)
        {
            seive[i*prime[j]]=1;
            if(i%prime[j]==0) break;
        }
    }
}

int get_aim(int x)
{
    if(x<=prime[pt-1]) return *(lower_bound(prime,prime+pt,x));
    else
    {
        for(int j=x;;++j)
        {
            // debug1(j);
            bool get=1;
            for(int i=0,end=floor(sqrt(j));prime[i]<=end;++i)
            {
                if(j%prime[i]==0)
                {
                    // debug2(j,prime[i]);
                    get=0;
                    break;
                }
            }
            if(get) return j;
        }
    }
}

int pos[5];
int maxi=2e9+12; // 最大是2e9+11

void judge()
{
    int x,p,ans=0;
    for(int i=d;i>0;--i)
    {
        x=get_part(n,pos[i],pos[i-1]);
        p=get_aim(x);
        // printf("%d,%d ",x,p);
        if(lenz(p)!=pos[i]-pos[i-1])
        {
            // printf("\n");
            return; // 比它大的第一个质数长度不同
        }
        ans*=pows[pos[i]-pos[i-1]],ans+=p;
    }
    // printf("%d\n",ans);
    if(ans<maxi) maxi=ans;
}

void dfs(int p,int layer)
{
    pos[layer]=p;
    if(layer==1)
    {
        judge();
        return;
    }
    for(int i=p-1;i>=layer-1;--i)
    {
        pos[layer-1]=i;
        dfs(i,layer-1);
    }
}

int main()
{
    // cout<<lenz(123456789)<<endl;
    // cout<<get_part(123456789,9,0)<<endl;
    // init();
    // for(int i=0;i<100;++i) printf("%d ",prime[i]);
    // printf("\n");
    // get_aim(2e9);
    scanf("%d %d",&d,&n);
    // d=3,n=123456789;
    if(n<limit[d]) printf("%d\n",limit[d]);
    else
    {
        init();
        // debug2(pt,prime[5]);
        for(;;++n)
        {
            l=lenz(n);
            dfs(l,d);
            if(maxi!=2e9+12) break;
        }
        printf("%d\n",maxi);
    }
    return 0;
}

/*==================================================================
added at 2019-07-07 11:09:24 Problem:NK984G
2 152592086
152592087
1 2000000000
2000000011
3 459711936
459711937
5 22229
读错题啦
==================================================================*/