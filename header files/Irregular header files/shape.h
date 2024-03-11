#ifndef SHAPE_H
#define SHAPE_H
#include<iostream>
using namespace std;
const double PI = 3.1415926; //外部对象，对所有类可见
class Shape //抽象基类
{
public:
	virtual double Area()const = 0; //面积计算接口
	virtual void Output()const = 0; //面积输出接口
};

class Triangle:public Shape //三角形
{
	double bottom;
	double height;
	double Area()const{ return bottom  *height / 2; }
public:
	Triangle(double b = 0,double h = 0):bottom(b),height(h){}
	~Triangle(){}
	void Output()const{ cout << Area() << endl; }
};

class Rectangle:public Shape //矩形
{
	double length;
	double width;
	double Area()const{ return length  *width; }
public:
	Rectangle(double l = 0,double w = 0):length(l),width(w) {}
	~Rectangle(){}
	void Output()const{ cout << Area() << endl; }
};

class Trapezoide:public Shape //梯形
{
	double top;
	double bottom;
	double height;
	double Area()const{ return(top + bottom)  *height / 2; }
public:
	Trapezoide(double t = 0,double b=0,double h=0):top(t),bottom(b),height(h){}
	~Trapezoide(){}
	void Output()const{ cout << Area() << endl; }
};

class Circle: public Shape //圆形
{
	double radius;
	double Area()const{ return PI  *radius  *radius; }
public:
	Circle(double r = 0):radius(r) {}
	~Circle() {}
	void Output()const{ cout << Area() << endl; }
};
#endif