#ifndef SIMULATION_H
#define SIMULATION_H
#include<iomanip>
#include<iostream>
#include"pqueue.h" //优先级链队列类模板
#include"queue.h" //链队列类模板
using namespace std;
class Event //事件类型
{
	int time; //事件发生时间
	int etype; //事件类型。0表示到达，非0整数表示从该号窗口离开
public:
	Event():time(0),etype(0){} //默认构造
	Event(int t,int e):time(t),etype(e){} //一般构造
	operator int()const{ return(time); } //成员转换
	int GetTime()const{ return(time); } //读取事件发生时间
	int GetEventType()const{ return(etype); } //读取事件类型
};
struct Service //排队客户信息结构
{
	int arrivalTime; //客户到达时间
	int serviceTime; //服务时间
};
struct TellerStatus //窗口信息结构
{
	int totalCustomer; //接待客户总数
	int totalService; //服务时间总数
	int totalWait; //客户等待时间总数
};
class Simulation
{
	int SimulationLength; //模拟时间长度
	int numTellers; //服务窗口个数
	int arrivalLow,arrivalHigh; //客户到达最短和最长时间间隔
	int serviceLow,serviceHigh; //客户最短和最长服务时间
	TellerStatus t[11]; //最多10个窗口，TellerStatus t[1]~t[10]
	Queue<Service>Q[11]; //最多10个窗口队列，Q[1]~Q[10]
	PQueue<Event>PQ; //事件是优先级链队列
	int GetIntertime() //读取客户到达的时间间隔
	{
		return (arrivalLow + rand() % (arrivalHigh - arrivalLow + 1));
	}
	int GetServiceTime() //读取服务时间
	{
		return (serviceLow + rand() % (serviceHigh - serviceLow + 1));
	}
	int GetNextTeller(); //取下一个可用窗口
	void Arrived(const Event &e); //处理一位客户到达事件
	void Departure(const Event &s); //处理一位客户离开事件
	void PrintPQueue(); //显示事件表
	void PrintQueue(); //显示窗口队列
public:
	Simulation(); //模拟过程初始化
	Simulation(int L,int nT,int aL,int aH,int sL,int sH);
	void RunSimulation(); //执行模拟
	void PrintSimulationResults(); //显示模拟过程
};
#endif