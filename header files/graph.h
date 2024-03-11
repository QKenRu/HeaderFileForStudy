#ifndef GRAPH_H
#define GRAPH_H
#include"../../AAAPublicHeaderFile/list.h"
#include"../../AAAPublicHeaderFile/vector.h"
#include"../../AAAPublicHeaderFile/queue.h"
#include"../../AAAPublicHeaderFile/heap.h"
#include<float.h>
#include<fstream>
#include<optional>
#include<iostream>
using namespace std;
bool operator==(const optional<double> &a,const optional<double> &b)
{
	if(!a.has_value() && !b.has_value())
	{ //等式两边都没有值时，默认两边相等
		return true;
	}
	else if(a.has_value() && b.has_value())
	{
		return a.value()==b.value();
	}
	else
	{
		return false;
	}
}
bool operator!=(const optional<double> &a,const optional<double> &b)
{
	if(!a.has_value() && !b.has_value())
	{ //等式两边都没有值时，默认两边相等
		return false;
	}
	else if(a.has_value() && b.has_value())
	{
		return a.value()!=b.value();
	}
	else
	{ //一边有值一边无值默认不相等
		return true;
	}
}
bool operator>(const optional<double> &a,const optional<double> &b)
{
	if(!a.has_value() && !b.has_value())
	{ //等式两边都没有值时，默认两边相等
		return false;
	}
	else if(a.has_value() && b.has_value())
	{ //等式两边有值
		return a.value() > b.value();
	}
	else if(a.has_value() && !b.has_value())
	{ //左式有值右式无值，无值视为无穷大，即右式大
		return false;
	}
	else if(!a.has_value() && b.has_value())
	{ //左式无值右式有值，左式大
		return true;
	}
	else
	{
		throw "Operator '>' occured an error.";
	}
}
bool operator>=(const optional<double> &a,const optional<double> &b)
{
	if(!a.has_value() && !b.has_value())
	{ //等式两边都没有值时，默认两边相等
		return false;
	}
	else if(a.has_value() && b.has_value())
	{ //等式两边有值
		return a.value() >= b.value();
	}
	else if(a.has_value() && !b.has_value())
	{ //左式有值右式无值，无值视为无穷大，即右式大
		return false;
	}
	else if(!a.has_value() && b.has_value())
	{ //左式无值右式有值，左式大
		return true;
	}
	else
	{
		throw "Operator '>=' occured an error.";
	}
}
bool operator<(const optional<double> &a,const optional<double> &b)
{
	if(!a.has_value() && !b.has_value())
	{ //等式两边都没有值时，默认两边相等
		return false;
	}
	else if(a.has_value() && b.has_value())
	{ //等式两边有值
		return a.value() < b.value();
	}
	else if(a.has_value() && !b.has_value())
	{ //左式有值右式无值，无值视为无穷大，即左式小
		return true;
	}
	else if(!a.has_value() && b.has_value())
	{ //左式无值右式有值，右式大
		return false;
	}
	else
	{
		throw "Operator '<' occured an error.";
	}
}
bool operator<=(const optional<double> &a,const optional<double> &b)
{
	if(!a.has_value() && !b.has_value())
	{ //等式两边都没有值时，默认两边相等
		return false;
	}
	else if(a.has_value() && b.has_value())
	{ //等式两边有值
		return a.value() <= b.value();
	}
	else if(a.has_value() && !b.has_value())
	{ //左式有值右式无值，无值视为无穷大，即左式小
		return true;
	}
	else if(!a.has_value() && b.has_value())
	{ //左式无值右式有值，右式大
		return false;
	}
	else
	{
		throw "Operator '<=' occured an error.";
	}
}
optional<double> operator+(const optional<double> &a,const optional<double> &b)
{
	if(!a.has_value() || !b.has_value())
	{ //任意一边无值，计算结果无值
		return nullopt;
	}
	else if(a.has_value() && b.has_value())
	{ //两边有值，正常计算
		return a.value()+b.value();
	}
	else
	{
		throw "Operator '+' occured an erro.";
	}
}
struct PathData
{ //用于最小生成树算法的一种结点结构
	int start,dest; //边的起点和终点的下标
	optional<double> cost; //权
	operator optional<double>()const
	{ //成员转换函数，用于比较运算
		if(cost.has_value())
		{
			return cost.value();
		}
		else
		{
			return nullopt;
		}
	}
};

