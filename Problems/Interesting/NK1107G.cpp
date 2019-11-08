#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e4+5;
char s1[MAXN],s2[MAXN];

int main()
{
    while(~scanf("%s %s",s1,s2))
    {
        int l1=strlen(s1),l2=strlen(s2);
        int i=0,j=0;
        int cnt1[2],cnt2[2];
        bool flag=1;
        while(1)
        {
            cnt1[0]=cnt2[0]=cnt1[1]=cnt2[1]=0;
            while(i<l1&&s1[i]!='c') ++cnt1[s1[i++]=='b'];
            while(j<l2&&s2[j]!='c') ++cnt2[s2[j++]=='b'];
            if((cnt1[0]-cnt2[0])&1)
            {
                flag=0;
                break;
            }
            if((cnt1[1]-cnt2[1])&1)
            {
                flag=0;
                break;
            }
            if(i==l1||j==l2) break;
            ++i,++j;
        }
        if(i!=l1||j!=l2) flag=0;//,debug2(i,j);
        printf(flag?"Yes\n":"No\n");
    }
    return 0;
}

/*==================================================================
added at 2019-10-02 16:49:30	NK1107G
思维题
发现可以任意交换ab的顺序之后就好做了
==================================================================*/