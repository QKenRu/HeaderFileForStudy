#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include"vector.h"
#include"binarytree.h"
#include"heap.h"
#include"stack.h"
#include"seqlist.h"
template<class T>
struct Hufm
{
	BTNode<T> *t;
	int operator<(const Hufm &h) { return t->data < h.t->data; }
	int operator<=(const Hufm &h) { return t->data <= h.t->data; }
	int operator>(const Hufm &h) { return t->data > h.t->data; }
	int operator>=(const Hufm &h) { return t->data >= h.t->data; }
	int operator==(const Hufm &h) { return t->data == h.t->data; }
	int operator!=(const Hufm &h) { return t->data != h.t->data; }
};
template<class T>
BTNode<T> *HufmTree(const SeqList<T> &value,int n) //有n个权存储在数组中，用该数组建立哈夫曼树
{
	Hufm<T>hf; //哈夫曼结构对象
	BTNode<T> *l; //二叉链表结点指针
	BTNode<T> *r; //二叉链表结点指针
	Heap<Hufm<T>>H(n); //建立以哈夫曼结构对象为元素的小根堆
	for (int i = 0; i < n; ++i) //每一个权生成一个哈夫曼结构对象，作为独根哈夫曼树插入堆。根的权就是结点数据成员data的值
	{
		hf.t = new BTNode<T>(value.GetData(i));
		H.Insert(hf);
	}
	while (H.Size() > 1) //进入循环。每一次迭代都从堆中提取两个元素作为左右孩子，形成二叉树，根的权是左右孩子的权之和，然后插入堆，直到堆中只有一个元素
	{
		H.Remove(hf);
		l = hf.t;
		H.Remove(hf);
		r = hf.t;
		hf.t = new BTNode<T>(l->data + r->data,l,r);
		H.Insert(hf);
	}
	H.Remove(hf); //提取堆中的元素，返回其中的数据成员，那是哈夫曼树的根
	return hf.t;
}
/*
template<class T>
void OutputCode(Vector<const BTNode<T>*>vt) //哈夫曼编码②
{
	Tname Vector<const BTNode<T>*>::iterator first = vt.Begin();
	Tname Vector<const BTNode<T>*>::iterator last = vt.End();
	cout << (  *(last - 1))->data << ':'; //输出代码的权
	const BTNode<T> *t = *first;
	++first;
	while (first != last)
	{
		if (t->left == *first)
			cout << '0';
		else
			cout << '1';
		t = *first;
		++first;
	}
	cout << endl;
}
template<class T>
void HafmCoder(const BTNode<T> *t) //哈夫曼编码①
{
	if (t == 0)
		return;
	const BTNode<T> *p;
	Vector<const BTNode<T>*>S; //把结点指针栈改为结点指针向量，以便通过遍历路径来得到哈夫曼编码
	int tag;
	Stack<int>tagS; //记录结点指针入栈次数，当结点第二次出栈时，访问该结点
	while(t||!S.Empty())
		if (t)
		{
			S.PushBack(t);
			tagS.Push(1);
			t = t->left;
		}
		else
		{
			p = S.Back();
			S.PopBack();
			tag = tagS.Pop();
			if (tag == 1)
			{
				S.PushBack(p);
				tagS.Push(2);
				t = p->right;
			}
			else if (p->left == 0 & &p->right == 0) //把输出结点的条件改为输出叶子的条件，叶子的左、右子树为空。输出叶子的操作有三步
			{
				S.PushBack(p); //将叶子尾插到向量对象，这是向量对象存储的根到该叶子的路径
				OutputCode(S); //通过向量对象输出该叶子的编码
				S.PopBack(); //尾删该叶子，继续后序遍历迭代算法
			}
		}
}
*/
template<class T>
void OutputCode(Vector<const BTNode<T>*>vt,const SeqList<int> &value,const SeqList<char> &word,const int n) //哈夫曼编码②
{
	fstream file;
	file.open("D:\\HuffmanCode.txt",ios::out|ios::app);
	typename Vector<const BTNode<T>*>::iterator first = vt.Begin();
	typename Vector<const BTNode<T>*>::iterator last = vt.End();
	for (int i = 0; i < n; ++i)
	{
		if (value.GetData(i) == (*(last - 1))->data)
		{
			cout << word.GetData(i) << ':';
			file << word.GetData(i) << ':'; //输出代码的权
		}
	}
	const BTNode<T> *t = *first;
	++first;
	while (first != last)
	{
		if (t->left == *first)
		{
			cout << '0';
			file << '0';
		}
		else
		{
			cout << '1';
			file << '1';
		}
		t = *first;
		++first;
	}
	cout << endl;
	file << endl;
	file.close();
}
template<class T>
void HafmCoder(const BTNode<T> *t,const SeqList<int> &value,const SeqList<char> &word,const int n) //哈夫曼编码①
{
	if (t == 0)
		return;
	const BTNode<T> *p;
	Vector<const BTNode<T>*>S; //把结点指针栈改为结点指针向量，以便通过遍历路径来得到哈夫曼编码
	int tag;
	Stack<int>tagS; //记录结点指针入栈次数，当结点第二次出栈时，访问该结点
	while (t || !S.Empty())
		if (t)
		{
			S.PushBack(t);
			tagS.Push(1);
			t = t->left;
		}
		else
		{
			p = S.Back();
			S.PopBack();
			tag = tagS.Pop();
			if (tag == 1)
			{
				S.PushBack(p);
				tagS.Push(2);
				t = p->right;
			}
			else if (p->left == 0 & &p->right == 0) //把输出结点的条件改为输出叶子的条件，叶子的左、右子树为空。输出叶子的操作有三步
			{
				S.PushBack(p); //将叶子尾插到向量对象，这是向量对象存储的根到该叶子的路径
				OutputCode(S,value,word,n); //通过向量对象输出该叶子的编码
				S.PopBack(); //尾删该叶子，继续后序遍历迭代算法
			}
		}
}
template<class T>
void Output(const Vector<T>vt) //哈夫曼译码②：电文输出
{
	fstream file;
	file.open("D:\\HuffmanText.txt",ios::out|ios::app);
	Vector<T>::const_iterator first = vt.Begin();
	Vector<T>::const_iterator last = vt.End();
	while (first != last)
	{
		file << *first<<" ";
		++first;
	}
	file << endl;
	file.close();
}
template<class T>
void HufmDecoder(const BTNode<T> *t,char *c) //哈夫曼译码①
{
	const BTNode<T> *r = t; //提取二叉树根
	int i = 0;
	Vector<int>v; //用于存放译码
	while (c[i] != '\0' & &r != 0)
	{
		if (c[i] == '0')
			r = r->left;
		else
			r = r->right;
		if (r->left == 0 & &r->right == 0) //读到叶子
		{
			v.PushBack(r->data); //保存译码的一个字符
			r = t;
		}
		++i;
	}
	if (c[i] == '\0' & &r != t) //电文没有结束或提前结束
		cout << "Error." << endl;
	else
		Output(v);
}
#endif