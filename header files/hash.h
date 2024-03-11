#ifndef HASH_H
#define HASH_H
#include"..\..\AAAPublicHeaderFile\vector.h"
#include"..\..\AAAPublicHeaderFile\list.h"
#include<iostream>
#include<iomanip>
using namespace std;
template<class T>
//这里的Hash类采用分离链表法(separate chaining)来处理关键码(key)冲突(collision)，其特点是把散列到同一个桶里的关键码保留到一个链表中，每个表是一个List对象，散列表是List对象数组
class Hash
{
	Vector<List<T>> ht; //一个桶一个List对象，ht全称为hash table，即散列表或哈希表
	int (*hf)(const T &x); //散列函数指针
	int sizeBucket; //桶总数
public:
	explicit Hash(int n,int (*hash)(const T &)):ht(n),hf(hash){ sizeBucket=n; } //这里"int (*hash)(const T &)"是将一个int型函数作为另一个的函数的形参，意味着头文件不自带散列函数，而是由用户自行完成
	bool Insert(const T &x); //插入
	bool Erase(const T &x); //删除
	bool Find(const T &x)const; //查找
	int SizeKey()const; //关键码总数
	void Output()const; //显示器输出
};

template<class T>
int Hash<T>::SizeKey()const
{ //关键码总数
	int counter=0; //累加器
	for(int i=0;i<sizeBucket;++i)
	{ //累计每个桶的长度
		counter+=ht[i].Size();
	}
	return counter;
}

template<class T>
bool Hash<T>::Insert(const T &x)
{ //插入
	if(!Find(x))
	{
		ht[hf(x)].PushBack(x);
		return 1;
	}
	return 0;
}
template<class T>
bool Hash<T>::Erase(const T &x)
{ //删除
	List<T> &L=ht[hf(x)];
	typename List<T>::iterator first=L.Begin();
	typename List<T>::iterator last=L.End();
	for(;first!=last;++first)
	{
		if(*first==x)
		{
			L.Erase(first);
			return 1;
		}
	}
	return 0;
}
template<class T>
bool Hash<T>::Find(const T &x)const
{ //查找
	const List<T> &L=ht[hf(x)];
	typename List<T>::const_iterator first=L.Begin();
	typename List<T>::const_iterator last=L.End();
	for(;first!=last;++first)
	{
		if(*first==x)
		{
			return 1;
		}
	}
	return 0;
}

template<class T>
void Hash<T>::Output()const
{ //显示器输出
	typename List<T>::const_iterator first;
	typename List<T>::const_iterator last;
	for(int i=0;i<sizeBucket;++i)
	{
		first=ht[i].Begin();
		last=ht[i].End();
		for(;first!=last;++first)
		{
			cout<<setw(6)<<*first<<' ';
		}
		cout<<endl;
	}
}

#endif