template<class T>
class Graph
{
	struct Edge
	{ //边结点数据结构
		int dest; //边的终点下标
		double cost; //边的权
		operator int() {return dest;} //成员转换
	};
	Vector<T> vt; //向量类对象存储顶点
	List<Edge> *el; //指向边链表边数组的指针
	optional<double> GetCost(int s,int e)const; //根据顶点下标读取边的权
	void DFS(List<T> &L,int id,bool *visited)const; //图的深度优先遍历（私有方法）
public:
	explicit Graph(int max=100):vt(max){el=new List<Edge>[max];} //默认构造函数
	virtual ~Graph(){delete []el;} //析构函数
	
	int SizeV()const{return vt.Size();} //取顶点数
	int SizeE()const; //取边数
	int InDegree(int id)const; //求某顶点的入度
	int OutDegree(int id)const {return el[id].Size();} //求某顶点的出度

	int FindV(const T &item)const; //取顶点下标
	void GetVertexItem(T &x,int id)const; //取下标为id的顶点，存储到元素x中
	optional<double> GetCost(const T &v1,const T &v2)const; //根据顶点元素读取边的权
	
	void InsertV(const T &item){vt.PushBack(item);} //插入顶点
	bool InsertE(const T &v1,const T &v2,double w); //插入边

	void BFS(List<T> &L,const T &v)const; //图的广度优先遍历
	void DFS(List<T> &L,const T &v)const; //图的深度优先遍历（公有方法）
	
	bool Prim(const T &v,Vector<PathData> &vt)const; //最小生成树——Prim算法
	bool Kruskal(Vector<PathData> &vt)const; //最小生成树——Kruskal算法

	bool Dijkstra(const T &v,Vector<optional<double>> &dist,Vector<int> &prefix)const; //最短路径问题——Dijkstra算法
	bool BellmanFord(const T &src,Vector<optional<double>> &dist,Vector<int> &prefix); //最短路径问题——Bellman-Ford算法

	bool TopologicalSort(Vector<int> &tp)const; //拓扑序列算法

	void CriticalPath(Vector<double> &ve,Vector<double> &vl)const; //关键路径算法

	void ReadGraph(const char *filename); //从磁盘文件读取图的数据
	void WriteGraph(const char *filename); //从磁盘文件写入图的数据

	void Output()const; //输出到显示器

};

template<class T>
int Graph<T>::SizeE()const
{ //取边数
	int n=vt.Size(); //取顶点个数
	int counter=0; //累加器
	for(int i=0;i<n;++i)
	{
		counter+=el[i].Size(); //累计每个边链表长度
	}
	return counter;
}

template<class T>
int Graph<T>::InDegree(int id)const
{ //求某顶点的入度
	int counter=0; //计数器
	int n=SizeV(); //顶点总数
	for(int i=0;i<n;++i)
	{
		typename List<Edge>::const_iterator first=el[i].Begin();
		typename List<Edge>::const_iterator last=el[i].End();
		for(;first!=last;++first)
		{
			if((*first).dest==id)
			{
				++counter;
				break;
			}
		}
	}
	return counter;
}

template<class T>
int Graph<T>::FindV(const T &item)const
{ //取顶点的下标
	int n=SizeV();
	for(int i=0;i<n;++i)
	{
		if(vt[i]==item)
		{
			return i;
		}
	}
	cout<<"The vertex for element "<<item<<" does not exist."<<endl;
	return -1;
}

template<class T>
void Graph<T>::GetVertexItem(T &x,int id)const
{ //取下标为id的顶点，存储到x中
	if(id<0||id>=SizeV())
	{
		cout<<"The vertex of id "<<id<<" does not exist."<<endl;
		return;
	}
	x=vt[id];
}

