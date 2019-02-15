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
    void print()
    {
        for(int i=0;i<top;++i) putchar(str[i]);
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
struct strNum
{
    strNode* head;
    int top;
    strNode num[MAXN];
    void init()
    {
        top=1,head=&num[0];
        num[0].build(NULL,0,NULL);
    }
    strNode* add(char* str,int lenz)
    {
        num[top].build(str,lenz,head);
        return head=&num[top++];
    }
    void print()
    {
        for(strNode* i=&num[0];i!=NULL;i=i->next)
            i->print();
        printf("\n");
    }
} number;
typedef strNode::iterator Sit;
typedef vector<strNode*>::iterator Vit;

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

void choose(vector<strNode*>* q)
{
    for(Vit i=q->begin();i+1!=q->end();++i)
    {
        if(test(*i,*(i+1))==1)
        {
            (*i)->dlt();
            q->erase(i);
            return;
        }
    }
    q->back()->dlt(),q->pop_back();
}

int main()
{
    int n;
    for(int T,_=scanf("%d",&T);T--;++_)
    {
        scanf("%d",&n);
        number.init();
        char tmp[11];
        int first=20,second=20,lenz;
        vector<strNode*> q1,q2;
        strNode* cur;
        for(int i=0;i<n;++i)
        {
            scanf("%s",&tmp);
            lenz=strlen(tmp);
            cur=number.add(tmp,lenz);
            if(lenz<=first)
            {
                if(lenz<first)
                {
                    q2.swap(q1),q1=vector<strNode*>();
                    second=first,first=lenz;
                }
                q1.push_back(cur);
            } else if(lenz<=second)
            {
                if(lenz<second)
                {
                    q2=vector<strNode*>();
                    second=lenz;
                }
                q2.push_back(cur);
            }
        }
        printf("Case #%d: ",_);
        if(q1.size()>1)
        {
            choose(&q1);
            choose(&q1);
        } else
        {
            q1.front()->dlt();
            choose(&q2);
        }
        number.print();
    }
    return 0;
}

/*=======================================
added at 2019.Feb14 15:44:08	problem:B
若最短的数有多个，确定a1是否删的方法：
a1,b,a2,c,a3
比较[a1,b]和[b,a2]
1-前者小 说明a1可删
2-前者大 说明a1不可删
3-相同   待定
每次只要找到一种1情况就可以删除，然后重新进行搜索。
=======================================*/