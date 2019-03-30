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
const int MAXN=100005;
int num[MAXN],tmp[MAXN];
ll ans;
int n;
struct Quee
{
    int data[MAXN],top;
    void add(int x) { data[top++]=x; }
    int& operator[](int x) { return data[x]; }
} Q;

void margin1(int fr,int to)
{
    if(to-fr<=1) return;
    int mid=(fr+to)>>1;
    margin1(fr,mid);
    margin1(mid,to);
    int i=fr,j=mid,top=fr;
    while(i<mid&&j<to)
    {
        if(num[i]<=num[j]) tmp[top++]=num[i++],ans+=j-mid;
        else tmp[top++]=num[j++];
    }
    while(i<mid) tmp[top++]=num[i++],ans+=to-mid;
    while(j<to) tmp[top++]=num[j++];
    for(int k=fr;k<to;++k) num[k]=tmp[k];
}

void margin2(int fr,int to)
{
    if(to-fr<=1) return;
    int mid=(fr+to)>>1;
    margin2(fr,mid);
    margin2(mid,to);
    int i=fr,j=mid,top=fr;
    while(i<mid&&j<to)
    {
        if(num[i]>=num[j]) tmp[top++]=num[i++],ans+=j-mid;
        else tmp[top++]=num[j++];
    }
    while(i<mid) tmp[top++]=num[i++],ans+=to-mid;
    while(j<to) tmp[top++]=num[j++];
    for(int k=fr;k<to;++k) num[k]=tmp[k];
}

int work()
{
    ll maxi=0;
    for(int i=0;i<Q.top;++i)
    {
        ans=0;
        margin1(0,Q[i]);
        margin2(Q[i],n);
        if(ans>maxi) maxi=ans;
    }
    return maxi;
}

int main()
{
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
    scanf("%d",&n);
    int maxi=0;
    for(int i=Q.top=0;i<n;++i)
    {
        scanf("%d",&num[i]);
        if(num[i]>maxi) maxi=num[i],Q.top=0;
        if(num[i]>=maxi) Q.add(i);
    }
    printf("%lld\n",work());
    return 0;
}

/*=======================================
added at 2019.Mar27 19:02:51	problem:CSU2286
9
10 4 6 3 15 9 1 1 12
=======================================*/