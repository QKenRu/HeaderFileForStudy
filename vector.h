#ifndef VECTOR_H
#define VECTOR_H
#include<stdlib.h>
using namespace std;
template<class T>
class Vector
{
private:
	T*data; //指向动态数组的指针
	int size; //数组的数据元素个数
	int max; //数组容量
public:
//迭代器类型
	typedef T*iterator; //迭代器
	typedef const T*const_iterator; //const型迭代器
//读取迭代器区间边界
	iterator Begin() { return data; } //读取左闭区间
	const_iterator Begin()const{ return data; }
	iterator End() { return data + size; } //读取右开区间
	const_iterator End()const{ return data + size; }
//构造与析构
	explicit Vector(int n=10):size(0),max(n) { data=new T[max]; } //转换和默认构造
	Vector(const Vector &v):data(0),max(0) { *this=v; } //复制赋值
	~Vector() { delete[]data; }
//复制赋值
	Vector &operator=(const Vector<T> &v); //复制赋值
//插入
	void Reserve(int newMax); //扩大数组容量，保留原数据
	void PushBack(const T &item); //尾插
//删除
	void PopBack() { --size; } //尾删
	void Clear() { size=0; } //清空
//索引运算符重载
	T &operator[](int id) { return data[id]; } //下标运算符函数
	const T &operator[](int id)const{ return data[id]; } //常量型下标运算符函数
//读取
	bool Empty()const{ return size==0; } //判空
	int Size()const{ return size; } //求数据元素个数
	int Max()const{ return max; } //求数组容量
	const T &Back()const{ return data[size - 1]; } //返回尾元素的引用
	const T &Front()const{ return data[0]; } //返回首元素的引用
};

template<class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &v) //复制赋值
{
	delete[]data;
	data=new T[v.max];
	size=v.size;
	max=v.max;
	for (int i=0; i < size; ++i)
		data[i]=v.data[i];
	return *this;
}
template<class T>
void Vector<T>::PushBack(const T &item) //尾插
{
	if (size==max) //如果空间数据已满，就要先扩大容量
		Reserve(2 *max + 1);
	data[size++]=item; //插入元素到尾部，数据元素个数增1
}

template<class T>
void Vector<T>::Reserve(int newmax)
{
	if(newmax <=max) //如果数组容量已满足，则返回
		return;
	T*old=data; //保留原数组
	data=new T[newmax]; //重新分配新数组
	for (int i=0; i < size; ++i) //将原数组中的数据复制到新数组
		data[i]=old[i];
	max=newmax; //修改数组容量
	delete[]old; //释放原数组空间
}
#endif