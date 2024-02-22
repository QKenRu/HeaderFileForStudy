#ifndef BINARYTREE_H
#define BTNARYTREE_H
#include"vector.h"
#include"queue.h"
#include"stack.h"
#include"seqlist.h"
#include<iostream>
template<class T>
struct BTNode //二叉树结点
{
	T data; //存储数据元素
	BTNode *left, *right; //指向左右孩子结点的指针
	BTNode(const T &item=T(),BTNode *l=0,BTNode *r=0):data(item),left(l),right(r){} //默认构造
};
template<class T> //层次序列输出
void Level(BTNode<T> *t)
{
	if (t == 0)
		return;
	Queue<BTNode<T>*>Q;
	Q.Push(t);
	while (!Q.Empty())
	{
		t = Q.Pop();
		cout << t->data;
		if (t->left)
			Q.Push(t->left);
		if (t->right)
			Q.Push(t->right);
	}
	cout << endl;
}
struct Location //结点输出位置
{
	int x,y;
};
void Gotoxy(int x,int y) //定位函数
{
	static int indent = 0; //偏移量。事实上indent静态变量在本函数是无用的，因为它不停地被赋值为0
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
void PrintBTree(const BTNode<T> *t,SeqList<int> &value,SeqList<char> &word,int w) //垂直输出二叉树
{
	if (t == 0)
		return;
	int level = 0,off = w / 2; //从0层开始，偏移量是宽度的1/2
	Location f,c;
	Queue<const BTNode<T>*>Q; //存储结点指针
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
		if (!t->left && !t->right)
		{
			for (int i = 0; i < value.GetSize(); ++i)
				if ((t->data) == value.GetData(i))
					cout << word.GetData(i);
		}
		else
			cout << t->data;
		if (f.y != level) //除跟外，每层首结点输出后，都修改层数和偏移量
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
template<class T> //由顺序存储生成二叉链式存储
BTNode<T> *MakeBTree(const T *p,int n)
{
	if (n <= 0)
		return 0;
	Queue<BTNode<T>*>Q;
	BTNode<T> *t = new BTNode<T>(p[0]); //生成根指针
	BTNode<T> *f, *c; //双亲和孩子指针
	Q.Push(t); //根指针入队
	int i = 0;
	while (!Q.Empty())
	{
		f = Q.Pop(); //一个结点指针出队
		if (2*i + 1 < n && p[2*i+1] != T() ) //如果有左孩子
		{
			c = new BTNode<T>(p[2*i+1]); //生成左孩子结点
			f->left = c; //与双亲连接
			Q.Push(c); //左孩子指针入队
		}
		if (2*i + 2 < n && p[2*i+2] != T() ) //如果有右孩子
		{
			c = new BTNode<T>(p[2*i+2]); //生成右孩子结点
			f->right = c; //与双亲连接
			Q.Push(c); //右孩子指针入队
		}
		++i;
		while (i < n && p[i] == T()) //查找下一个非0元素
			++i;
	}
	return t;
}
template<class T>
void Preorder(const BTNode<T> *t) //前序遍历递归函数
{
	if (t == 0)
		return;
	cout << t->data << '\t'; //访问根
	Preorder(t->left); //前序遍历左子树
	Preorder(t->right); //断点(1)，前序遍历右子树
} //断点(2)
/*前序遍历递归函数另一个版本，含有if子句，遍历的左、右子树不能为空
template<class T>
void Preorder(const BTNode<T> *t)
{
	if(t==0)
		return;
	cout<<t->data<<'\t';
	if(t->left)
		Preorder(t->left);
	if(t->right)  //断点(1)
		Preorder(t->right);
} //断点(2)
*/
template<class T>
void SimPreoder(const BTNode<T> *t) //前序遍历迭代函数
{
	if (t == 0)
		return;
	Stack<const BTNode<T>*>S; //用户栈
	while (t || !S.Empty())
		if (t)
		{
			cout << t->data << '\t'; //访问结点
			if (t->right)
				S.Push(t->right); //右孩子指针入栈保存
			t = t->left; //提取左孩子指针
		}
		else
			t = S.Pop(); //右孩子指针出栈
}
template<class T> //快速排序划分
int Partition(T *p,int left,int right) //对p[left:right]划分，返回根的索引
{
	T root = p[left]; //提取数据首元素作为根，留出空位
	while (left != right)
	{
		while (p[right] >= root && right > left) //在剩余的数据元素中，从右往左遍历，找到第一个小于根的元素停止。将该元素移到上一位的空位，留出新的空位
			--right;
		if (right > left)
			p[left++] = p[right];
		while (p[left] <= root && left < right) //在没有访问的数据元素中，从左往右遍历，找到第一个大于根的元素停止。将该元素移到上一位的空位，留出新的空位
			++left;
		if (left < right)
			p[right--] = p[left];
	}
	p[left] = root; //重复以上步骤，直到所有元素都访问过，只剩一个空位。将根移到空位，返回根的索引
	return left;
}
template<class T>
void QuickSort(T *p,int left,int right) //快速排序
{
	if (left >= right)
		return;
	int m = Partition(p,left,right); //对数组划分
	QuickSort(p,left,m - 1); //对左子树快速排序
	QuickSort(p,m + 1,right); //对右子树快速排序
}
template<class T>
void QuickSort(T *p,int n) //快速排序引擎
{
	QuickSort(p,0,n - 1); //调用快速排序递归算法
}
template<class T>
void Inorder(const BTNode<T> *t) //中序遍历递归算法 
{
	if (t == 0)
		return;
	Inorder(t->left); //中序遍历左子树
	cout << t->data << '\t'; //断点(!)
	Inorder(t->right); //中序遍历右子树
} //断点(2)
/*中序遍历递归函数还有另一个版本，含有if子句，遍历的左、右子树不能为空，即递归过程直到指针所指向的结点没有左、右子树0为止，开始回溯
template<class T>
void Inorder(const BTNode<T> *t)
{
	if(t==0)
		return;
	if(t->left)
		Inorder(t->left); //中序遍历左子树
	cout<<t->data<<'\t'; //断点(!)
	if(t->right)
		Inorder(t->right); //中序遍历右子树
} //断点(2)
*/
template<class T>
void SimInorder(const BTNode<T> *t) //中序遍历迭代算法
{
	if (t == 0)
		return;
	Stack<const BTNode *> S; //用户栈
	while(t||!S.Empty())
		if (t)
		{
			S.Push(t); //结点指针入栈保存
			t = t->left; //提取左孩子指针
		}
		else
		{
			t = S.Pop(); //结点指针出栈
			cout << t->data << '\t'; //访问结点
			t = t->right; //提取右孩子指针
		}
}
void Hanoi(int n,char S,char M,char E) //汉诺塔问题求解
{ //用四元组(n,起始位置,中间位置,结束位置)表示n阶汉诺塔问题。如果阶数大于1，它就有左右孩子；它和左孩子的关系是阶数差1，中间位置和结束位置交换；
  //它和右孩子的关系是阶数差1，起始位置和中间位置交换。这棵树称为汉诺塔状态树。n阶汉诺塔问题递归求解模型是二叉树中序遍历递归算法。
	if (n <= 0)
		return;
	if (n > 1)
		Hanoi(n - 1,S,E,M); //中间位置和结束位置交换
	cout << n << ':' << S << "->" << E << endl; //把第n号盘子从起始位置直接移到结束位置
	if (n > 1)
		Hanoi(n - 1,M,S,E); //起始位置和中间位置交换
}
template<class T>
void Postorder(const BTNode<T> *t) //后序遍历递归算法
{
	if (t == 0)
		return;
	Postorder(t->left); //后序遍历左子树
	Postorder(t->right); //断点(1)，后序遍历右子树
	cout << t->data << '\t'; //断点(2)，输出结点数据元素
}
/*后序遍历递归函数还有另一个版本，含有if子句
template<class T>
void Postorder(const BTNode<T> *t)
{
	if (t == 0)
		return;
	if (t->left)
		Postorder(t->left); //后序遍历左子树
	if (t->right) //断点(1)
		Postorder(t->right); //后序遍历右子树
	cout << t->data << '\t'; //断点(2)
}
*/
template<class T>
void SimPostorder(const BTNode<T> *t) //后序遍历迭代算法
{
	if (t == 0)
		return;
	int tag;
	Stack<int>tagS; //记录结点指针入栈次数，当结点第二次出栈时，访问该结点
	Stack<const BTNode<T>*> S;
	const BTNode<T> *p;
	while(t || !S.Empty())
		if (t)
		{
			S.Push(t);
			tagS.Push(1);
			t=t->left;
		}
		else
		{
			p = S.Pop();
			tag = tagS.Pop();
			if (tag == 1) //第一次出栈
			{
				S.Push(p);
				tagS.Push(2);
				t = p->right;
			}
			else //第二次出栈
				cout << p->data << '\t';
		}
}
template<class T>
BTNode<T> *CopyTree(const BTNode<T> *t) //复制二叉链表的递归算法
{
	if (t == 0)
		return 0;
	BTNode<T> *l = CopyTree(t->left);
	BTNode<T> *r = CopyTree(t->right);
	return new BTNode<T>(t->data,l,r);
}
template<class T>
int Depth(const BTNode<T> *t) //计算二叉树高度
{
	if (t == 0)
		return -1;
	int l = Depth(t->left);
	int r = Depth(t->right);
	return(1 + (l > r ? l: r));
}
template<class T>
void DeleteBTree(BTNode<T> *t) //删除二叉链表的递归算法
{
	if (t == 0)
		return;
	DeleteBTree(t->left);
	DeleteBTree(t->right);
	delete t;
}
template<class T>
BTNode<T> *MakeBTree(const T *p,int size,int i) //生成二叉链表的递归算法
{
	if (size == 0 || i >= size || p[i] == T())
		return 0;
	BTNode<T> *l = MakeBTree(p,size,2  *i + 1);
	BTNode<T> *r = MakeBTree(p,size,2  *i + 2);
	return new BTNode<T>(p[i],l,r);
}
#endif
