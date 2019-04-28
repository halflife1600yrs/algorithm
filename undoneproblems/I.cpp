#include <bits/stdc++.h>

using namespace std;

int read()
{
    int ans=0;
    char c;
    bool get=0;
    while(c=getchar())
    {
        if('0'<=c&&c<='9') ans+=c-'0',get=1;
        else if(get) break;
        else continue;
    }
    return ans%3;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int a=read(),b=read();
        // debug2(a,b);
        if(a==0)
        {
            if(b==0) printf("0\n");
            else if(b==1) printf("1\n");
            else printf("0\n");
        } else if(a==1)
        {
            if(b==0) printf("0\n");
            else if(b==1) printf("1\n");
            else printf("0\n");
        } else
        {
            if(b==0) printf("1\n");
            else if(b==1) printf("0\n");
            else printf("1\n");
        }
    }
    return 0;
}