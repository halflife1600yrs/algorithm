### 线性基（插入，求最值，第k大，交并）

```c++
typedef long long ll;
const int L=64;

template<int L>
struct linearbasis
{
    bitset<L> b[L];
    bool independent; // 判断是否线性独立

    linearbasis():independent(1) { memset(b,0,sizeof(b)); }

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
            if(b[i][i]&&x[i])
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

//==================求第k大相关========================
bitset<L> tmp[L];
int cnt;
bool ind;

int rebuild(linearbasis<L> l_b)
{ // 转为对角阵并进行紧凑
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
// 答案是所有第i大的线性基异或(已经转为对角阵),i满足k的第i位为1
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
//=========================================================

void merge(const linearbasis<L>& x,const linearbasis<L>& y,linearbasis<L>& z)
{ // z可以与x相同但不能与y相同
    z=x;
    for(int i=L-1;i>=0;--i)
        if(y.b[i][i]) z.insert(y.b[i]);
}
// 线性基的交,不能直接把x里能被y表示的作为答案,考虑{1100,0011}{1010,0101}
// 它们的交应该是1111
void intersect(const linearbasis<L>& x,const linearbasis<L>& y,linearbasis<L>& z)
{
    z=linearbasis<L>();
    linearbasis<L> c=y,d=y;
    for(int i=0;i<L;++i)
    {
        bitset<L> a=x.b[i];
        if(a.none()) continue;
        int j=i;
        bitset<L> t=0;
        for(;j>=0;--j)
            if(a[j])
                if(c.b[j][j])
                    a^=c.b[j],t^=d.b[j];
                else break;
        if(a.none()) z.b[i]=t;
        else c.b[j]=a,d.b[j]=t;
    }
}
```

### 食用注意

1. 求k大需要先rebuild一遍然后存到一个数组里面，以支持多次查询

### 前缀线性基（HDU6579）

```c++
struct linearbasis
{
    int b[L], pos[L];

    linearbasis& operator=(const linearbasis& x)
    {
        for(int i = 0; i < L; ++i)
            b[i] = x.b[i], pos[i] = x.pos[i];
        return *this;
    }

    void insert(int x, int p)
    { // 优先保存出现晚的基，如{1000}插入1001后变为{1001，0001}
        for(int i = L - 1; i >= 0; --i)
            if(x & (1 << i))
                if(b[i])
                {
                    if(pos[i] > p)
                        x ^= b[i];
                    else
                    {
                        b[i] ^= x;
                        swap(b[i], x);
                        swap(pos[i], p);
                    }
                } else
                {
                    b[i] = x;
                    pos[i] = p;
                    break;
                }
    }

    int query_max(int l)
    { // 查找能被位置大于等于l的表示的最大值
        int ans = 0;
        for(int i = L - 1; i >= 0; --i)
            if(!(ans & (1 << i)) && b[i] && pos[i] >= l)
                ans ^= b[i];
        return ans;
    }
};
```

