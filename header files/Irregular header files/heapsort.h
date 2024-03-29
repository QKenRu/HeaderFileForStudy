#ifndef HEAPSORT_H
#define HEAPSORT_H
template<class T>
void PercolateUp(T *p,int id,int n) //将p[id:n)向上调整为小根堆
{
	int c = n - 1; //尾插元素的索引
	int f = (c - 1) / 2; //双亲索引
	T x = p[c]; //读取尾元素
	while (c > id) //比较循环：以尾元素为孩子，将双亲与读取元素比较，若不大于读取元素，则结束循环；否则从双亲读取，写入孩子，然后以原来双亲为孩子继续迭代
		if (p[f] <= x) //双亲不大于读取的元素
			break;
		else //双亲大于读取的元素
		{
			p[c] = p[f]; //从双亲读取，写入孩子
			c = f; //以原来双亲为孩子
			f = (c - 1) / 2;
		}
	p[c] = x; //把读取元素写入最后读取的位置
}
template<class T>
void BuildHeap(T *p,int n) //将p[0:n)建成小根堆
{
	for (int num = 1; num < n; ++num) //堆插入。注：堆是完全二叉树，所以num应该从1开始
		PercolateUp(p,0,num + 1); //将p[0,num+1)向上调整为小根堆
}
/*
将数组建成小根堆还可以使用另一种思路：
把数组看作是完全二叉树的层次序列，每个叶子都是小根堆。从索引最大的非叶子开始到根，每增加一个元素，都可能不再是小根堆，需要向下调整为小根堆。
template<class T>
void BuildHeap(T *p,int n) //将p[0:n)建成小根堆
{
	for (int id = n / 2 - 1; id > -1; --id) //n/2-1是非叶子的最大索引
		PercolaterDown(p,id,n); //将p[id:n)向下调整为小根堆
}
*/
template<class T>
void PercolateDown(T *p,int id,int n) //将p[id:n)向下调整为小根堆
{
	int f = id; //双亲索引
	int c = 2  *f + 1; //左孩子索引
	T x = p[f]; //读取首元素
	while (c < n) //比较循环：以首元素为双亲，将左右孩子的小者与读取元素比较，若不小于读取元素，则结束循环；否则从小者读取，写入双亲，然后以原来小者为双亲继续迭代
	{
		if (c + 1 < n & &p[c + 1] < p[c]) //取左右孩子的小者
			++c;
		if (p[c] >= x) //小者不小于读取元素
			break;
		else //小者小于读取元素
		{
			p[f] = p[c]; //从小者读取，写入双亲
			f = c; //以原来小者为双亲
			c = 2  *f + 1;
		}
	}
	p[f] = x; //把读取元素写入最后读取的位置
}
template<class T>
void HeapSort(T *p,int n) //将p[0:n)从大到小堆排序
{
	T item; //作为两数值交换的中间变量
	BuildHeap(p,n); //将p[0:n)建成小根堆
	for (int num = n; num > 0; --num) //堆删取
	{
		item = p[0];
		p[0] = p[num - 1];
		p[num - 1] = item;
		PercolateDown(p,0,num - 1); //将p[0,num-1)向下调整为小根堆
	}
}
#endif