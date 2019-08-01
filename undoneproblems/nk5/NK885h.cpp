#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e4+5;
typedef pair<int,int> pii;
typedef vector<int>::iterator vit;

vector<int> words[26],head; // 记录每个单词的第几个对应哪个节点
char kind[MAXN];

int top,v,in[MAXN];
struct Edge
{
    int last,to;
    void set(int _last,int _to) { last=_last,to=_to; }
} es[MAXN];

void add(int fr,int to)
{
    es[top].set(head[fr],to);
    head[fr]=top++;
    ++in[to];
}

bool vis[26];

vit addv(char c)
{
    add(v,*words[c].rbegin());
    kind[v]=c;
    words[c].push_back(v++);
    return words[c].end()-1;
}

void topsort()
{
    queue<int> q;
    for(int i=0;i<v;++i)
        if(!in[i]) q.push(i);
    int fr,to;
    while(!q.empty())
    {
        fr=q.front(),q.pop();
        for(int i=head[fr];~i;i=es[i].last)
        {
            
        }
    }
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    head.reserve(1.2*n);
    char cl[5],c1,c2,c;
    int l;
    vit cur,last;
    top=v=0;
    for(int i=0;i<m;++i)
    {
        scanf("%3[ \n\r]",cl);
        scanf("%c%c %d",&c1,&c2,&l);
        scanf("%s",cl);
        cur=words[c1-'a'].end();
        for(int i=0,en=strlen(cl);i<en;++i)
        {
            c=cl[i]-'a';
            if(!vis[c]) cur=addv(c);
            else --cur;
            if(i&&cl[i-1]!=cl[i])
            {
                add(*cur,*last);
            }
            last=cur;
        }
        vis[c1-'a']=vis[c2-'a']=1;
    }
    topsort();

    return 0;
}