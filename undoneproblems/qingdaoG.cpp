#include <bits/stdc++.h>

using std::cout;
using std::endl;
using std::fill;
using std::min;

#define DEBUG
#define debug1(x) cout << #x " = " << x << endl;
#define debug2(x, y) cout << #x " = " << x << " ," #y " = " << y << endl;

//brickdata保存每块中小于n的个数,itvdata保存i到j块的逆序数
const int sz = 1e5 + 5;
const int BrickLen = 2200, BrickNum = 50; //sz^(2/3) sz^(1/3)
int Lenz, Num, N, tot;
int data[sz], copy[sz];
int low[BrickNum], up[BrickNum];
int BrickData[BrickNum][sz], ItvData[BrickNum][BrickNum];
bool havequery[BrickNum], query[sz];

inline int get_brick(int x) { return x / Lenz; } //标号0开始
inline int get_up(int x)
{
    if(up[x]) return up[x];
    return min((x + 1) * Lenz, N);
}
inline int get_low(int x)
{
    if(low[x]) return low[x];
    return x * Lenz;
}
int temp[sz], count, chip1[2 * BrickLen], chip2[2 * BrickLen];
void Merge(int* array, int first, int mid, int last)
{
    int i = first, j = mid, k = 0;
    while(i < mid && j < last)
    {
        if(array[i] <= array[j])
            temp[k++] = array[i++];
        else
        {
            temp[k++] = array[j++];
            count += mid - i;
        }
    }
    while(i < mid) temp[k++] = array[i++];
    while(j < last) temp[k++] = array[j++];
    for(int s = 0, t = first; t < last; s++, t++)
        array[t] = temp[s];
}

int combine(int* array1, int l1, int* array2, int l2)
{
    int i = 0, j = 0, ans = 0;
    for(int i = 0; i < l1; i++)
        printf("%d ", array1[i]);
    printf("\n");
    for(int i = 0; i < l2; i++)
        printf("%d ", array2[i]);
    printf("\n");
    while(i < l1 && j < l2)
        if(array1[i] > array2[j])
            ans += l1 - i, j++;
        else
            i++;
    return ans;
}

void MergeSort(int* array, int first, int last)
{
    if(last == first + 1) return;
    if(last == first) return;
    int mid = (first + last) / 2;
    MergeSort(array, first, mid);
    MergeSort(array, mid, last);
    Merge(array, first, mid, last);
}

void get_list(int x)
{
    memset(BrickData[x], 0, sizeof(BrickData[x]));
    int low = get_low(x);
    for(int i = 0; i < Lenz; i++)
        BrickData[x][data[low + i]]++;
    for(int i = 1; i <= N; i++)
        BrickData[x][i] += BrickData[x][i - 1];
}

int get_change(int a, int b)
{
    int low = get_low(a), up = get_up(a), ans = 0;
    if(ItvData[a][b] != -1) return ItvData[a][b];
    for(int i = low; i < up; i++)
        ans += BrickData[b][copy[i] - 1]; //因为brickdata里保存的是小于等于的数量
    return ItvData[a][b] = ans;
}

void solve(int mark)
{
    debug1(mark);
    mark--;
    int nbrick = get_brick(mark), low = get_low(nbrick), up = get_up(nbrick);
    int start = low - 1, end = up + 1, top1 = 0, top2 = 0;
    int i = nbrick, j = nbrick;
    int ans1 = 0, ans2 = 0, ans3 = 0, ans4 = 0;
    for(int k = mark; k >= low; k--)
        if(query[k])
        {
            start = k;
            break;
        } else
            chip1[top1++] = data[k];
    if(start<low)
        for(i = nbrick - 1; i >= 0; i--)
            if(havequery[i])
            {
                for(int k = get_up(i) - 1; !query[k]; k--)
                    chip1[top1++] = data[k];
                break;
            }
    for(int k = mark + 1; k < up; k++)
        if(query[k])
        {
            end = k;
            break;
        } else
            chip2[top2++] = data[k];
    if(end>up)
        for(j = nbrick + 1; j < Num; j++)
            if(havequery[j])
            {
                for(int k = get_low(j); !query[k]; k++)
                    chip2[top2++] = data[k];
                break;
            }
    debug2(start, end);
    for(int m = nbrick - 1; m > i; m--) //整块对整块
        for(int n = nbrick + 1; n < j; n++)
            ans1 += get_change(m, n);
    MergeSort(chip1, 0, top1);
    MergeSort(chip2, 0, top2);
    ans2 = combine(chip1, top1, chip2, top2); //不足一块对不足一块
    for(int m = nbrick + 1; m < j; m++)
        for(int n = 0; n < top1; n++)
            ans3 += BrickData[m][chip1[n] - 1];
    for(int m = nbrick - 1; m > i; m--) //m对应前面的逆序数也需要减掉
    {
        ans4 += BrickData[m][N] - BrickData[m][data[mark]];
        for(int n = 0; n < top2; n++)
            ans4 += BrickData[m][N] - BrickData[m][chip2[n]];
    }
    for(int m = 0; m < top1; m++)
        if(chip1[m] > data[mark]) tot--;
    havequery[nbrick] = 1, query[mark] = 1;
    debug2(ans1, ans2);
    debug2(ans3, ans4);
    tot -= ans1 + ans2 + ans3 + ans4;
    debug1(tot);
}

int main()
{
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
    int cas;
    scanf("%d", &cas);
    while(cas--)
    {
        scanf("%d", &N);
        Num = pow(N, 1.0 / 3), Lenz = ceil(1.0*N / Num);
        debug2(Num, Lenz);
        for(int i = 0; i < N; i++)
            scanf("%d", &data[i]), copy[i] = data[i];
        for(int i = 0; i < Num; i++)
            for(int j = 0; j < Num; j++)
                ItvData[i][j] = -1;
        memset(havequery, 0, sizeof(havequery));
        memset(query, 0, sizeof(query));
        memset(low, 0, sizeof(low));
        memset(up, 0, sizeof(up));
        count = 0;
        MergeSort(copy, 0, N);
        tot = count;
        printf("%d", tot);
        for(int i = 0; i < Num; i++)
            get_list(i);
        int mark;
        for(int i = 0; i < N; i++)
        {
            scanf("%d", &mark);
            solve(mark ^ tot);
        }
        printf("\n");
    }
    return 0;
}

/*=======================================
added at 2018年9月18日 21:15:23	problem:qingdaoG
写了两天了
预处理n^(4/3)次复杂度
标记点后将区间分为四段
标记点前不足一个块,前整个块,后不足一个块,后整块
这四段前面任意一段和后面任意一段都需要计算
整块对整块,使用get_change,然后保存,实现优化,如果未保存就是k1*k2*lenz的复杂度
k1为前面块数,k2为后面块数,最多可达bricknum*bricknum*bricklenz/4 (sz^(4/3))
整块对不足一块的利用brickdata保存的数据,复杂度为lenz*k
(lenz为前面的长度,最大bricklenz,k为后面的块数)
不足一块的对不足的,先mergesort然后combine,lenz+lenz复杂度
=======================================*/