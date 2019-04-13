#include<bits/stdc++.h>
using namespace std;
int main() {
    long long n;
    while(~scanf("%lld",&n))
    {
        if(n&1) printf("1\n");
        else printf("-1\n");
    }
    return 0;
}