template<class T>
optional<double> Graph<T>::GetCost(const T &v1,const T &v2)const
{ //根据顶点元素读取边的权（公有方法）
	int s=FindV(v1);
	int e=FindV(v2);
	return GetCost(s,e); //根据顶点下标读取边的权（私有方法）
}
template<class T>
optional<double> Graph<T>::GetCost(int s,int e)const
{ //根据顶点下标读取边的权（私有方法）
		typename List<Edge>::const_iterator first=el[s].Begin();
		typename List<Edge>::const_iterator last=el[s].End();
		for(;first!=last;++first)
		{
			if((*first).dest==e)
			{
				return (*first).cost;
			}
		}
		return nullopt;
}

template<class T>
bool Graph<T>::InsertE(const T &v1,const T &v2,double w)
{ //插入边
	int s=FindV(v1);
	int e=FindV(v2); //确定边的始点和终点的下标
	if(s==-1 || e==-1 || s==e)
	{
		cout<<"Vertex "<<v1<<" or "<<v2<<" doesn't exist, or they are the same vertex."<<endl;
		return 0;
	}
	Edge ed; //边的结构对象
	ed.dest=e;
	ed.cost=w; //给边的结构对象复制
	el[s].PushBack(ed); //尾插到边链表
	return 1;
}

template<class T>
void Graph<T>::ReadGraph(const char *filename)
{ //从磁盘文件读取图的数据
	fstream infile;
	infile.open(filename,ios::in);
	if(!infile)
	{
		cout<<"Can't open "<<filename<<endl;
		return;
	}
	char str[40];
	int n;
	T s,e;
	double w;
	infile>>str>>n;
	for(int i=0;i<n;++i)
	{
		infile>>s;
		InsertV(s);
	}
	infile>>str>>n;
	for(int i=0;i<n;++i)
	{
		infile>>s>>e>>w;
		InsertE(s,e,w);
	}
	infile.close();
}
template<class T>
void Graph<T>::WriteGraph(const char *filename)
{ //把图的数据输出到磁盘文件
	fstream outfile;
	outfile.open(filename,ios::out); //打开磁盘文件
	if(!outfile)
	{
		cout<<"Can't open "<<filename<<endl;
		return;
	}
	int n=SizeV();
	typename List<Edge>::const_iterator first,last;
	for(int i=0;i<n;++i)
	{
		outfile<<i<<'-'<<vt[i]<<':'; //输出顶点下标和元素
		first=el[i].Begin(), last=el[i].End();
		for(;first!=last;++first)
		{ //输出边链表
			outfile<<'('<<(*first).dest<<' '<<(*first).cost<<')'<<' ';
		}
		outfile<<endl;
	}
	outfile.close();
}

template<class T>
void Graph<T>::Output()const
{ //把图的数据输出到显示器
	int n=SizeV();
	typename List<Edge>::const_iterator first,last;
	for(int i=0;i<n;++i)
	{
		cout<<i<<'-'<<vt[i]<<':'; //输出顶点下标和元素
		first=el[i].Begin(),last=el[i].End();
		for(;first!=last;++first)
		{
			cout<<'('<<(*first).dest<<' '<<(*first).cost<<')'<<' ';
		}
		cout<<endl;
	}
}

template<class T>
void Graph<T>::BFS(List<T> &L,const T &v)const
{ //图的广度优先遍历
	int id=FindV(v); //取顶点下标
	if(id==-1)
	{
		return; //FindV()会有报错提示，此处不需要报错
	}
	int n=SizeV();
	bool *visited=new bool[n](); //标志数组，初始化元素值为0，记录结点是否被访问过
	
	Queue<int>Q;
	Q.Push(id); //把始点插入队列
	visited[id]=1; //做被访问过的标志
	typename List<Edge>::const_iterator first, last; //边链表迭代器	
	while(!Q.Empty()) //若队列不为空，从队列取出一个顶点访问，然后遍历该顶点的边链表，若其邻接点未被访问，就插入队列，同时做被访问过的标志
	{
		id=Q.Pop(); //从队列取出顶点下标
		L.PushBack(vt[id]); //把广度优先队列存入链表并作为参数返回
		first=el[id].Begin(),last=el[id].End(); //指向边链表的首、尾结点
		for(;first!=last;++first)
		{ //遍历边链表，查找未被访问的邻接点
			if(visited[(*first).dest]==0) //若邻接点未被访问
			{
				Q.Push((*first).dest); //邻接点下标入队列
				visited[(*first).dest]=1; //做被访问过的标志
			}
		}
	}
	delete []visited;
}

