#include <bits/stdc++.h>

using namespace std;

char n[10]={},m[10]={};
int dp[20];     //dp[i]表示小于1ei的符合条件的数（包括0）

int getsum(char* num,int lenz,int& ans)  //lenz=1表示在个位，2表示在十位，类推
{
    int flag=0,d=dp[lenz-1];    //标记数字中有没有出现62和4，如果出现了后面就不用算了
    char last=*(num-1);
    if(*num=='4'||(*num=='2'&&last=='6')) flag=1;
    for(char c=*num-1;c>='0';c--)
    {
        if(c=='4'||(c=='2'&&last=='6')) continue;
        if(c=='6') ans-=dp[lenz-2];
        ans+=d;
    }
    return flag;
}

int getitv(char* num)
{	//从数字的第一位开始遍历，比如7560是7000，7500，7560所以是不包含上界的，如果从最后一位开始那么是包含上界的
    int lenz=strlen(num),ans=0;
    for(int i=0;i<=lenz;i++)
        if(num[i]>'0')
            if(getsum(&num[i],lenz-i,ans)) break;
    return ans;
}

int main()
{
    dp[0]=1;dp[1]=9;
    for(int i=2;i<20;i++)
        dp[i]=9*dp[i-1]-dp[i-2];
    while(scanf("%s %s",&n,&m),m[0]!='0')
    {
        int lenz=strlen(m);
        m[lenz-1]++;
        for(int i=lenz-1;m[i]>'9';) //因为getsum计算的是小于m的合格数数目，所以需要算出m+1
        {
            if(i==0&&m[i]>'9')
            {
                m[lenz+1]=0;
                for(int j=lenz;j>1;j--)
                    m[j]=m[j-1];
                m[1]='0',m[0]='1';
                break;
            }
            else
            {
                m[i]='0';
                m[--i]++;
            }
        }
        printf("%d\n",getitv(m)-getitv(n));
    }
    return 0;
}
/*====================================
不要62
关键点在于getsum计算的是小于n的符合规则的数
所以6(5)00是从6(4)xx开始搜
所以对于6(4)00，在计算第二位时做的操作应该是标记flag（只标记flag）
因为从6(4)00开始搜肯定是向小的方向，不会碰到6(4)xx
当某位比4大时才需要在遍历到4时进行continue
而对于(62)xx,在搜索过程中碰到时continue，但是在搜索(6)xxx时并没有减去(62)xx的情况
而且也不能在检测(6)xxx的情况下减去(62)00的情况,因为并不知道6后的数是否大于2
另外字符串数字+1的过程刚开始没有写对、、、、真的菜
====================================*/
