#include <bits/stdc++.h>

using namespace std;

template<int L>
struct linearbasis
{
    bitset<L> b[L];
    bool independent; // 判断是否线性独立

    bool insert(bitset<L> x)
    { // 成功插入返回0
        for(int i = L - 1; i >= 0; --i)
            if(x[i])
                if(b[i].none())
                { // 成功插入
                    b[i] = x;
                    return 0;
                } else
                    x ^= b[i];
        independent=0;
        return 1;
    }
    bool can_express(bitset<L> x)
    { // 能表示返回1
        for(int i = L - 1; i >= 0; --i)
            if(b[i].any())
                x ^= b[i];
        return x.none();
    }
    bitset<L> query_max()
    {
        bitset<L> ans;
        for(int i=L-1;i>=0;--i)
            if(b[i].any()&&!ans[i])
                ans^=b[i];
        return ans;
    }
    bitset<L> query_min()
    {
        bitset<L> ans;
        for(int i=L-1;i>=0;--i)
            if(b[i].any()&&ans[i])
                ans^=b[i];
        return ans;
    }
    bitset<L> query_kth_big(long long k)
    { // 询问第k大(kth_big/kth_smallest)
        if(!independent) --k; // 线性不独立的话0是最小的
        for(int i=0;i<L-1;++i)
            if(b[i])
            for(int j=i+1;j<L;++j)
    }
    void merge(const linearbasis<L>& x)
    {
        for(int i=L-1;i>=0;--i)
            if(x[i].any()) insert(x[i]);
    }
};

const int L=32;

void merge(const linearbasis<32>& x,const linearbasis<32>& y,linearbasis<32>& z)
{
    z=x;
    for(int i=L-1;i>=0;++i)
        if(y.b[i].any()) z.insert(y.b[i]);
}

void intersect(const linearbasis<32>& x,const linearbasis<32>& y,linearbasis<32>& z)
{

}

int main()
{

    return 0;
}