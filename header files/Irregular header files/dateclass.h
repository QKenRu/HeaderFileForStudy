#ifndef DATECLASS_H
#define DATECLASS_H
#include<iostream>
using namespace std;
class Date
{
	int year,month,day;
	static const int NoLeapyear[]; //静态数据成员
	bool Leapyear(int y)const{ return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0); }
public:
	Date():year(1),month(1),day(1) {} //默认构造
	Date(int y,int m,int d):year(y),month(m),day(d) {}
	explicit Date(int ndays) { *this = ndays; } //转换构造
	Date &operator=(int ndays); //转换赋值
	operator int() const; //成员转换
	bool Leapyear()const{ return Leapyear(year); }
	friend istream &operator>>(istream &istr,Date &dt);
	friend ostream &operator<<(ostream &ostr,const Date &dt);
	Date &operator++(); //前++
	Date operator++(int); //后++
	Date &operator--(); //前--
	Date operator--(int); //后--
	void SetYear(int y) { year = y; } //成员赋值
	void SetMonth(int m) { month = m; }
	void SetDay(int d) { day = d; }
	int GetYear()const{ return year; } //成员取值
	int GetMonth()const{ return month; }
	int GetDay()const{ return day; }
};
const int Date::NoLeapyear[] = { 31,28,31,30,31,30,31,31,30,31.30,31 }; //平常年

Date &Date::operator=(int ndays) //转换赋值
{
	int n;
	year = month = day = 0;
	year = 1;
	n = Leapyear(year) ? 366: 365; //自公元1年开始，从正整数中扣除整年的天数，每扣除1年，年份加1.
	while (ndays > n)
	{
		ndays -= n;
		++year;
		n = Leapyear(year) ? 366: 365;
	}
	month = 1; //自1月开始，从正整数中扣除整月的天数，每扣除1月，月份加1.
	n = NoLeapyear[month - 1];
	while (ndays > n)
	{
		ndays -= n;
		++month;
		n = NoLeapyear[month - 1];
		if (month == 2 && Leapyear(year))
			++n;
	}
	day = ndays; //剩余的整数就是日
	return *this;
}

Date::operator int() const //成员转换
{
	int i;
	int ndays = 0;
	for (i = 1; i < year; ++i) //从公元1年起累加每一个整年的天数
		ndays += Leapyear(i) ? 366: 365;
	for (i = 1; i < month; ++i) //对日期所属的年份，从1月起累加每个整月的天数。如果包括2月，还要判断是否闰年，以决定是否再加一天
		ndays += NoLeapyear[i - 1];
	if (month > 2 && Leapyear(year))
		++ndays;
	ndays += day; //加上所在月份天数
	return ndays; //返回结果
}

ostream &operator<<(ostream &ostr,const Date &dt) //插入符重载
{
	ostr << dt.year << '-' << dt.month << '-' << dt.day;
	return ostr;
}
istream &operator>>(istream &istr,Date &dt) //提取符重载
{
	istr >> dt.year >> dt.month >> dt.day;
	return istr;
}

Date &Date::operator++() //前++
{
	int ndays = *this; //调用成员转换，将调用对象转换为整数
	++ndays; //整数增1
	*this = ndays; //调用转换赋值，将整数转换赋值给调用对象
	return *this; //返回调用对象的引用
}
Date Date::operator++(int) //后++
{
	Date t(*this); //保留调用对象的原值
	int ndays = *this; //调用成员转换，将调用对象转换为整数
	++ndays; //整数增1
	*this = ndays; //调用转换赋值，将整数转换赋值给调用对象
	return t; //返回调用对象的保留值
}
Date &Date::operator--() //前--
{
	int ndays = *this;
	--ndays;
	*this = ndays;
	return *this;
}
Date Date::operator--(int) //后--
{
	Date t(*this);
	int ndays = *this;
	--ndays;
	*this = ndays;
	return t;
}
#endif