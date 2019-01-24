#include <bits/stdc++.h>
using namespace std;

// #define DEBUG
#define debug1(x) cout<<#x"="<<x<<endl;
#define debug2(x,y) cout<<#x"="<<x<<","#y"="<<y<<endl;

typedef long long ll;
ll loff[1000005];

int gcd(int a,int b)
{
    if(!b) return a;
    return gcd(b, a % b);
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int cas;
    scanf("%d", &cas);
    int a, b, c, d;
    ll v, t;
    while(cas--)
    {
        scanf("%d %d %d %d %lld %lld", &a, &b, &c, &d, &v, &t);
        if(a > c) swap(a, c),swap(b,d);
        ll ans = (t / a + 1) * b + (t / c + 1) * d - 1; //因为0秒时也要拍，同时0秒灯是暗的
        int G = gcd(a, c), lvm = a / G * c, noff = 0;
        if(v<a)
        {
            ll p1 = 0, p2 = c;
            while(p2 <= lvm && p1 <= lvm)
            {
                while(p1<p2)
                    p1 += a, loff[noff++] = p1;
                noff--; //多算的减掉
                if(p2 - p1 + a > v) loff[noff++] = p2;
                if(p1 - p2 > v) loff[noff++] = p1;
                p2 += c;
            }
            #ifdef DEBUG
            for(int i = 0; i < noff;i++)
            {
                cout << loff[i] << " ";
            }
            cout << endl;
            #endif
            ans -= (t / lvm) * noff;
            for(ll low = t / lvm * lvm, i = 0; i < noff;i++)
                if(low + loff[i] <= t)
                {
                    ans--;
                    // cout << low + loff[i] << " ";
                }
                else
                    break;
        }
        printf("%lld\n", ans);
    }
    return 0;
}

/*=======================================
added at 2018年9月16日 14:24:13	problem:qingdaoJ

=======================================*/