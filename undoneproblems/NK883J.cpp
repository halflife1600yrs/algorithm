#include <bits/stdc++.h>
#include <tr1/unordered_map>

using namespace std;

typedef long long ll;
const int MAXN=1e6+5;

struct Node
{
    Node *last,*next;
    int v;
    bool in; // 标记在不在里面
    Node(int _v=0,Node* _last=NULL,Node* _next=NULL,bool _in=1)
        :v(_v),last(_last),next(_next),in(_in) {}
};

namespace L
{
    int length,top;
    Node st,en,ns[MAXN<<1];
    void init()
    {
        st=Node(0,NULL,&en,0);
        en=Node(0,&st,NULL,0);
        top=length=0;
    }

    Node* insert_tail(int v)
    {
        ns[top]=Node(v,en.last,&en);
        en.last=(en.last)->next=&ns[top];
        ++length;
        return ns+(top++);
    }

    void delete_head()
    {
        (st.next)->in=0;
        (st.next)->next->last=&st;
        st.next=(st.next)->next;
        --length;
    }

    void move_to_tail(Node* n)
    {
        n->last->next=n->next;
        n->next->last=n->last;
        n->next=&en;
        n->last=en.last;
        en.last=(en.last)->next=n;
    }
}

unordered_map<ll,Node*> name;

ll val(char* str,int l)
{
    ll ans=0;
    for(int i=0;i<l;++i)
        ans*=10,ans+=str[i]-'0';
    return ans*10+l;
}

int main()
{
    int T,c,q,op,v;
    char s[20];
    scanf("%d",&T);
    while(T--)
    {
        L::init();
        scanf("%d %d",&q,&c);
        name.clear();
        L::length=0;
        for(int i=0;i<q;++i)
        {
            scanf("%d %s %d",&op,s,&v);
            int l=strlen(s);
            Node* pn=name[val(s,l)];
            if(op==0)
            {
                if(pn==NULL||!(pn->in))
                { // 不在cache里
                    printf("%d\n",v);
                    if(L::length==c) L::delete_head();
                    name[val(s,l)]=L::insert_tail(v);
                } else
                { // 在cache里
                    printf("%d\n",pn->v);
                    L::move_to_tail(pn);
                }
            } else 
            {
                if(pn==NULL||!(pn->in)) printf("Invalid\n");
                else
                {
                    if(v==-1)
                    { // 特判一下头尾节点
                        if(pn->last==&L::st) printf("Invalid\n");
                        else printf("%d\n",pn->last->v);
                    } else if(v==1)
                    {
                        if(pn->next==&L::en) printf("Invalid\n");
                        else printf("%d\n",pn->next->v);
                    } else printf("%d\n",pn->v);
                }
            }
        }
    }
    return 0;
}

/*==================================================================
added at 2019-07-25 21:28:54 NK883J
==================================================================*/