template<class T>
void Graph<T>::DFS(List<T> &L,const T &v)const
{ //图的深度优先遍历（公有方法）
	int id=FindV(v);
	if(id==-1)
	{
		cout<<"Vertex "<<v<<" doesn't exist.";
		return;
	}
	int n=SizeV();
	bool *visited=new bool[n](); //标志数组
	DFS(L,id,visited);
}
template<class T>
void Graph<T>::DFS(List<T> &L,int id,bool *visited)const
{ //图的深度优先遍历（私有方法）
	L.PushBack(vt[id]); //访问始点
	visited[id]=1; //做访问标记
	typename List<Edge>::const_iterator first,last; //边链表迭代器
	first=el[id].Begin(),last=el[id].End(); //指向边链表的首、尾结点
	for(;first!=last;++first)
	{ //依次以未访问过的邻接点为始点，进行深度优先遍历
		if(visited[(*first).dest]==0)
		{
			DFS(L,(*first).dest,visited);
		}
	}
}

template<class T>
void OutputList(const List<T> &L)
{ //输出各种遍历方式存储在链表L的结果
	typename List<T>::const_iterator first=L.Begin(),last=L.End();
	for(;first!=last;++first)
	{
		cout<<*first<<'\t';
	}
	cout<<endl;
}

template<class T>
bool Graph<T>::Prim(const T &v,Vector<PathData> &vt)const
{ //最小生成树算法——Prim算法
    //由始点组成最初的入选子网，其余顶点组成候选点集，把候选边集存入PathData结构数组
	int nv=SizeV(); //顶点数
	PathData *E=new PathData[nv-1]; //根据边数建立数组，最小生成树的边数等于顶点数减1
	int s=FindV(v); //取始点索引
	if(s==-1)
	{
		cout<<"Vertex "<<v<<" doesn't exist."<<endl;
		return 0;
	}
	PathData item;
	optional<double> cost;
	int id=0,n=0; //索引
	for(int e=0;e<nv;++e)
	{ //s和e分别是边的始点和终点索引
		if(e!=s)
		{
			item.start=s;
			item.dest=e;
			item.cost=GetCost(s,e);
			E[id++]=item;
			++n;
		}
	} //在候选边集中选定一条权最小的加入到入选子网，实现这一操作的方法是将候选边集调整为小根堆，小根堆首元素就是权值最小的侯选边
	BuildHeap(E,n); //对候选边集键小根堆
	//更新侯选边集，以入选子网的新顶点作为始点、候选点集的顶点为终点所构成的边与同一终点的原侯选边比较，用边权小的替换边权大的
	int i,j,counter=0; //计数器，记录最小生成树的边数
	for(i=0;i<n;++i)
	{ //更新候选边集
		if(E[0].cost.has_value())
		{ //若候选边集的最小者存在，计数器加1
			++counter;
		}
		s=E[0].dest; //取新的入选集顶点
		for(j=1;j<n-i;++j)
		{ //更新候选边集
			cost=GetCost(s,E[j].dest);
			if(E[j].cost>cost)
			{
				E[j].cost=cost;
				E[j].start=s;
			}
		}
		item=E[0]; //候选边集的首尾元素交换，item这里用来当作临时变量
		E[0]=E[n-1-i]; //id-1-i是删除后的尾元素下标
		E[n-1-i]=item;
		BuildHeap(E,n-1-i); //重建小根堆
	}
	//如果计时器的值等于图的顶点个数减1，说明已生成最小生成树，函数返回值为1，否则为0
	vt.Clear(); //清空向量对象，用于存储最小生成树的结果
	if(counter==nv-1)
	{
		for(i=0;i<counter;++i)
		{
			vt.PushBack(E[i]);
		}
		delete []E;
		return 1;
	}
	delete []E;
	cout<<"Prim algorithm failed in generating minimal spanning tree."<<endl;
	return 0;
}
template<class T>
bool Graph<T>::Kruskal(Vector<PathData> &vt)const
{ //最小生成树——Kruskal算法
	//由n个顶点分别组成n个只有单个顶点的连通子网，这时并查集(数组DS)的每个元素值是-1
	int nv=SizeV(); //最小生成树的顶点个数
	int *DS=new int[nv]; //并查集
	int i,j;
	for(i=0;i<nv;++i)
	{ //初始化并查集
		DS[i]=-1;
	}
	//把每一条边的信息插入小根堆
	optional<double> cost;
	PathData item;
	Heap<PathData> H; //小根堆
	for(i=0;i<nv;++i)
	{
		for(j=i+1;j<nv;++j)
		{
			cost=GetCost(i,j);
			if(cost.has_value())
			{
				item.start=i; //索引小的顶点表示始点
				item.dest=j; //索引大的顶点表示终点
				item.cost=cost.value();
				H.Insert(item); //插入小根堆
			}
		}
	}
	//从堆中提取并删除的一条边（这条边的权在小根堆一定是最小的）；若始点和终点属于不同的连通子网（即它们所属的连通子网的根不同），
	//就将它们连接城一个连通子网（根大的子网并入跟小的）；然后把这条边的信息保存起来，作为最小生成树的边
	int id=0,counter=0;
	PathData *E=new PathData[nv-1]; //最小生成树的边数为顶点数减1
	while(!H.Empty())
	{
		H.Remove(item); //删取（提取后删除）堆的首元素
		i=item.start;
		while(DS[i]>=0) //查找边的始点在连通子网中的根
		{ //DS[i]若小于0，表示序号为i的顶点是一个连通子网的根，绝对值是这个连通子网的顶点个数；若大于0，DS[i]=j表示序号为i,j(j<i)的顶点在一个连通子网中
			i=DS[i];
		}
		j=item.dest;
		while(DS[j]>=0) //查找边的终点在连通子网中的根
		{
			j=DS[j];
		}
		if(i!=j)
		{ //若边的始点与终点属于不同的连通子网，则合并
			if(i<j)
			{
				DS[i]+=DS[j]; //将两个连通子网的顶点个数加到整合后的连通子网的顶点个数DS[i]中
				DS[j]=i; //修改被吞并的连通子网的根
			}
			else
			{
				DS[j]+=DS[i];
				DS[i]=j;
			}
			E[id++]=item; //保存最小生成树的边
			++counter;
		}
	}
	delete []DS;
	vt.Clear(); //清空向量对象，用于存储最小生成树的结果
	if(counter==nv-1)
	{
		for(i=0;i<counter;++i)
		{
			vt.PushBack(E[i]);
		}
		delete []E;
		return 1;
	}
	delete []E;
	cout<<"Kruskal algorithm failed in generating minimal spanning tree."<<endl;
	return 0;
}
void MSTOutput(const Vector<PathData> &vt)
{ //最小生成树输出函数
	int n=vt.Size();
	for(int i=n-1;i>=0;--i)
	{
		std::cout<<'('<<vt[i].start<<"-"<<vt[i].dest<<','<<vt[i].cost.value()<<')'<<std::endl;
	}
	return;
}

