#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#define rg register
#define ls 2*k
#define rs 2*k+1
using namespace std;
const int MAXN=5000010;
const int INF=0x3f3f3f3f;
struct node
{
    int next;
    int to;
    int w;
} t[MAXN];
struct Heap
{
    int a[MAXN],dist[MAXN];
    int tail;
    void clear()
    {
        tail=0;
    }
    void Swap(int x,int y)
    {
        swap( a[ x ],a[ y ] );
        swap( dist[ x ],dist[ y ] );
    }
    void insert(rg int id,rg int d)
    {
        a[ ++tail ]=id,dist[ tail ]=d;
        int tmp=tail;
        while( tmp>=2 )
        {
            if( dist[ tmp ]<dist[ tmp/2 ] )
            {
                Swap( tmp,tmp/2 );
                tmp=tmp/2;
            }
            else   break ;
        }
    }
    void update(rg int k)
    {
        int tmp=k;
        if( ls<=tail && dist[ ls ]<=dist[ tmp ] )   tmp=ls;
        if( rs<=tail && dist[ rs ]<=dist[ tmp ] )   tmp=rs;
        if( tmp!=k )
        {
            Swap( k,tmp );
            update( tmp );
        }
    }
    int top( )
    {
        return a[ 1 ];
    }
    void pop( )
    {
        a[ 1 ]=a[ tail ],dist[ 1 ]=dist[ tail-- ];
        if( tail<=1 )   return ;
        update( 1 );
    }
    int empty( )
    {
        return tail;
    }
} q;
bool vis[MAXN];
int head[MAXN],num;
int dis[MAXN];
int n,m,k;
int S,T,ans=INF;
inline int gi()
{
    int x=0,f=1;
    char ch=getchar();
    while (ch<'0' || ch>'9') {if (ch=='-') f=-1;ch=getchar();}
    while (ch>='0' && ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
inline void add(int x,int y,int z)
{
    t[ ++num ].next=head[ x ];
    t[ num ].to=y;
    t[ num ].w=z;
    head[ x ]=num;
}
inline void dijkstra( )
{
    int  x;
    memset( dis,INF,sizeof dis);
    q.clear();
    dis[ S ]=0;
    q.insert( S,0 );
    while( q.empty() )
    {
        x=q.top(),q.pop();
        if( vis[ x ] )   continue ;
        vis[ x ]=1;
        for(rg int i=head[ x ],y; i ;i=t[ i ].next )
        {
            y=t[ i ].to;
            if( dis[ y ]>dis[ x ]+t[ i ].w && !vis[ y ] )
            {
                dis[ y ]=dis[ x ]+t[ i ].w;
                q.insert( y,dis[ y ] );
            }
        }
    }
}
int main()
{
    int x,y,z,t0,t1,t2;
   n=gi(),m=gi(),S=gi(),T=gi(),k=gi();
    for(int i=1; i<=m; i++)
    {
       x=gi(),y=gi(),z=gi();
        for(int j=0;j<=k;j++)
        {
            add( x+n*j,y+n*j,z ),add( y+n*j,x+n*j,z );
            if( j<k )   add( x+n*j,y+n*(j+1),0 ),add( y+n*j,x+n*(j+1),0 );
        }
    }
    dijkstra();
    for(int i=0; i<=k; i++)   ans=min( ans,dis[ T+i*n ] );
    printf("%d\n",ans);
    return 0;
}