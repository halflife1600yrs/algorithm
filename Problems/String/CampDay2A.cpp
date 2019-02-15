#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;
const int MAXN=6005;
int nums[MAXN];

struct strNum
{
    char num[50];
    int top;
    void append(int x)
    {
        if(!x) return;
        while(x)
        {
            num[top++]=x%10;
            x/=10;
        }
    }
    void print()
    {
        for(int i=top-1;i>=0;--i) printf("%d",num[i]);
        printf("\n");
    }
};

int lenz_of(int num)
{
    int j=0;
    for(ll i=1;i<=num;++j,i*=10);
    return j;
}

int main()
{
    int n;
    for(int T,_=scanf("%d",&T);T--;++_)
    {
        scanf("%d",&n);
        int maxi=0,pos=-1;
        for(int i=0;i<n;++i)
        {
            scanf("%d",&nums[i]);
            if(nums[i]>maxi) maxi=nums[i],pos=i;
        }
        int pre=0,nxt=0;
        for(int i=0;i<pos;++i)
            if(nums[i]>pre) pre=nums[i];
        for(int i=pos+1;i<n;++i)
            if(nums[i]>nxt) nxt=nums[i];
        printf("Case #%d: ",_);
        int l=lenz_of(maxi),l1=lenz_of(pre),l2=lenz_of(nxt);
        if(l1<l2) printf("%d%d\n",maxi,nxt);
        else if(l1>l2) printf("%d%d\n",pre,maxi);
        else
        {
            strNum a,b;
            a.top=b.top=0;
            a.append(maxi);
            a.append(pre);
            b.append(nxt);
            b.append(maxi);
            for(int i=a.top-1;i>=0;--i)
            {
                if(a.num[i]>b.num[i])
                {
                    a.print();
                    break;
                } else if(a.num[i]<b.num[i])
                {
                    b.print();
                    break;
                } else if(!i)
                    a.print();
            }
        }
    }
    return 0;
}

/*=======================================
added at 2019.Feb11 19:28:44	problem:A
乍一看好像要分很多种情况，其实只要分别找最大数前后就行
=======================================*/