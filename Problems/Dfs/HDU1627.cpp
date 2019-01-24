#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

int L,K;
char ans[80];
char alpha[30]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void printans(int length)
{
    int n=0;
    do
    {
        for(int j=0;j<16;j++)
        {
            for(int i=0;i<4;i++)
            {
                printf("%c",ans[n]);
                if(n==length-1) {printf("\n");return;}
                n++;
            }
            if(j!=15) printf(" ");

        }
        printf("\n");
    }while(1);
}

int check(char a,int length)
{
    int result=0;
    if(ans[length-1]==a) return 0;
    for(int i=length-2;i>=(length-1)/2;i--)
    {
        if(ans[i]==a)
        {
            result=0;
            for(int j=1;j<length-i;j++)
            {
                if(i-j<0||ans[i-j]!=ans[length-j])
                    result=1;
            }
            if(!result) return 0;
        }
    }
    return 1;
}

int dfs(int &rak,int &length)
{
    if(rak==K) return 1;
    for(int i=0;i<L;i++)
    {
        if(check(alpha[i],length))
        {
            ans[length]=alpha[i];
            if(dfs(++rak,++length))
                return 1;
            length--;//rak--;
        }
    }
    return 0;
}
int main()
{
    //if(!freopen("D:\\input.txt","r",stdin)) printf("error1");
    //if(!freopen("D:\\output1.txt","w",stdout)) printf("error2");
    int length,rak;
    do
    {
        scanf("%d%d",&K,&L);
        if(K==0) return 0;
        length=0,rak=0;
        if(dfs(rak,length))
        {
            printans(length);
            printf("%d\n",length);
        }
        else printf("\n%d\n",0);

    }while(1);
    return 0;
}
/*
总结一下做题过程中出现的错误：
第一次是check函数内部判断出现问题
第二次是没有考虑到不能成功的案例，如20 1，所以初始条件的设置还需要谨慎考虑
第三次是没有注意到第一个字母不为A的案例，如4 2，这是由于最后没有判断dfs的返回值
然后发现rak也需要加上引用符号、、、
格式错误，忽略了每16组换行的要求
*/

