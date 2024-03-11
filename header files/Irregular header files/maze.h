#ifndef MAZE_H
#define MAZE_H
#include<stdlib.h>
#include<iostream>
using namespace std;
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
	static int d[4][2]={{1,0},{0,1},{-1,0},{0,-1}}; //表示可能移动方向的数据，表示向右、向下、向左、向上
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