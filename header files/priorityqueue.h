#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include"list.h"
template<class T>
class PQueue
{
	List<T>que;
public:
	PQueue(){}
	~PQueue(){}
	void Push(const T &item) { que.PushBack(item); } //入队
	T Pop(); //出队
	void Clear() { que.Clear(); } //清空队列
	int Size()const{ return que.Size(); } //取数据元素个数
	bool Empty()const{ return que.Empty(); } //判空
};
template<class T>
T PQueue<T>::Pop() //以最小值为优先级最高
{
	typename List<T>::iterator min = que.Begin(); //假设首元素是最小元素
	typename List<T>::iterator first = que.Begin();
	typename List<T>::iterator last = que.End(); //查找最小元素
	for (; first != last; ++first) //查找最小元素
		if ((*first) < (*min))
			min = first; //指向当前最小元素
	T item = *min; //存储最小元素值
	que.Erase(min); //删除最小元素结点
	return item; //返回最小元素值
}
#endif