#include <bits/stdc++.h>

using namespace std;

const int MAXN=6005;
struct strNode
{
    char str[15];
    int top;
    strNode *next,*last;
    void build(char* _str,int lenz,strNode* _last)
    {
        top=lenz,last=_last,next=NULL;
        if(_last) _last->next=this;
        for(int i=0;i<lenz;++i) str[i]=_str[i];
    }
    void dlt()
    {
        if(last) last->next=next;
        if(next) next->last=last;
    }
    struct iterator
    {
        strNode* cur;
        char* data;
        iterator():cur(NULL),data(NULL) {}
        iterator(strNode* _cur):cur(_cur),data(cur->str) {}
        char& operator*() { return *data; }
        void operator++()
        {
            if(data+1<cur->str+cur->top) ++data;
            else cur=cur->next,data=cur->str;
        }
        bool operator!=(const iterator& x)const
        {
            if(cur==x.cur&&data==x.data) return 0;
            return 1;
        }
    };
};
struct cmp
{
    bool operator()(strNode* &a,strNode* &b)
    { //优先长度后位置，均小的在前
        return a->top==b->top? a>b : a->top>b->top;
    }
};
struct strNum
{
    strNode* head;
    int top;
    strNode num[MAXN];
    void init() { top=0,head=NULL; }
    strNode* add(char* str,int lenz)
    {
        num[top].build(str,lenz,head);
        return head=&num[top++];
    }
} number;
struct strInt
{
    char num[10*MAXN];
    void init() { memset(num,0,sizeof(num)); }
    void add_char(char c,int pos)
    {
        c-=48;
        num[pos]+=c;
        if(num[pos]>=10) num[pos]-=10,++num[pos+1];
    }
    void add(strNum* n)
    {
        int pos=0;
        for(strNode* i=n->head;i!=NULL;i=i->last)
            for(int j=i->top-1;j>=0;--j)
                add_char(i->str[j],pos++);
    }
    void print()
    {
        int i=0;
        for(;i<10*MAXN-1;++i)
            if(num[i]>=10) num[i]-=10,++num[i+1];
        for(;i>=0;--i)
            if(num[i]) break;
        for(;i>=0;--i) printf("%d",num[i]);
        printf("\n");
    }
} Ans;
typedef strNode::iterator Sit;
typedef vector<strNode*>::iterator Vit;
priority_queue<strNode*,vector<strNode*>,cmp> q;
vector<strNode*> v;

int test(strNode* fr,strNode* to)
{
    Sit end(to);
    for(Sit i(fr),j(fr->next);i!=end;++i,++j)
    {
        if(*i<*j) return 1;
        else if(*i>*j) return -1;
    }
    return 0;
}

void choose()
{
    for(Vit i=v.begin();i+1!=v.end();++i)
    {
        if(test(*i,*(i+1))==1)
        {
            (*i)->dlt();
            v.erase(i);
            return;
        }
    }
    v.back()->dlt(),v.pop_back();
}

void calcu()
{
    v.clear();
    v.push_back(q.top()),q.pop();
    int lenz=v.front()->top;
    while(!q.empty()&&q.top()->top==lenz)
        v.push_back(q.top()),q.pop();
    while(!v.empty())
    {
        choose();
        Ans.add(&number);
    }
}

int main()
{
    int n;
    for(int T,_=scanf("%d",&T);T--;++_)
    {
        scanf("%d",&n);
        number.init();
        Ans.init();
        char tmp[11];
        int first=20,second=20,lenz;
        strNode* cur;
        for(int i=0;i<n;++i)
        {
            scanf("%s",&tmp);
            lenz=strlen(tmp);
            q.push(number.add(tmp,lenz));
        }
        number.add(NULL,0);
        printf("Case #%d: ",_);
        while(!q.empty()) calcu();
        Ans.print();
    }
    return 0;
}