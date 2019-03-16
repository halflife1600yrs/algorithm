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
typedef pair<int,int> Pii;
const int MODE=1e9+7;
int n,m; //n行每行m个
int number[2001];
ll powerM[2001];

template<typename T,int SIZE>
struct Quee
{
    T data[SIZE];
    int top;
    void add(T x) { data[top++]=x; }
    T& operator[](int x) { return data[x]; }
    T tail() { return data[--top]; }
};
Quee<Pii,2001*2001> M;
Quee<int,2005> appear;

bool cmp(Pii a,Pii b) { return a.first<b.first; }

void compress(int x)
{ // 把每行的每个数出现次数压到M里面
    sort(number,number+m);
    int lenz=1;
    for(int i=1;i<m;i++)
    {
        if(number[i-1]==number[i]) lenz++;
        else M.add(Pii(number[i-1],lenz)),lenz=1;
    }
    M.add(Pii(number[m-1],lenz));
}

ll work()
{
    // disp(appear.data,0,appear.top)
    ll ans=0,multi=1;
    for(int i=0,j;i<appear.top;++i)
    {
        j=appear[i];
        ans=(ans+j*multi%MODE*powerM[n-i-1])%MODE;
        multi=multi*(m-j)%MODE;
    }
    // debug1(ans);
    return ans;
}

int main()
{
    scanf("%d %d",&m,&n);
    powerM[0]=1;
    for(int i=1;i<n;++i) powerM[i]=powerM[i-1]*m%MODE;
    for(int i=M.top=0;i<n;++i)
    {
        for(int j=0;j<m;++j) scanf("%d",&number[j]);
        compress(i);
    }
    sort(M.data,M.data+M.top,cmp);
    // for(int j=0;j<M.top;++j) printf("(%d %d) ",M[j].first,M[j].second);
    // printf("\n");
    ll sum=appear.top=0;
    Pii last=M.tail(),cur;
    appear.add(last.second);
    while(M.top)
    { // 从M里面得到每个数在各行出现的次数(答案与顺序无关)
        cur=M.tail();
        if(cur.first!=last.first)
        {
            sum=(sum+last.first*work())%MODE;
            appear.top=0;
        }
        appear.add(cur.second);
        last=cur;
    }
    sum=(sum+last.first*work())%MODE;
    printf("%lld\n",sum);
    return 0;
}

/*=======================================
added at 2019.Mar16 12:35:03	problem:NK393C

=======================================*/