#include <iostream>

using namespace std;

typedef unsigned long long ll;
ll c[35];

int main()
{
    c[0]=1,c[1]=1,c[2]=2;
    for(int i=3;i<35;++i)
        c[i]=(4*i-2)*c[i-1]/(i+1);
    int n;
    while(scanf("%d",&n),n)
        cout<<c[n]<<endl;
    return 0;
}