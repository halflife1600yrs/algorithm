#include <bits/stdc++.h>

#define DEBUG
#define debug1(x) std::cout << #x " = " << x << std::endl
#define debug2(x, y) std::cout << #x " = " << x << " ," #y " = " << y << std::endl
#define disp(arry, fr, to) \
    { \
        std::cout << #arry " : "; \
        for(int _i = fr; _i < to; _i++) std::cout << arry[_i] << " "; \
        std::cout << std::endl; \
    }

using namespace std;

template<int SIZE>
struct nByte_int
{
    typedef long long ll;
    unsigned char byte[SIZE];
    nByte_int<SIZE>() { memset(byte,0,sizeof(byte)); };
    nByte_int<SIZE>(ll x)
    {
        memset(byte,0,SIZE);
        memcpy(byte,&x,sizeof(x));
    }
    nByte_int<SIZE>(const nByte_int<SIZE>& x) { memcpy(byte,x.byte,SIZE); }
    bool sign() { return byte[SIZE-1]&0x80; }
    nByte_int<SIZE> operator-()const
    { //取负号
        nByte_int<SIZE> ans;
        unsigned char r=1;
        for(int i=0;i<SIZE;++i)
        {
            ans.byte[i]=~byte[i];
            if(r==1)
                if(ans.byte[i]==0xFF) ans.byte[i]=0;
                else r=0,ans.byte[i]++; 
        }
        return ans;
    }
    nByte_int<SIZE>& operator<<=(int x)
    {
        if(x<0) return *this>>=-x;
        int m=x>>3,r=x&0x07,i=SIZE;
        // debug2(m,r);
        for(;i>=m;--i)
        {
            byte[i]=byte[i-m]<<r;
            if(i>m&&r) byte[i]+=byte[i-m-1]>>(8-r);
        }
        for(;i>=0;--i) byte[i]=0;
        return *this;
    }
    nByte_int<SIZE> operator<<(int x)const
    {
        nByte_int<SIZE> ans(*this);
        ans<<=x;
        return ans;
    }
    nByte_int<SIZE>& operator>>=(int x)
    {
        if(x<0) return *this<<=-x;
        int m=x>>3,r=x&0x07,i=0;
        bool flag=sign();
        for(;i<=SIZE-m-1;++i)
        {
            byte[i]=byte[i+m]>>r;
            if(r)
                if(i<SIZE-m-1) byte[i]+=byte[i+m+1]<<(8-r);
                else if(flag) byte[i]+=0xFF<<(8-r);
        }
        for(;i<SIZE-1;++i) byte[i]=flag?0xFF:0;
        return *this;
    }
    nByte_int<SIZE> operator>>(int x)const
    {
        nByte_int<SIZE> ans(*this);
        ans>>=x;
        return ans;
    }
    nByte_int<SIZE>& operator+=(const nByte_int<SIZE>& x)
    {
        unsigned int r=0;
        for(int i=0;i<SIZE;++i)
        {
            r+=byte[i]+x.byte[i];
            memcpy(&byte[i],&r,1);
            r>>=8;
        }
        return *this;
    }
    nByte_int<SIZE> operator+(const nByte_int<SIZE>& x)const
    {
        nByte_int<SIZE> ans(*this);
        ans+=x;
        return ans;
    }
    nByte_int<SIZE>& operator-=(const nByte_int<SIZE>& x)
    {
        *this+=-x;
        return *this;
    }
    nByte_int<SIZE> operator-(const nByte_int<SIZE>& x)const
    {
        return *this+(-x);
    }
    nByte_int<SIZE>& operator*=(const nByte_int<SIZE>& x)
    { //booth算法
        nByte_int<SIZE> curSum,_x(-x);
        bool aid=0; //辅助位
        char tail; //末位
        for(int i=0;i<=8*SIZE;++i)
        {
            tail=byte[0]&1;
            if(!aid&&tail==1) curSum+=_x;
            else if(aid==1&&!tail) curSum+=x;
            if(i<8*SIZE)
            {
                aid=tail,tail=curSum.byte[0]&1;
                curSum>>=1,*this>>=1;
                byte[SIZE-1]=tail?byte[SIZE-1]|0x80:byte[SIZE-1]&0x7F;
            }
        }
        return *this;
    }
    nByte_int<SIZE> operator*(const nByte_int<SIZE>& x)const
    {
        nByte_int<SIZE> ans(*this);
        ans*=x;
        return ans;
    }
    nByte_int<SIZE>& operator/=(const nByte_int<SIZE>& x)
    {
        nByte_int<SIZE> num(*this),_x(-x);
        bool flag1=num.sign(),flag2=x.sign();
        for(int i=0;i<8*SIZE-1;++i)
        {
            flag1=num.sign();
            if(flag1==flag2) num+=_x;
            else num+=x;
            flag1=num.sign();
            if(flag1==flag2) byte[0]|=0x01;
            else byte[0]&=0xFE;
            num<<=1,*this<<=1;
        }
        return *this;
    }
    nByte_int<SIZE> operator/(const nByte_int<SIZE>& x)const
    {
        nByte_int<SIZE> ans(*this);
        ans/=x;
        return ans;
    }
    nByte_int<SIZE>& operator++()
    { //前置++
        for(int i=0;i<SIZE;++i)
            if(byte[i]==0xFF) byte[i]=0;
            else
            {
                ++byte[i];
                break;
            }
        return *this;
    }
    nByte_int<SIZE> operator++(int x)
    { //后置++
        nByte_int<SIZE> ans(*this);
        for(int i=0;i<SIZE;++i)
            if(byte[i]==0xFF) byte[i]=0;
            else
            {
                ++byte[i];
                break;
            }
        return ans;
    }
    nByte_int<SIZE>& operator--()
    { //前置--
        for(int i=0;i<SIZE;++i)
            if(!byte[i]) byte[i]=0xFF;
            else
            {
                --byte[i];
                break;
            }
        return *this;
    }
    nByte_int<SIZE> operator--(int x)
    { //后置--
        nByte_int<SIZE> ans(*this);
        for(int i=0;i<SIZE;++i)
            if(!byte[i]) byte[i]=0xFF;
            else
            {
                --byte[i];
                break;
            }
        return ans;
    }
    bool operator==(const nByte_int<SIZE>& x)
    {
        for(int i=0;i<SIZE;++i)
            if(byte[i]!=x.byte[i]) return 0;
        return 1;
    }
    bool operator!=(const nByte_int<SIZE>& x)
    {
        for(int i=0;i<SIZE;++i)
            if(byte[i]!=x.byte[i]) return 1;
        return 0;
    }
    bool operator<=(const nByte_int<SIZE>& x)
    {
        bool flag1=sign(),flag2=x.sign();
        if(flag1>flag2) return 0;
        for(int i=0;i<SIZE;++i)
            if(byte[i]<x.byte[i]) return !flag1; //若flag同为0，则为正数，应返回1
            else if(byte[i]>x.byte[i]) return flag1;
        return 1;
    }
    bool operator<(const nByte_int<SIZE>& x)
    {
        bool flag1=sign(),flag2=x.sign();
        if(flag1>flag2) return 0;
        for(int i=0;i<SIZE;++i)
            if(byte[i]<x.byte[i]) return !flag1;
            else if(byte[i]>x.byte[i]) return flag1;
        return 0;
    }
    bool operator>=(const nByte_int<SIZE>& x)
    {
        bool flag1=sign(),flag2=x.sign();
        if(flag1>flag2) return 0;
        for(int i=0;i<SIZE;++i)
            if(byte[i]<x.byte[i]) return flag1;
            else if(byte[i]>x.byte[i]) return !flag1;
        return 1;
    }
    bool operator>(const nByte_int<SIZE>& x)
    {
        bool flag1=sign(),flag2=x.sign();
        if(flag1>flag2) return 0;
        for(int i=0;i<SIZE;++i)
            if(byte[i]<x.byte[i]) return flag1;
            else if(byte[i]>x.byte[i]) return !flag1;
        return 0;
    }
    void reveal()
    {
        int i=SIZE-1;
        for(;i>=0;--i)
            if(byte[i]) break;
        if(i<0)
        {
            printf("0\n");
            return;
        }
        for(;i>=0;--i)
            printf("%02X ",byte[i]);
        printf("\n");
    }
};

int main()
{
    int x=24;
    nByte_int<8> a(11),b(33609),c(0x8000000000000007);
    // (c>>1).reveal();
    a.reveal();
    // a=a-b;
    return 0; 
}