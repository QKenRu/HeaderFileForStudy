#ifndef BINARYSEARCHTREE_H //二叉搜索链表类
#define BINARYSEARCHTREE_H
#include"queue.h"
#include"stack.h"
#include<iostream>
using namespace std;
template<class T>
class BSTree
{
	struct BTNode
	{
		T data;
		BTNode *left, *right;
		BTNode(const T &item=T(),BTNode *l=0,BTNode *r=0):data(item),left(l),right(r){}
	};
	BTNode *root; //根指针
	int size; //结点个数
	void Insert(const T &x,BTNode **t); //插入
	void Erase(const T &x,BTNode **t); //删除
	void Update(const T &x,BTNode **t); //更新
	void Clear(BTNode *t); //清空
	BTNode *FindMin(BTNode *t)const; //查找最小元素
	BTNode *FindMax(BTNode *t)const; //查找最大元素
	BTNode *Find(const T &x,BTNode *t)const; //查找
	void PrintBSTree(const BTNode *t,int w); //垂直输出
public:
	class const_iterator  //中序迭代器
	{
	protected:
		BTNode *current;
		T &retrieve()const{ return current->data; }
		const_iterator(BTNode *t) { current = GoFarLeft(t); } //构造函数
		Stack<BTNode*>St; //栈
		BTNode *GoFarLeft(BTNode *t) //查找中序序列首结点指针
		{
			if (t == 0)
				return 0;
			while (t->left)
			{
				St.Push(t);
				t = t->left;
			}
			return t;
		}
		friend class BSTree<T>;
	public:
		const_iterator():current(0) {}
		const T &operator *()const{ return retrieve(); }
		const_iterator &operator++() //前++
		{
			if (current->right)
				current = GoFarLeft(current->right);
			else if (!St.Empty())
				current = St.Pop();
			else
				current = 0;
			return *this;
		}
		bool operator==(const const_iterator &rhs)const{ return current == rhs.current; }
		bool operator!=(const const_iterator &rhs)const{ return current != rhs.current; }
	};
	class iterator: public const_iterator
	{
	protected:
		iterator(BTNode *t):const_iterator(t) {}
		friend class BSTree<T>;
	public:
		iterator() {}
		T &operator*() { return this->retrieve(); }
		const T &operator*()const{ return(const_iterator::operator*()); }
		iterator &operator++()
		{
			if (this->current->right)
				this->current = this->GoFarLeft(this->current->right);
			else if (!this->St.Empty())
				this->current = this->St.Pop();
			else
				this->current = 0;
			return  *this;
		}
	};
public:
	BSTree():root(0),size(0) {}; //默认构造
	virtual ~BSTree() { Clear(); } //析构
	const_iterator Begin()const{ return const_iterator(root); }
	iterator Begin() { return iterator(root); }
	const_iterator End()const{ return const_iterator(0); }
	iterator End() { return iterator(0); }
	void Insert(const T &x) { Insert(x,&root); } //插入
	void Erase(const T &x) { Erase(x,&root); } //删除
	void Update(const T &x) { Update(x,&root); } //更新
	void Clear() { Clear(root); }  //清空
	T &FindMin()const{ return FindMin(root)->data; } //查找最小元素
	T &FindMax()const{ return FindMax(root)->data; } //查找最大元素
	int Find(const T &x)const{ return Find(x,root) != 0; } //查找
	int Size() { return size; } //读取结点个数
	void PrintBSTree(int w) { PrintBSTree(root,w); /*调用私有方法*/ } //垂直输出
};
template<class T>
void BSTree<T>::Clear(BTNode *t) //清空
{
	if (t == 0)
		return;
	Clear(t->left);
	Clear(t->right);
	delete t;
}
template<class T>
void BSTree<T>::Insert(const T &x,BTNode **t) //插入
{
	while ((*t) != 0)
	{
		if (x < (*t)->data) //如果比当前结点的值小
			t = &((*t)->left); //到左子树查找插入位置
		else //如果比当前结点的值大
			t = &((*t)->right); //到右子树查找插入位置
	}
	(*t) = new BTNode(x); //插入
	++size;
}
struct Location //垂直输出，位置
{
	int x,y;
};
void Gotoxy(int x,int y) //垂直输出，移动光标到坐标(x,y)
{
	static int indent = 0; //偏移量
	static int level = 0; //层数
	if (y == 0)
	{
		level = 0;
		indent = 0;
	}
	if (y != level) //换行输出时，从头开始
	{
		int n = y - level;
		for (int i = 0; i < n; ++i)
		{
			cout << endl;
			++level;
		}
		indent = 0;
	}
	cout.width(x - indent); //同行输出时减量
	indent = x; //记录输出的列坐标
}
template<class T>
void BSTree<T>::PrintBSTree(const BTNode *t,int w) //垂直输出
{ //代码大体同btnode.h的垂直输出二叉树PrintBTree函数
	if (t == 0)
		return;
	int level = 0,off = w / 2; //从0层开始，偏移量是宽度的1/2
	Location f,c;
	Queue<const BTNode*>Q; //存储结点指针，此处与btnode.h中的函数不同
	Queue<Location>LQ; //存储结点输出位置
	f.x = off;
	f.y = level;
	Q.Push(t);
	LQ.Push(f);
	while (!Q.Empty())
	{
		t = Q.Pop();
		f = LQ.Pop();
		Gotoxy(f.x,f.y); //移动光标到输出位置
		cout << t->data;
		if (f.y != level) //除根外，每层首结点输出后，都修改层数和偏移量
		{
			++level;
			off /= 2;
		}
		if (t->left)
		{
			Q.Push(t->left);
			c.x = f.x - off / 2;
			c.y = f.y + 1;
			LQ.Push(c);
		}
		if (t->right)
		{
			Q.Push(t->right);
			c.x = f.x + off / 2;
			c.y = f.y + 1;
			LQ.Push(c);
		}
	}
	cout << endl;
}
template<class T>
void BSTree<T>::Erase(const T &y,BTNode **t) //删除。因为删除方法要修改结点中指针域的值，所以需要传递指针的地址，相应的形参为指向指针的指针
{
	T z = y;
	while (*t) //查找要删除的结点。如果要删除的元素比当前结点的值小，就到左子树查找；如果要删除的元素比当前结点的值大，就到右子树查找
		if (z < (*t)->data)
			t = &((*t)->left);
		else if (z > (*t)->data)
			t = &((*t)->right);
		else if ((*t)->left != 0 & &(*t)->right != 0) //要删除的元素结点有左、右子树。查找该节点右子树的最小结点，用最小结点的值覆盖要删除的结点的值；然后将这个值作为要删除的元素，在右子树查找该元素结点，这个结点一定没有左子树
		{
			(*t)->data = FindMin((*t)->right)->data;
			z = (*t)->data;
			t = &((*t)->right);
		}
		else //要删除的元素结点没有左子树，或左、右子树都没有。将子树直接与要删除的结点的双亲连接
		{
			BTNode *old = *t; //指向要删除的结点
			(*t) = ((*t)->left != 0) ? (*t)->left: (*t)->right; //其实此处(*t)结点一定没有左子树，指针此时要么为NULL，要么为(*t)->right
			delete old;
			--size;
		}
}
template<class T>
void BSTree<T>::Update(const T  &x,BTNode **t) //更新
{
	BTNode *p = Find(x,*t); //根据关键词查找结点
	if (p) //查找到
		p->data = x;
	else //没查找到
		Insert(x);
}
template<class T>
typename BSTree<T>::BTNode *BSTree<T>::Find(const T &x,BTNode *t)const //查找
{
	while (t != 0 & &x != t->data)
		if (x < t->data)
			t = t->left;
		else
			t = t->right;
	return t;
}
template<class T>
typename BSTree<T>::BTNode *BSTree<T>::FindMin(BTNode *t)const //查找最小元素
{
	if (t != 0)
		while (t->left != 0)
			t = t->left;
	return t;
}
template<class T>
typename BSTree<T>::BTNode *BSTree<T>::FindMax(BTNode *t)const //查找最大元素
{
	if (t != 0)
		while (t->right != 0)
			t = t->right;
	return t;
}
#endif