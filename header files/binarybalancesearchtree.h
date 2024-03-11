#ifndef BINARYBALANCESEARCHTREE_H
#define BINARYBALANCESEARCHTREE_H
#include"queue.h"
#include"stack.h"
#include<iostream>
using namespace std;

template<class T>
class AvlTree
{
	struct BTNode
	{
		T data;
		BTNode *left,*right;
		int height;
		BTNode(const T &item,BTNode *l = 0,BTNode *r = 0,int h = 0):data(item),left(l),right(r),height(h){}
	};
	BTNode *root;
	int size;
	void Insert(BTNode **t,const T &y);
	void Erase(BTNode **t,const T &y);
	void Clear(BTNode *t);
	void RR(BTNode **t);
	void RL(BTNode **t);
	void RRL(BTNode **t);
	void RLR(BTNode **t);
	BTNode *FindMin(BTNode *t)const; //查找最小元素结点
	BTNode *FindMax(BTNode *t)const; //查找最大元素结点
	BTNode *Find(BTNode *t,const T &x)const; //查找特定元素结点
	int H(BTNode *t)const{ return t == 0 ? -1: t->height; } //节点高度
	int Max(int x1,int x2) { return x1 < x2 ? x2: x1; } //最大值
	void PrintAvlTree(const BTNode *t,int w);

public:
	class const_iterator
	{
	protected:
		BTNode *current;
		T &retrieve() const{ return current->data; }
		const_iterator(BTNode *t) { current = GoFarLeft(t); } //构造函数
		Stack<BTNode*>BTNodeS;
		BTNode *GoFarLeft(BTNode *t)
		{
			if (!t)
			{
				return 0;
			}
			while (t->left)
			{
				BTNodeS.Push(t);
				t = t->left;
			}
			return t;
		}
		friend class AvlTree<T>;
	public:
		const_iterator():current(0) {}
		const T &operator *()const{ return retrieve(); }
		const_iterator &operator++() //前++
		{
			if (current->right)
			{
				current = GoFarLeft(current->right);
			}
			else if (!BTNodeS.Empty())
			{
				current = BTNodeS.Pop();
			}
			else
			{
				current = 0;
			}
			return *this;
		}
		bool operator==(const const_iterator &rhs)const{ return current == rhs.current; }
		bool operator!=(const const_iterator &rhs)const{ return current != rhs.current; }
	};
	class iterator:public const_iterator
	{
	protected:
		iterator(BTNode *t):const_iterator(t) {}
		friend class AvlTree<T>;
	public:
		iterator() {}
		T &operator *() { return const_iterator::retrieve(); }
		const T &operator *()const{ return (const_iterator::operator *()); }
		iterator &operator++() //前++
		{
			if (this->current->right)
			{
				this->current = GoFarLeft(this->current->right);
			}
			else if (!this->BTNodeS.Empty())
			{
				this->current = this->BTNodeS.Pop();
			}
			else
			{
				this->current = 0;
			}
			return *this;
		}
	};

public:
	AvlTree():root(0),size(0) {} //默认构造
	virtual ~AvlTree() { Clear(); } //析构
	const_iterator Begin()const{ return const_iterator(root); }
	iterator Begin() { return iterator(root); }
	const_iterator End()const{ return 0; }
	iterator End() { return 0; }
	void Insert(const T &x) { Insert(&root,x); } //插入
	void Erase(const T &x) { Erase(&root,x); } //删除
	void Clear() { Clear(root); }
	T &FindMin()const{ return FindMin(root)->data; } //查找最小元素
	T &FindMax()const{ return FindMax(root)->data; } //查找最大元素
	bool Find(const T &x)const{ return Find(root,x)!=0; } //查找特定元素是否存在
	void Update(const T &x); //更新
	int Size() { return size; } //读取结点个数
	void PrintAvlTree(int w) { PrintAvlTree(root,w); }

};

template<class T>
void AvlTree<T>::RL(BTNode **t)
{
	BTNode *c = (*t)->right;
	(*t)->right = c->left;
	c->left = *t;
	(*t)->height = Max(H((*t)->left),H((*t)->right)) + 1;
	c->height = Max((*t)->height,H(c->right)) + 1;
	*t = c;
}
template<class T>
void AvlTree<T>::RR(BTNode **t)
{
	BTNode *c = (*t)->left;
	(*t)->left = c->right;
	c->right = *t;
	(*t)->height = Max(H((*t)->left),H((*t)->right)) + 1;
	c->height = Max(H(c->left),(*t)->height) + 1;
	*t = c;
}
template<class T>
void AvlTree<T>::RRL(BTNode **t)
{
	RR(&(*t)->right);
	RL(t);
}
template<class T>
void AvlTree<T>::RLR(BTNode **t)
{
	RL(&(*t)->left);
	RR(t);
}

template<class T>
typename AvlTree<T>::BTNode *AvlTree<T>::FindMin(BTNode *t) const
{
	if (t != 0)
	{
		while (t->left != 0)
		{
			t = t->left;
		}
	}
	return t;
}
template<class T>
typename AvlTree<T>::BTNode *AvlTree<T>::FindMax(BTNode *t) const
{
	if (t != 0)
	{
		while (t->right != 0)
		{
			t = t->right;
		}
	}
	return t;
}
template<class T>
typename AvlTree<T>::BTNode *AvlTree<T>::Find(BTNode *t,const T &x)const
{
	while (t != 0 & &x != t->data)
	{
		if (x < t->data)
		{
			t = t->left;
		}
		else
		{
			t = t->right;
		}
	}
	return t;
}

