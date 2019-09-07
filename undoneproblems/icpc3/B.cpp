#include <bits/stdc++.h>
#define DEBUG
#define debug1(x) std::cout << #x " = " << (x) << std::endl
#define debug2(x, y) std::cout << #x " = " << (x) << " ," #y " = " << (y) << std::endl
#define disp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }

using namespace std;

typedef long long ll;
ll fib[75];

int main()
{
    fib[0]=fib[1]=1;
    for(int i=2;i<75;++i)
        fib[i]=fib[i-1]+fib[i-2];
        
    disp(fib,0,75)

    return 0;
}