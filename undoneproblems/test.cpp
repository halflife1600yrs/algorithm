#include<bits/stdc++.h>
#define debug1(x) std::cout<<#x"="<<x<<std::endl
#define debug2(x,y) std::cout<<#x"="<<x<<","#y"="<<y<<std::endl
using namespace std;
typedef long long ll;
char a[110],b[110];
int dp[110][110][110];
int main()
{
    int a,b;
    char clear[3];
    scanf("(%d,%d)",&a,&b);
    printf("%d %d\n",a,b);
    // scanf("%3[ \n\r]",clear);
    scanf("(%d,%d)",&a,&b);
    debug2(a,b);
    return 0;    
}
/**
(()(()))
()()
*/