template<class T>
void AvlTree<T>::Insert(BTNode **t,const T &y)
{
	Stack<BTNode **>S; //建立栈，用于存储结点指针
	while (*t) //查找插入位置，每次进入下一级子树查找前，都把当前结点指针入栈保存
	{
		S.Push(t);
		if (y < (*t)->data)
		{
			t = &((*t)->left);
		}
		else if (y > (*t)->data)
		{
			t = &((*t)->right);
		}
	}
	*t = new BTNode(y); //插入结点
	++size;
	while (!S.Empty()) //弹栈。栈中的指针所指向的结点是从根到插入结点的一条路径。因为插入，这条路径上的子树可能因层数增加而破坏与兄弟子树的平衡，所以每次得到一个指针，都要做两件事：一是判断该指针所指向的结点其
	{ //左、右子树是否平衡，若不则按照类型调整；二是修改该结点的层数
		t = S.Pop(); //弹出一个结点指针
		if (H((*t)->left) - H((*t)->right) == 2)
		{
			if (H((*t)->left->left) >= H((*t)->left->right))
			{
				RR(t);
			}
			else
			{
				RLR(t);
			}
		}
		else if (H((*t)->right) - H((*t)->left) == 2)
		{
			if (H((*t)->right->right) >= H((*t)->right->left))
			{
				RL(t);
			}
			else
			{
				RRL(t);
			}
		}
		(*t)->height = Max(H((*t)->left),H((*t)->right)) + 1; //修改结点的层数，该结点是参与调整前的子树的根节点的层数
	}
}

template<class T>
void AvlTree<T>::Erase(BTNode **t,const T &y)
{
	Stack<BTNode **>BTNodeS; //建立栈，用于存储结点指针。复制要删除的元素
	T z = y;
	while (*t) //查找删除结点。每次进入下一级子树查找前，都把当前结点指针入栈保存
	{
		if (z < (*t)->data)
		{
			BTNodeS.Push(t);
			t = &((*t)->left);
		}
		else if (z > (*t)->data)
		{
			BTNodeS.Push(t);
			t = &((*t)->right);
		}
		else if ((*t)->left != 0 & &(*t)->right != 0)
		{
			(*t)->data = FindMin((*t)->right)->data;
			z = (*t)->data;
			BTNodeS.Push(t);
			t = &((*t)->right);
		}
		else //删除结点
		{
			BTNode *old = *t;
			(*t) = ((*t)->left != 0) ? (*t)->left: (*t)->right;
			delete old;
			--size;
		}
	}
	while (!BTNodeS.Empty()) //弹栈。栈中的指针所指向的结点是从根到删除结点的一条路径。因为删除，这条路径上的子树可能因层数减少而破坏与兄弟子树的平衡，所以每次得到一个指针，都要做两件事：
	{ //一是判断该指针所指向的结点其左、右子树是否平衡，若不，则按照类型调整；二是修改该结点的层数
		t = BTNodeS.Pop();
		if (H((*t)->left) - H((*t)->right) == 2)
		{
			if (H((*t)->left->left) >= H((*t)->left->right))
			{
				RR(t);
			}
			else
			{
				RLR(t);
			}
		}
		else if (H((*t)->right) - H((*t)->left) == 2)
		{
			if (H((*t)->right->right) >= H((*t)->right->left))
			{
				RL(t);
			}
			else
			{
				RRL(t);
			}
		}
		(*t)->height = Max(H((*t)->left),H((*t)->right)) + 1;
	}
}

template<class T>
void AvlTree<T>::Update(const T &x) //此函数暂不明白其功能，有些多余，请勿使用
{
	BTNode *p = Find(root,x); //根据关键字查找结点
	if (p) //查找到
	{
		p->data = x;
	}
	else
	{
		Insert(x);
	}
}

template<class T>
void AvlTree<T>::Clear(BTNode *t)
{
	if (t == 0)
	{
		return;
	}
	Clear(t->left);
	Clear(t->right);
	delete t;
}

struct Location
{
	int x,y;
};
void Gotoxy(int x,int y)
{
	static int indent = 0,level = 0;
	if (y == 0)
	{
		level = 0;
		indent = 0;
	}
	if (y != level)
	{
		int n = y - level;
		for (int i = 0; i < n; ++i)
		{
			cout << endl;
			++level;
		}
		indent = 0;
	}
	cout.width(x - indent);
	indent = x;
}
template<class T>
void AvlTree<T>::PrintAvlTree(const BTNode *t,int w)
{
	int off =w/ 2,level = 0;
	Location f,c;
	Queue<const BTNode*>BTNodeQ;
	Queue<Location> LocationQ;
	f.x = off,f.y = level;
	BTNodeQ.Push(t);
	LocationQ.Push(f);
	while (!BTNodeQ.Empty())
	{
		t = BTNodeQ.Pop();
		f = LocationQ.Pop();
		Gotoxy(f.x,f.y);
		cout << t->data;
		if (f.y != level)
		{
			off /= 2;
			++level;
		}
		if (t->left)
		{
			BTNodeQ.Push(t->left);
			c.x = f.x - off / 2;
			c.y = f.y + 1;
			LocationQ.Push(c);
		}
		if (t->right)
		{
			BTNodeQ.Push(t->right);
			c.x = f.x + off / 2;
			c.y = f.y + 1;
			LocationQ.Push(c);
		}
	}
	cout << endl;
}
#endif