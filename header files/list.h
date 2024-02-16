#ifndef LIST_H
#define LIST_H
template<class T>
class List
{
	struct Node
	{
		T data;
		Node *prev,*next;
		Node(const T &d=T(),Node *p=0,Node *n=0):data(d),prev(p),next(n){}
	};
	int size;
	Node *head;
	Node *tail;
	void Init() { size=0; head=new Node; tail=new Node; head->next=tail; tail->prev=head; }
public:
	class const_iterator
	{
	protected:
		Node*current;
		T &Retrieve()const{ return current->data; }
		const_iterator(Node *p):current(p){} //转换构造
		friend class List<T>;
	public:
		const_iterator():current(0){} //默认构造
		const T &operator*()const{ return Retrieve(); }
	//自增自减
		const_iterator &operator++() //前++
		{
			current=current->next;
			return *this;
		}
		const_iterator operator++(int) //后++
		{
			const_iterator old=*this;
			++(*this);
			return old;
		}
		const_iterator &operator--() //前--
		{
			current - current->prev;
			return *this;
		}
		const_iterator operator--(int) //后--
		{
			const_iterator old=*this;
			--(*this);
			return old;
		}
		//关系运算
		bool operator==(const const_iterator &itr)const{ return current==itr.current; }
		bool operator!=(const const_iterator &itr)const{ return current !=itr.current; }
	};
	class iterator:public const_iterator
	{
	protected:
		iterator(Node *p):const_iterator(p){} //转换构造
		friend class List<T>;
	public:
		iterator(){} //默认构造
		T &operator*() { return const_iterator::Retrieve(); }
		const T &operator*() const{ return const_iterator::operator*(); }
	//自增自减
		iterator &operator++() //前++
		{
			this->current=this->current->next;
			return *this;
		}
		iterator operator++(int) //后++
		{
			iterator old=*this;
			++(*this);
			return old;
		}
		iterator &operator--() //前--
		{
			this->current=this->current->prev;
			return *this;
		}
		iterator operator--(int) //后--
		{
			iterator old=*this;
			--(*this);
			return old;
		}
	};
	List() { Init(); } //默认构造
	List(const List<T> &l) { Init(); *this=l; } //复制构造
	~List() { Clear(); delete head; delete tail; } //析构
	const List<T> &operator=(const List<T> &l); //复制构造
	int Empty()const{ return size==0; }
	int Size()const{ return size; }
	const_iterator Begin()const{ return const_iterator(head->next); } //指向元素首结点
	iterator Begin() { return iterator(head->next); }
	const_iterator End()const{ return const_iterator(tail); } //指向链表尾结点
	iterator End() { return iterator(tail); }
	iterator Erase(iterator itr); //删除迭代器指向的结点
	void PopFront() { Erase(Begin()); } //删除元素首结点
	void PopBack() { Erase(--End()); } //删除元素尾结点
	void Clear() { while (!Empty()) PopFront(); } //清表
	iterator Insert(iterator itr,const T &item); //在迭代器位置插入
	void PushBack(const T &item) { Insert(End(),item); } //在链表尾节点插入
	void PushFront(const T &item) { Insert(Begin(),item); } //前插
	T &Front() { return *Begin(); } //返回首元素的引用
	const T &Front() const{ return *Begin(); } //返回首元素的常量型引用
	T &Back() { return *--End(); } //返回尾元素的引用
	const T &Back() const{ return *--End(); } //返回尾元素的常量型引用
};
template<class T>
typename List<T>::iterator List<T>::Erase(iterator itr)
{
	Node*p=itr.current;
	iterator re(p->next);
	p->prev->next=p->next;
	p->next->prev=p->prev;
	delete p;
	--size;
	return re;
}
template<class T>
typename List<T>::iterator List<T>::Insert(iterator itr,const T &item)
{
	Node*p=itr.current;
	p->prev->next=new Node(item,p->prev,p);
	p->prev=p->prev->next;
	++size;
	return iterator(p->prev);
}
template<class T> //复制赋值
const List<T> &List<T>::operator=(const List<T> &l)
{
	Clear(); //清表
	const_iterator first=l.Begin(),last=l.End();
	for (; first !=last; ++first)
		PushBack(*first);
	return *this;
}
template<class T> //链表逆置
void InvertList(List<T> &L)
{
	typename List<T>::iterator first=L.Begin();
	typename List<T>::iterator last=L.End();
	typename List<T>::iterator next=first;
	++next;
	if(L.Size()>=1)
		while (next !=last)
		{
			L.PushFront(*next);
			L.Erase(next);
			next=first;
			++next;
		}
}
#endif
