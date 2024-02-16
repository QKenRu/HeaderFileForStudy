#ifndef SEQLIST_H
#define SEQLIST_H
#include<iostream>
using namespace std;
template<class T>
class SeqList
{
private:
	T *data;
	int max;
	int size;
public:
	explicit SeqList(int n = 10):max(10),size(0) { data = new T[n]; } //转换和默认构造
	SeqList(const SeqList &l):data(0) { *this = l;} //复制构造
	~SeqList() { delete[]data; } //析构
	SeqList &operator=(const SeqList &l); //复制赋值
	void Reserve(int newmax); //扩容
	void Insert(int id,T item); //定点插入
	void Insertup(int id); //定点自加
	void Insertfix(int id,T item); //定点修改
	void PushBack(const T &item) { Insert(size,item); } //尾插
	void PushFront(const T &item) { Insert(0,item); } //首插
	void Erase(int id); //定点删除
	void PopFront() { Erase(0); } //首删
	void PopBack() { Erase(size); } //尾删
	void Clear() { size = 0; } //清表
	T &operator[](int id) { return data[id]; } //非常量索引
	const T &operator[](int id)const{ return data[id]; } //常量索引
	bool Empty()const{ return size == 0; }
	int GetSize()const{ return size; }
	const T &GetData(int id)const{ return data[id]; }
};
template<class T>
void SeqList<T>::Reserve(int newmax) //扩容
{
	if (newmax <= max)
		return;
	T *old = data; //指向数组，以保留原始数据
	max = newmax; //扩大数组长度
	data = new T[newmax]; //建新数组
	for (int i = 0; i < size; ++i) //将原始数据元素写入新数组空间
		data[i] = old[i];
	delete []old; //释放原数组空间
}
template<class T>
void SeqList<T>::Insert(int id,T item) //定点插入
{
	if (id < 0 || id>size + 1)
		cout<<("Insert:Id is illegal");
	if (size == max)
		Reserve(2*max);
	for (int i = size - 1; i >= id; --i)
		data[i + 1] = data[i];
	data[id] = item;
	++size;
}
template<class T>
void SeqList<T>::Insertup(int id) //定点自加
{
	if (id < 0 || id>size + 1)
		cout << ("Insertup:Id is illegal");
	++data[id];
}
template<class T>
void SeqList<T>::Insertfix(int id,T item) //定点修改
{
	if (id < 0 || id>size + 1)
		cout << ("Insertfix:Id is illegal");
	data[id]=item;
}
template<class T>
void SeqList<T>::Erase(int id) //定点删除
{
	if (id<0 || id>size)
		cout<<("Erase:id is illegal");
	for (int i = id + 1; i < size; ++i)
		data[i - 1] = data[i];
	--size;
}
template<class T>
SeqList<T> &SeqList<T>::operator=(const SeqList &l) //复制赋值
{
	delete[]data;
	data = new T[l.max];
	size = l.size;
	max = l.max;
	for (int i = 0; i < size; ++i)
		data[i] = l.data[i];
	return *this;
}
#endif