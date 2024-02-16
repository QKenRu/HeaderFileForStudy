#ifndef STACK_H
#define STACK_H
#include"list.h"
template<class T>
class Stack
{
	List<T>st;
public:
	Stack(){}
	~Stack(){}
	void Push(const T &item) { st.PushBack(item); } //入栈
	T Pop() { T item = st.Back(); st.PopBack(); return item; } //弹栈
	const T &Top()const{ return st.Back(); } //取栈顶元素
	void Clear() { st.Clear(); } //清栈
	int Size()const{ return st.Size(); } //取个数
	int Empty()const{ return st.Empty(); } //判空
};
#endif