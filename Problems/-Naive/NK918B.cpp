#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n,m,x,y;
    scanf("%d %d %d %d",&n,&m,&x,&y);
    int d1=abs(m-n);
    int d2=abs(n-x)+abs(m-y);
    int d3=abs(n-y)+abs(m-x);
    printf("%d\n",min(d1,min(d2,d3)));
    return 0;
}