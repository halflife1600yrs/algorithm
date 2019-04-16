# Camp Day1 Summary

前天凌晨赶火车还没缓过来，状态有点差。

今日我队出题BCF。

## A

首先跟队友简化了这个问题：在两个通道点之间只要有点，那么无论点的数量为多少都是等价的。那么问题就转化为选择若干条两端与通道相接的边（虽然不知道这个简化有啥用）

![1547999307887](E:\WorkSpaceC\ACM\wannafly\day1\1547999307887.png)

然后就可以清晰地看到想要走一个循环至少也要走一个包含所有待选边的矩形的周长（必要性），而同时它也能保证到达所有点（充分性），因此也就是我们需要的最优解。

再仔细考虑一下开始点在最一端和所有点都在一侧的情况就可以了。讨论完扔给队友写了，然后为了早点吃饭就提前撤了。

## B

数据范围较小的版本->简单dp，需要注意dp的时候判断一下曼哈顿距离是否小于t（wa了就是因为这个）

听大佬们的说法是寻找大的循环节然后使用倍增？有点迷迷糊糊但是需要后面补题的时候认真证明一下

## C

今天1A的题

半构造半暴力法。队友首先猜想出至多拆成两组，并构造出双奇数的拆法：2，a-2；b-2，2。然后我在这一猜想指导下寻找构造方法：找到一个质数p使$a\%p!=0\&\&b\%p!=0$，那么就可以拆为p，a-p；b-p，p。那么问题就显而易见，只需要遍历质数即可。那么搜索质数范围为多大？最坏情况是前若干个质数均是ab公因子，然后计算器算了一下，前18个质数连乘就会大于1e18，那么只要一个个比较它们即可。再特判一下gcd为1。

## F

做的时候没有分成两个点而是在dij的过程中对两种情况做一下松弛操作然后保存最低值就行了

好晚了。先写这么一点点。
