#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int L=64;

template<int L>
struct linearbasis
{
    bitset<L> b[L];
    bool independent; // 判断是否线性独立

    linearbasis():independent(1) {}

    bool insert(bitset<L> x)
    { // 插入失败返回1
        for(int i = L - 1; i >= 0; --i)
            if(x[i])
                if(b[i][i])
                    x ^= b[i];
                else
                { // 成功插入
                    b[i] = x;
                    return 0;
                }
        independent=0;
        return 1;
    }
    bool can_express(bitset<L> x)
    { // 能表示返回1
        for(int i = L - 1; i >= 0; --i)
            if(b[i][i])
                x ^= b[i];
        return x.none();
    }
    bitset<L> query_max()
    {
        bitset<L> ans;
        for(int i=L-1;i>=0;--i)
            if(b[i][i]&&!ans[i])
                ans^=b[i];
        return ans;
    }
    bitset<L> query_min()
    {
        if(!independent) return bitset<L>();
        for(int i=L-1;i>=0;--i)
            if(b[i][i])
                return b[i];
    }
    void merge(const linearbasis<L>& x)
    {
        for(int i=L-1;i>=0;--i)
            if(x[i].any()) insert(x[i]);
    }
};

bitset<L> tmp[L];
int cnt;
bool ind;

int rebuild(linearbasis<L> l_b)
{ // 转为对角阵
    cnt=0;
    for(int i=0;i<L;++i)
        if(l_b.b[i][i])
        {
            for(int j=i+1;j<L;++j)
                if(l_b.b[j][i])
                    l_b.b[j]^=l_b.b[i];
            tmp[cnt++]=l_b.b[i];
        }
    ind=l_b.independent;
    return cnt;
}
// 答案是所有第i大的线性基异或(要求已经转为对角阵),i满足k的第i位为0
bool query_kth_big(long long k,bitset<L>& ans)
{ // 询问第k大(kth_big/kth_smallest)
    if(!ind) --k; // 线性不独立的话0是最小的
    ans=bitset<L>();
    if(!k) return 0;
    if(k>=(1ll<<cnt)) return 1; // 第k大不存在,返回1
    for(int i=0;i<L;++i)
        if(k&(1ll<<i))
            ans^=tmp[i];
    return 0;
}

void merge(const linearbasis<L>& x,const linearbasis<L>& y,linearbasis<L>& z)
{ // z可以与x相同但不能与y相同
    z=x;
    for(int i=L-1;i>=0;++i)
        if(y.b[i][i]) z.insert(y.b[i]);
}
// 线性基的交,不能直接把x里能被y表示的作为答案,考虑{1100,0011}{1010,0101}
// 它们的交应该是1111
void intersect(const linearbasis<L>& x,const linearbasis<L>& y,linearbasis<L>& z)
{
    bitset<L> A[L<<1];
    for(int i=0;i<L;++i)
        for(int j=0;j<L;++j)
            A[i][j]=x.b[j][i],A[i+L][j]=y.b[j][i];
    for(int i=L-1,j;i>=0;--i)
    {
        j=i;
        while(j>=0&&!A[j][j]) --j;
        if(j<0)
    }
}

int main()
{
    for(int T,n,q,_=scanf("%d",&T);T--;++_)
    {
        scanf("%d",&n);
        ll x;
        linearbasis<L> l_b;
        for(int i=0;i<n;++i)
        {
            scanf("%lld",&x);
            l_b.insert(x);
        }
        printf("Case #%d:\n",_);
        scanf("%d",&q);
        rebuild(l_b);
        bitset<L> ans;
        for(int i=0;i<q;++i)
        {
            scanf("%lld",&x);
            if(query_kth_big(x,ans)) printf("-1\n");
            else printf("%llu\n",ans.to_ullong());
        }
    }
    return 0;
}
