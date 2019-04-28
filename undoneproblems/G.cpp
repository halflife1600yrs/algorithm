#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T,n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        int k=ceil(n/7.0)*7;
        if(k%4==0) printf("%d\n",k+7);
        else printf("%d\n",k);
    }
    return 0;
}