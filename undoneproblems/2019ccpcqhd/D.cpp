#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T,n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        while(!(n&1)) n>>=1;
        while(n%5==0) n/=5;
        if(n==1) printf("No\n");
        else printf("Yes\n");
    }
    return 0;
}