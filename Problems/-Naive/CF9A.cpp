#include <bits/stdc++.h>

using namespace std;

int gcd(int a,int b)
{
    if(!b) return a;
    return gcd(b,a%b);
}

int main()
{
    int a,b;
    scanf("%d %d",&a,&b);
    int c=6-max(a,b)+1,d=gcd(6,c);
    printf("%d/%d\n",c/d,6/d);
    return 0;
}