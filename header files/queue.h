#ifndef QUEUE_H
#define QUEUE_H
#include"list.h"
template<class T>
class Queue
{
	List<T>que;
public:
	Queue(){}
	~Queue(){}
	void Push(const T &item) { que.PushBack(item); } //入队
	T Pop() { T item = que.Front(); que.PopFront(); return item; } //出队
	const T &Front()const{ return que.Front(); } //取队头元素
	void Clear() { que.Clear(); } //置空队
	int Size()const{ return que.Size(); } //取个数
	int Empty()const{ return que.Empty(); } //判空
};
#endif