template<class T>
bool Graph<T>::Dijkstra(const T &v,Vector<optional<double>> &dist,Vector<int> &prefix)const
{
	int nv=SizeV(); //顶点数
	PathData *E=new PathData[nv-1]; //候选路径集的边数为nv-1
	int i,j;
	dist.Clear(); //清空向量对象
	prefix.Clear();
	for(i=0;i<nv-1;++i)
	{ //向量对象初始化为0，元素个数size扩大为nv
		dist.PushBack(0);
		prefix.PushBack(0);
	}
	int s=FindV(v); //寻找始点的下标
	if(s==-1)
	{
		return 0;
	}
	dist[s]=0; //从源点到自身路径长度为0
	prefix[s]=-1; //源点无前驱
	PathData item;
	optional<double> cost;
	int id=0,n=0; //n用于记录候选路径数
	for(int e=0;e<nv;++e)
	{ //s和e分别是候选路径的始点和终点索引
		if(e!=s)
		{
			item.start=s;
			item.dest=e;
			item.cost=GetCost(s,e);
			cost=GetCost(s,e);
			E[id++]=item;
			++n;
			dist[e]=item.cost;
			prefix[e]=(cost.has_value() ? s : -1);
		}
	}
	BuildHeap(E,n); //对候选路径集建小根堆
	int counter=0;
	optional<double> distBLMAX=nullopt;
	for(int i=0;i<n;++i)
	{
		if(E[0].cost<distBLMAX)
		{ //nullopt在比较运算符重载中被定义为最大，distBL_MAX也小于nullopt
			++counter;
		}
		s=E[0].dest;
		for(j=1;j<n-i;++j)
		{
			cost=GetCost(s,E[j].dest);
			if(E[j].cost>E[0].cost+cost)
			{
				E[j].cost=E[0].cost+cost;
				E[j].start=s;
				dist[E[j].dest]=E[j].cost;
				prefix[E[j].dest]=s;
			}
		}
		item=E[0];
		E[0]=E[n-1-i];
		E[n-1-i]=item;
		BuildHeap(E,n-1-i); //重建小根堆
	}
	delete []E;
	return counter==nv-1 ? 1 : 0;
}
template<class T>
bool Graph<T>::BellmanFord(const T &source,Vector<optional<double>> &dist,Vector<int> &prefix)
{
	int nv=SizeV();
	int ne=SizeE();
	int s,e,src;
	src=FindV(source); //寻找始点下标
	if(src==-1)
	{
		return 0;
	}
	PathData *item=new PathData[ne];
	Vector<optional<double>>backupDist;
	optional<double> cost;
	for(int i=0;i<nv-1;++i)
	{ //向量对象初始化为0，元素个数size扩大为nv
		dist.PushBack(0);
		backupDist.PushBack(0);
		prefix.PushBack(0);
	}
	//初始化：将除源点外的所有顶点的最短距离估计值 dist[v] ← +∞, dist[s] ←0;
	for(int i=0;i<nv;++i)
	{
		dist[i]=nullopt; //nullopt在比较运算符重载下为最大，大于DBL_MAX
		backupDist[i]=nullopt;
	}
	dist[src]=0; //始点到自己的距离为0
	backupDist[src]=0;
	prefix[src]=-1; //始点的前缀为-1
	//迭代求解：反复对边集E中的每条边进行松弛操作，使得顶点集V中的每个顶点v的最短距离估计值逐步逼近其最短距离；（运行nv-1次）
	int k=0;
	for(int i=0;i<nv;++i)
	{ //初始化边集item
		for(int j=0;j<nv;++j)
		{
			if(GetCost(i,j)!=nullopt)
			{
				item[k].start=i;
				item[k].dest=j;
				item[k].cost=GetCost(i,j);
				if(i==src)
				{
					dist[j]=item[k].cost;
					prefix[j]=i;
				}
				++k;
			}
		}
	}
	for(int i=0;i<nv;++i)
	{ //备份边集防串联。如果不备份上一次的item数组的话，最短距离变成了2。内层循环只迭代了一次，但是在更新的过程中会发生”串联”。比如说先更新了2号点，然后我们用2号点更新了3号点距离起点的距离，
	  //这样就发生了”串联”，3号点不能被2号点更新，这样就不满足最多不经过x条边的要求了
		for(int j=0;j<nv;++j)
		{
			backupDist[j]=dist[j];
		}
		for(int j=0;j<ne;++j)
		{ //边集item和备份边集backItem的边都是有值的
			s=item[j].start;
			e=item[j].dest;
			if(dist[e] > backupDist[s]+item[j].cost)
			{ //松弛操作
				dist[e]=backupDist[s]+item[j].cost;
				prefix[e]=s;
			}
		}
	}
	//检验负权回路：判断边集E中的每一条边的两个端点是否收敛。如果存在未收敛的顶点，则算法返回false，表明问题无解；否则算法返回true，并且从源点可达的顶点v的最短距离保存在dist[v]中。
	bool hasNegativeLoop=false;
	for(int i=0;i<ne;++i)
	{
		s=item[i].start;
		e=item[i].dest;
		cost=item[i].cost;
		if(dist[s].has_value() && dist[s]+cost < dist[e])
		{
			hasNegativeLoop=true;
			break;
		}
	}
	if(hasNegativeLoop)
	{
		cout<<"Graph has negative edge loops."<<endl;
		return 0;
	}
	return 1;
}
template<class T>
void SPPOutput(const Graph<T> &G,const Vector<optional<double>> &dist,const Vector<int> &prefix)
{
	int n=G.SizeV();
	T v;
	int f;
	int *stack=new int[n];
	int size; //记录栈元素个数
	for(int i=0;i<n;++i)
	{
		if(dist[i].has_value())
		{
			cout<<dist[i].value()<<':';
			size=0; //清空栈
			stack[size++]=i; //把终点压栈
			f=prefix[i]; //取顶点vi在路径上的前一个顶点
			while(f!=-1)
			{
				stack[size++]=f;
				f=prefix[f]; //取前驱顶点
			}
			for(int j=size-1;j>=0;--j)
			{ //弹栈，从始点开始输出
				G.GetVertexItem(v,stack[j]);
				cout<<v;
				if(j>0)
				{ //如果不是路径终点
					cout<<"->";
				}
			}
			cout<<endl;
		}
	}
	delete []stack;
}

