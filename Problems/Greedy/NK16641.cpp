#include <bits/stdc++.h>

using namespace std;

int work(int s,int m)
{
    int ans=ceil(s/17.0);
    for(int i=1;i<5;++i)
        for(int j=1;j<=(m+4*i)/10;++j)
            ans=min(ans,i+j+(s>60*j?(int)ceil((s-60*j)/17.0):0));
    return ans;
}

int work2(int t,int m)
{
    int ans=t*17;
    for(int i=1;i<=8;++i)
        if(t-i>=(int)ceil((i*10-m)/4.0))
            ans=max(ans,i*60+(t-i-(int)ceil((i*10-m)/4.0))*17);
    return ans;
}

int main()
{
    int m,S,T;
    scanf("%d %d %d",&m,&S,&T);
    int k=m/10;
    if(T<k)
    { // 剩余魔法够,全部闪烁
        if(S<=60*T) printf("Yes\n%d\n",ceil(S/60.0));
        else printf("No\n%d\n",T*60);
        return 0;
    }
    int s=60*k+(T-k)/7*120,t=k+(T-k)/7*7; // 全部用闪烁
    int r=m%10;
    if(s>S)
    {
        s=60*k+(S-60*k)/120*120,t=k+(S-60*k)/120*7;
        printf("Yes\n%d\n",t+work(S-s,r));
    } else
    {
        if(T-k>7) s-=120,t-=7; // 有可能出现9点魔然后少循环一次
        int tmp=work(S-s,r);
        if(t+tmp<=T) printf("Yes\n%d\n",t+tmp);
        else printf("No\n%d\n",s+work2(T-t,r));
    }
    return 0;
}

/*==================================================================
added at 2019-10-09 20:11:56 NK16641
没有考虑到出现剩余8点魔法值然后少循环一次的情况
==================================================================*/