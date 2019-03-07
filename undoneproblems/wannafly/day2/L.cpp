#include <bits/stdc++.h>

#define MAXN 999999999
#define MAXSIZE 5000
#define DLEN 9
using namespace std;
class BigInt
{
    private:
        int a[500];
        int len;
        bool sign;
        //sign表示符号位的正负~
    protected:
        BigInt add(const BigInt&,const bool)const;
        BigInt subtract(const BigInt&,const bool)const;
         //两个无符号整形的加减法,flag标明结果的符号位~~
    public:
        BigInt() {sign=false;len=1;memset(a,0,sizeof(a));}
        BigInt(const int);
        BigInt(const char*);
        BigInt(const BigInt&);
        BigInt& operator=(const BigInt&);
        friend istream& operator>>(istream&,BigInt&);
        friend ostream& operator<<(ostream&,const BigInt&);
        friend BigInt abs(const BigInt&);
 
        BigInt operator+(const BigInt&)const;
        BigInt operator-(const BigInt&)const;
        BigInt operator*(const BigInt&)const;
        BigInt operator/(const BigInt&)const;
        BigInt operator/(const int&)const;
 
        BigInt operator^(const int&)const;
        int operator%(const int&)const;
        bool operator<(const BigInt&)const;
        bool operator>(const BigInt&)const;
        bool operator<=(const BigInt&)const;
        bool operator>=(const BigInt&)const;
        bool operator==(const BigInt&)const;
 
        inline int size() {return DLEN*(len-1)+to_string(a[len-1]).size();}
};
//对于负数的处理~~~
BigInt::BigInt(const int b)
{
    int c,d=abs(b);
    len=0;
    sign=b<0;
    memset(a,0,sizeof(a));
    while(d>MAXN)
    {
        c=d-(d/(MAXN+1))*(MAXN+1);
        d=d/(MAXN+1);
        a[len++]=c;
    }
    a[len++]=d;
}
BigInt::BigInt(const char *in)
{
    const char *s;
    if(in[0]=='-') s=in+1,sign=true;
    else s=in,sign=false;
    int t,k,index,L,i;
    memset(a,0,sizeof(a));
    L=strlen(s);
    len=L/DLEN;
    if(L%DLEN) len++;
    index=0;
    for(i=L-1;i>=0;i-=DLEN)
    {
        t=0;
        k=i-DLEN+1;
        if(k<0) k=0;
        for(int j=k;j<=i;j++)
            t=t*10+s[j]-'0';
        a[index++]=t;
    }
}
BigInt::BigInt(const BigInt& T):len(T.len),sign(T.sign)
{
    memset(a,0,sizeof(a));
    for(int i=0;i<len;i++)
        a[i]=T.a[i];
}
BigInt& BigInt::operator=(const BigInt& n)
{
    sign=n.sign;
    len=n.len;
    memset(a,0,sizeof(a));
    for(int i=0;i<len;i++)
        a[i]=n.a[i];
    return *this;
}
//MDZZ~不是和字符串转化为BigInt一样么,233333
istream& operator>>(istream& in,BigInt& b)
{
    char ch[MAXSIZE];
    in>>ch;
    b=BigInt(ch);
    return in;
}
ostream& operator<<(ostream& out,const BigInt& b)
{
    out<<(b.sign?"-":"")<<b.a[b.len-1];
    for(int i=b.len-2;i>=0;i--) out<<setw(DLEN)<<setfill('0')<<b.a[i];
    return out;
}
BigInt abs(const BigInt& T)
{
    BigInt t(T);
    t.sign=false;
    return t;
}
BigInt BigInt::add(const BigInt& T,const bool flag)const
{
    BigInt t(*this);
    t.sign=flag;
    int big;
    big=T.len>len?T.len:len;
    for(int i=0;i<big;i++)
    {
        t.a[i]+=T.a[i];
        if(t.a[i]>MAXN)
        {
            t.a[i+1]++;
            t.a[i]-=MAXN+1;
        }
    }
    if(t.a[big]!=0) t.len=big+1;
    else t.len=big;
    return t;
}
BigInt BigInt::subtract(const BigInt& T,const bool flag)const
{
    BigInt t(*this);
    t.sign=flag;
    for(int i=0;i<t.len;i++)
    {
        if(t.a[i]<T.a[i])
        {
            //模拟借位运算过程~
            int j=i+1;
            while(t.a[j]==0) j++;
            t.a[j--]--;
            while(j>i) t.a[j--]+=MAXN;
            t.a[i]+=MAXN+1-T.a[i];
        }
        else t.a[i]-=T.a[i];
    }
    while(t.a[t.len-1]==0&&t.len>1) t.len--;
    return t;
}
BigInt BigInt::operator+(const BigInt& T)const
{
    BigInt ret;
    if(sign^T.sign)
    {
        BigInt t1(*this),t2(T);
        if(abs(t1)<abs(t2)) swap(t1,t2);
        ret=t1.subtract(t2,t1.sign);
        if(ret.a[ret.len-1]==0&&ret.len==1) ret.sign=false;
    }
    else ret=this->add(T,sign);
    return ret;
}
BigInt BigInt::operator-(const BigInt& T)const
{
    BigInt ret;
    if(sign^T.sign) ret=this->add(T,sign);
    else
    {
        BigInt t1(*this),t2(T);
        bool sn;
        if(abs(t1)<abs(t2))
        {
            sn=t1.sign^1;
            swap(t1,t2);
        }
        else sn=t1.sign;
        ret=t1.subtract(t2,sn);
        if(ret.a[ret.len-1]==0&&ret.len==1) ret.sign=false;
    }
    return ret;
}
BigInt BigInt::operator*(const BigInt& T)const
{
    BigInt ret;
    long long up;
    long long temp,temp1;
    for(int i=0;i<len;i++)
    {
        up=0;
        for(int j=0;j<T.len;j++)
        {
            temp=(long long)a[i]*T.a[j]+ret.a[i+j]+up;
            if(temp>MAXN)
            {
                temp1=temp%(MAXN+1);
                up=temp/(MAXN+1);
                ret.a[i+j]=temp1;
            }
            else
            {
                up=0;
                ret.a[i+j]=temp;
            }
        }
        if(up!=0) ret.a[i+T.len]=up;
    }
    ret.sign=sign^T.sign;
    ret.len=len+T.len;
    while(ret.a[ret.len-1]==0&&ret.len>1) ret.len--;
    return ret;
}
BigInt BigInt::operator/(const BigInt& T)const
{
    BigInt r(*this),ret(0);
    while(r>=T)
    {
        BigInt down(1);
        while(r-T*down>=0) down=down*10;
        down=down/10;
        r=r-T*down;
        ret=ret+down;
    }
    ret.sign=sign^T.sign;
    return ret;
}
BigInt BigInt::operator/(const int &b)const
{
    BigInt ret;
    bool sign1=b<0;
    long long down=0;
    for(int i=len-1;i>=0;i--)
    {
        ret.a[i]=(a[i]+down*(MAXN+1))/b;
        down=a[i]+down*(MAXN+1)-(long long)ret.a[i]*b;
    }
    ret.sign=sign^sign1;
    ret.len=len;
    while(ret.a[ret.len-1]==0&&ret.len>1) ret.len--;
    return ret;
}
int BigInt::operator%(const int &b)const
{
    int d=0;
    for(int i=len-1;i>=0;i--)
        d=(((long long)d*(MAXN+1))%b+a[i])%b;
    return sign?-d:d;
}
BigInt BigInt::operator^(const int &n)const
{
    BigInt ret(1),t(*this);
    int m=n;
    while(m)
    {
        if(m&1) ret=ret*t;
        t=t*t;
        m>>=1;
    }
    return ret;
}
bool BigInt::operator<(const BigInt& T)const
{
    if(sign&&!T.sign) return true;
    if(!sign&&T.sign) return false;
    //只有sign相同才能作比较~~
    if(len!=T.len) return sign^(len<T.len);
    for(int ln=len-1;ln>=0;ln--)
        if(a[ln]!=T.a[ln]) return sign^(a[ln]<T.a[ln]);
    return false;
}
bool BigInt::operator>(const BigInt& T)const
{
    return T<*this;
}
bool BigInt::operator<=(const BigInt& T)const
{
    if(*this==T) return true;
    return *this<T;
}
bool BigInt::operator>=(const BigInt& T)const
{
    return T<=*this;
}
bool BigInt::operator==(const BigInt& T)const
{
    if(sign!=T.sign||len!=T.len) return false;
    for(int i=len-1;i>=0;i--)
        if(a[i]!=T.a[i]) return false;
    return true;
}