template<class T>
bool Graph<T>::TopologicalSort(Vector<int> &tp)const
{ //拓扑序列算法
//建立一个整型数组和一个队列，记录每一个顶点的入度，把入度为0的顶点插入队列
	int nv=SizeV(); //顶点总数
	int *ID=new int[nv];
	int id;
	Queue<int> Q;
	for(id=0;id<nv;++id)
	{
		ID[id]=InDegree(id);
		if(ID[id]==0)
		{ //如果顶点的入度为0
			Q.Push(id);
		}
	}
//若队列不空，则取出一个顶点作为拓扑序列的顶点，同时计数器counter加1，然后以该顶点为始点的边的终点的入队减1。若减1后入度为0，则将该终点插入队列。重复这个步骤直到队列为空
	int i,j;
	tp.Clear(); //清空向量对象
	typename List<Edge>::const_iterator first,last;
	while(!Q.Empty())
	{
		i=Q.Pop();
		tp.PushBack(i); //记录拓扑序列顶点的序号
		first=el[i].Begin();
		last=el[i].End();
		for(;first!=last;++first)
		{ //扫描以拓扑顶点为始点的边链表
			j=(*first).dest;
			--ID[j];
			if(ID[j]==0)
			{
				Q.Push(j);
			}
		}
	}
	delete []ID;
//如果计数器counter的值等于图的顶点总数，则算法成功，否则失败
	int counter=tp.Size();
	return counter==nv?1:0;
}
template<class T>
void TopoOutput(const Graph<T> &g,const Vector<int> &tp)
{ //拓扑序列输出函数
	int nv=tp.Size();
	T v;
	for(int i=0;i<nv;++i)
	{
		g.GetVertexItem(v,tp[i]);
		cout<<v<<' ';
	}
	cout<<endl;
}

