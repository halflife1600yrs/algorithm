#include<bits/stdc++.h>
 
using namespace std;
 
const long long Inf = 1e15;
 
int main()
{
    long long a,b,c;
    scanf("%lld %lld %lld",&a,&b,&c);
    long long ans = Inf;
    if( (a+b)%2 == 0 )  ans = max(a,b);
    if( (a+c)%2 == 0 )  ans = min( max(a,c),ans );
    if( (b+c)%2 == 0 )  ans = min( max(b,c),ans );
    if( ans == Inf )  puts("-1");
    else printf("%lld\n",ans);
    return 0;
}