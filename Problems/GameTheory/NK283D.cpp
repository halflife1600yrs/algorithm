#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll game[300], depth;
ll gcd(ll a, ll b)
{
    if(!b) return a;
    game[depth++] = a / b;
    return gcd(b, a % b);
}


int main()
{
    int cas;
    scanf("%d", &cas);
    ll a, b;
    while(cas--)
    {
        scanf("%lld %lld", &a, &b);
        depth = 0;
        if(a > b)
            gcd(a, b);
        else
            gcd(b, a);
        int prefix1 = 0;
        for(int i = 0; i < depth; i++)
        {
            // printf("%d ", game[i]);
            if(game[i] == 1)
                prefix1++;
            else
                break;
        }
        // printf("\n");
        if(prefix1 & 1)
            printf("mmp\n");
        else
            printf("wula\n");
    }
    return 0;
}