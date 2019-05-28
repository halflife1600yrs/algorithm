#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<double,double> pdd;
const pdd NOSOLUTION=pdd(1e100,1e100);
ll n;

pdd root(int a,int b,int c)
{
    double delta=sqrt(b*b-4*a*c);
    if(delta<0) return NOSOLUTION;
    return pdd((-b-delta)/2/a,(-b+delta)/2/a);
}

int solve(int a,int b)
{

}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld",&n);
        if(n==3) printf("1 1\n");
        else if(n==4) printf("2 2\n");
        else if(n<=12)
        {

        } else
        {
            
        }
    }
    return 0;
}