typedef BigInt ll;

int n,m;
ll sum_k(ll x) { return (x*(x+1)/2); }
ll sum_square(ll x) { return x*(x+1)/2*(2*x+1)/3; }
ll sum_cube(ll x) { return sum_k(x)*sum_k(x); }
ll f1(ll x)
{
    if(x<=0) return 0;
    ll a=m-n+1,b=m-n,c=m+2*n+2;
    ll A=a*b*c,B=4*a*b+a*c+b*c,C=4*a+4*b+c;
    return (A*x+C*sum_square(x)-B*sum_k(x)-4*sum_cube(x))/3;
}
ll f2(ll x)
{
    if(x<=0) return 0;
    ll a=m,b=m+1,c=m+2;
    ll A=a*b*c,B=2*(a*b+b*c+a*c),C=4*(a+b+c);
    return (A*x+C*sum_square(x)-B*sum_k(x)-8*sum_cube(x))/3;
}
ll t1(ll x)
{
    if(x<=0) return 0;
    ll a=n+m+2,b=m-n+1;
    ll A=a*b,B=a+3*b;
    return (A*x+3*sum_square(x)-B*sum_k(x))/2;
}
ll t2(ll x)
{
    if(x<=0) return 0;
    ll A=(m+1)*(m+2)/2,B=2*m+3;
    return A*x+2*sum_square(x)-B*sum_k(x);
}
int main()
{
    // printf("%llu\n",sum_cube(90000));
    for(int T,_=scanf("%d",&T);T--;++_)
    {
        scanf("%d%d",&n,&m);
        // if(m>92000) while(1);
        // debug2(n,m);
        --n,--m;
        ll a=m-n+1,b=m-n,c=m+2*n+2;
        ll ans=a*b*c/6;
        printf("Case #%d: ",_);
        ll maxi=(m-1)/2;
        if(maxi<n)
        {
            ans=ans+f1(m-n-1);
            ans=ans+t1(m-n);
        } else
        {
            ans=ans+f2(maxi)-f2(n)+f1(n);
            ans=ans+t2(m/2)-t2(n)+t1(n);
        }
        printf("%llu\n",ans);
    }
    return 0;
}