template<class T>
void Graph<T>::CriticalPath(Vector<double> &ve,Vector<double> &vl)const
{
	int i,j,k;
	int nv=SizeV();
	Vector<int> tp;
	ve.Clear(); //清空向量对象
	vl.Clear();
	for(int i=0;i<nv;++i)
	{ //向量对象赋值0，元素个数size扩容为nv
		ve.PushBack(0);
		vl.PushBack(0);
	}
	optional<double> temp;
	double min,max;
	if(TopologicalSort(tp))
	{ //选定一个拓扑序列
//按拓扑序列顺序，从前往后计算每个顶点的最早发生时间。具体计算方法：从ve(0)=0开始，每个顶点最早发生时间是在所有以它为终点的入边中，始点的最早发生时间加上权后权后的最大值。
//因为每条有向边的始点和终点在拓扑序列中都是前后排列的，所以计算方法是递推的。
		ve[tp[0]]=0;
		for(k=1;k<nv;++k)
		{
			j=tp[k];
			max=DBL_MIN;
			for(i=0;i<nv;++i)
			{
				temp=GetCost(i,j);
				if(temp.has_value() && (ve[i]+temp.value())>max)
				{
					max=ve[i]+temp.value();
				}
			}
			ve[j]=max;
		}
//按拓扑序列顺序，从后往前计算每个顶点的最迟发生时间。具体计算方法：从vl(nv-1)=ve(nv-1)开始，每个顶点最迟发生时间是在所有以它为始点的出边中，
//终点的最迟发生时间减去权后的最小值。因为每条有向边的始点和终点在拓扑序列中都是前后排列的，所以计算方法是递推的。
		vl[tp[nv-1]]=ve[tp[nv-1]];
		for(k=nv-2;k>=0;--k)
		{
			i=tp[k];
			min=DBL_MAX;
			for(j=0;j<nv;++j)
			{
				temp=GetCost(i,j);
				if(temp.has_value() && (vl[j]-temp.value())<min)
				{
					min=vl[j]-temp.value();
				}
			}
			vl[i]=min;
		}
	}
	return;
}
template<class T>
void CPOutput(const Graph<T> &g,const Vector<double> &ve,const Vector<double> &vl)
{ //关键路径输出函数
	int nv=g.SizeV();
	T vj,vi;
	for(int j=0;j<nv;++j)
	{
		for(int i=0;i<nv;++i)
		{
			g.GetVertexItem(vi,i);
			g.GetVertexItem(vj,j);
			if(g.GetCost(vi,vj)!=nullopt)
			{ //这个输出的是边（活动）的延时（最长可持续时间）
				cout<<'<'<<vi<<','<<vj<<'>'<<"---"<<vl[j]-ve[i]-(g.GetCost(vi,vj)).value()<<endl;
			}
		}
	}
	return;
}

