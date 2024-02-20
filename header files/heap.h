#ifndef HEAP_H
#define HEAP_H
#include"binarytree.h"
#include<iostream>
using namespace std;
template<class T>
class Heap
{
	Vector<T>vt; //以向量类为底层结构
	void PercolateDown(); //向下调整为小根堆，用于删取操作
	void PercolateUp(); //向上调整为小根堆，用于插入操作
public:
	explicit Heap(int max=100):vt(max){} //建空堆
	virtual ~Heap(){} //析构
	int Empty()const { return vt.Empty(); } //判断堆是否为空
	int Size()const { return vt.Size(); } //判断元素个数
	const T& Top()const { return vt.Front(); } //取堆首元素
	void Insert(const T& item); //插入
	void Remove(T& item); //删取，将删除元素取回
	void Clear() { vt.Clear(); } //堆清空
	const T& operator[](int id) const { return vt[id]; } //常量型索引运算符重载
};
template<class T>
BTNode<T>* MakeBTree(const Heap<T>& H) //由堆生成二叉链表
{
	Queue<BTNode<T>*>Q;
	BTNode<T>* t = new BTNode<T>(H[0]); //生成根指针
	BTNode<T>* f, * c; //双亲和孩子指针
	Q.Push(t); //根指针入队
	int i = 0, n = H.Size();
	while (!Q.Empty())
	{
		f = Q.Pop(); //一个结点指针出队
		if (2 * i + 1 < n && H[2 * i + 1] != T()) //如果有左孩子
		{
			c = new BTNode<T>(H[2 * i + 1]); //生成左孩子结点
			f->left = c; //与双亲连接
			Q.Push(c); //左孩子指针入队
		}
		if (2 * i + 2 < n && H[2 * i + 2] != T()) //如果有右孩子
		{
			c = new BTNode<T>(H[2 * i + 2]); //生成右孩子结点
			f->right = c; //与双亲连接
			Q.Push(c); //右孩子指针入队
		}
		++i;
	}
	return t;
}
template<class T>
void Heap<T>::Insert(const T& item) //堆插入
{
	vt.PushBack(item); //读取尾元素
	PercolateUp(); //比较循环：以尾元素为孩子，将双亲与读取元素比较，若不大于读取元素，则结束循环；否则从双亲读取，写入孩子，然后以原来双亲为孩子继续迭代
}
template<class T>
void Heap<T>::PercolateUp() //向上调整为小根堆 
{
	int size = Size(); //元素个数
	int c = size - 1; //尾插元素的索引
	int f = (c - 1) / 2; //双亲索引
	T x = vt[c]; //读取尾元素
	while (c > 0) //比较循环：以尾元素为孩子，将双亲与读取元素比较，若不大于读取元素，则结束循环；否则从双亲读取，写入孩子，然后以原来双亲为孩子继续迭代
		if (vt[f] <= x) //双亲不大于读取的元素
			break;
		else //双亲大于读取的元素
		{
			vt[c] = vt[f]; //从双亲读取，写入孩子
			c = f; //以原来双亲为孩子
			f = (c - 1) / 2;
		}
	vt[c] = x; //把读取元素写入最后读取的位置
}
template<class T>
void Heap<T>::Remove(T& item) //堆删取，删除的元素通过参数返回
{
	item = vt[0]; //读取首元素
	vt[0] = vt[Size() - 1]; //用尾元素覆盖首元素
	vt.PopBack(); //尾删
	PercolateDown(); //向下调整为小根堆
}
template<class T>
void Heap<T>::PercolateDown() //向下调整为小根堆
{
	int size = Size(); //元素个数
	int f = 0; //双亲索引
	int c = 2 * f + 1; //左孩子索引
	T x = vt[f]; //读取首元素
	while (c < size) //比较循环：以首元素为双亲，将左右孩子的小者与读取元素比较，若不小于读取元素，则结束循环；否则从小者读取，写入双亲，然后以原来小者为双亲继续迭代
	{
		if (c + 1 < size && vt[c + 1] < vt[c]) //取左右孩子的小者
			++c;
		if (vt[c] >= x) //小者不小于读取元素
			break;
		else //小者小于读取元素
		{
			vt[f] = vt[c]; //从小者读取，写入双亲
			f = c; //以原来小者为双亲
			c = 2 * f + 1; 
		}
	}
	vt[f] = x; //把读取元素写入最后读取的位置
}

//以下函数用于堆排序，不属于Heap类
template<class T>
void HeapSortPercolateUp(T* p, int id, int n) //将p[id:n)向上调整为小根堆
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
void BuildHeap(T* p, int n) //将p[0:n)建成小根堆
{
	for (int num = 1; num < n; ++num) //堆插入。注：堆是完全二叉树，所以num应该从1开始
		HeapSortPercolateUp(p, 0, num + 1); //将p[0,num+1)向上调整为小根堆
}
/*
将数组建成小根堆还可以使用另一种思路：
把数组看作是完全二叉树的层次序列，每个叶子都是小根堆。从索引最大的非叶子开始到根，每增加一个元素，都可能不再是小根堆，需要向下调整为小根堆。
template<class T>
void BuildHeap(T* p, int n) //将p[0:n)建成小根堆
{
for (int id = n / 2 - 1; id > -1; --id) //n/2-1是非叶子的最大索引
PercolaterDown(p, id, n); //将p[id:n)向下调整为小根堆
}
*/
template<class T>
void HeapSortPercolateDown(T* p, int id, int n) //将p[id:n)向下调整为小根堆
{
	int f = id; //双亲索引
	int c = 2 * f + 1; //左孩子索引
	T x = p[f]; //读取首元素
	while (c < n) //比较循环：以首元素为双亲，将左右孩子的小者与读取元素比较，若不小于读取元素，则结束循环；否则从小者读取，写入双亲，然后以原来小者为双亲继续迭代
	{
		if (c + 1 < n && p[c + 1] < p[c]) //取左右孩子的小者
			++c;
		if (p[c] >= x) //小者不小于读取元素
			break;
		else //小者小于读取元素
		{
			p[f] = p[c]; //从小者读取，写入双亲
			f = c; //以原来小者为双亲
			c = 2 * f + 1;
		}
	}
	p[f] = x; //把读取元素写入最后读取的位置
}
template<class T>
void HeapSort(T* p, int n) //将p[0:n)从大到小堆排序
{
	T item; //作为两数值交换的中间变量
	BuildHeap(p, n); //将p[0:n)建成小根堆
	for (int num = n; num > 0; --num) //堆删取
	{
		item = p[0];
		p[0] = p[num - 1];
		p[num - 1] = item;
		HeapSortPercolateDown(p, 0, num - 1); //将p[0,num-1)向下调整为小根堆
	}
}
#endif