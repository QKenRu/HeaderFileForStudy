#ifndef DATEINHERITANCE_H
#define DATEINHERITANCE_H
#include<iostream>
using namespace std;
class Date //基类
{
protected:
	int year,month,day; //保护性成员
public:
	Date():year(2002),month(12),day(13){} //默认构造
	Date(int y,int m,int d):year(y),month(m),day(d){} //一般构造
	virtual void Display()const{ cout << year << '/' << month << '/' << day << endl; }
};
class NewDate:public Date //派生类。派生方式是公有
{
public:
	NewDate(){}
	NewDate(int y,int m,int d):Date(y,m,d){}
	void Display()const{ cout << year << '-' << month << '-' << day << endl; }
};
#endif