class Maze
{
	char **maze;
	int row,col; //行数和列数。若x和y代表横坐标和纵坐标，那么在二维数组中应该写作a[y][x]，横坐标相当于列，纵坐标相当于行
	int inx,iny,outx,outy; //入口和出口
	void AllPath(int x,int y); //从入口到出口所有路径的私有方法
public:
	explicit Maze(char **m,int row,int col,int inx,int iny,int outx,int outy);
	~Maze();
	void AllPath(){AllPath(inx,iny);} //从入口到出口所有路径的公有方法
	void PrintMaze(); //输出一条路径
};
Maze::Maze(char **m,int row,int col,int inx,int iny,int outx,int outy)
{
	this->row=row,this->col=col;
	this->inx=inx,this->iny=iny;
	this->outx=outx,this->outy=outy;
	maze=new char*[row];
	for(int i=0;i<row;++i)
	{
		maze[i]=new char[col];
	}
	for(int i=0;i<row;++i)
	{
		for(int j=0;j<col;++j)
		{
			maze[i][j]=m[i][j];
		}
	}
}
Maze::~Maze()
{
	for(int i=0;i<row;++i)
	{
		delete []maze[i];
	}
	delete []maze;
}
void Maze::PrintMaze()
{ //输出一条路径
	static int counter=0;
	++counter;
	cout<<"Path "<<counter<<endl;
	for(int i=0;i<row;++i)
	{
		for(int j=0;j<col;++j)
		{
			cout<<maze[i][j]<<' ';
		}
		cout<<endl;
	}
}
void Maze::AllPath(int x,int y)
{ //从入口到出口所有路径的私有方法
	static int d[4][2]={{1,0},{0,1},{-1,0},{0,-1}}; //表示可能移动方向的数据，分别表示向右、向下、向左、向上
	maze[y][x]='*';
	if(y==outy&&x==outx)
	{
		PrintMaze();
		return;
	}
	for(int i=0;i<4;++i)
	{
		if(maze[y+d[i][1]][x+d[i][0]]=='0')
		{ //注意，x和y代表横坐标和纵坐标，那么在二维数组中应该写作a[y][x]，横坐标相当于列，纵坐标相当于行
			AllPath(x+d[i][0],y+d[i][1]);
			maze[y+d[i][1]][x+d[i][0]]='0';
		}
	}
}
#endif