#ifndef BANK_H
#define BANK_H
#include <iostream>
#include <time.h>
#include <random>
#include "queue.cpp"
#include<cstdlib>
using namespace std;
class Cashier
{
private:
	int servingTime;//време на обслужването
	int startTime;//време,в което започва обслужването на даден клиент
	int endTime;//време,в което приключва обслужването на даден клиент
	int number;//номер на касата
	bool isFree;//дали касата е свободна
	int clientsCount;//брой обслужени клиенти
	int timeWhenFree;//време,през което касиера е бил свободен
public:
	Cashier(int start,int Max):number(0),isFree(1),clientsCount(0),timeWhenFree(0)
	{
		set_servingTime(Max);
		set_startTime(start);
		set_endTime();
	}
	Cashier():servingTime(0),startTime(0),endTime(0),
	isFree(1),number(0),clientsCount(0),timeWhenFree(0){}
	
	int get_servingTime() const;//връща колко време е отнело обслужването
	int get_startTime() const;//връща минутата,в която е започнало обслужването
	int get_endTime() const;//връща минутата,в която е приключило обслужването
	bool get_isFree() const;//връща 1 при свободна каса и 0 при заета каса
	int get_number() const;//връща номера на касата
	int get_clientsCount() const;//връща броя на обслужените клиенти
	int get_timeWhenFree() const;//връща времето,през което касиера е бил свободен
	
	void set_servingTime(int);//указва колко време ще отнеме обслужването
	void set_startTime(int);//указва времето,в което започва обслужването
	void set_endTime();//указва кога ще приключи обслужването
	void set_number(int);//указва номер на касата
	void set_isFree(bool);//указва дали касата е заета или не
	void set_clientsCount(int);//указва броя на обслужените клиенти
	void set_timeWhenFree(int);//указва колко време е бил свободен касиера
	
	friend ostream& operator << (ostream& out,Cashier& c);//извежда информация за касиера
};

class Client
{
private:
	int commingTime;//време,когато е дошъл клиентът
public:
	//time-минута,след която е дошъл клиента
	//maxDelay-максимално забавяне след дадената минута
	Client(int time,int maxDelay)
	{
		set_commingTime(time,maxDelay);
	}
	Client():commingTime(0){}

	void set_commingTime(int time,int maxDelay);//указва време на идване
	//като се взима в предвид някакво време,след което е дошъл клиента
	//и колко максимално след това време се е забавил
	
	int get_commingTime() const;//връща времето на идването
	
	friend ostream& operator << (ostream& out,Client& c);//извежда информация за клиента
    //за това кога е дошъл
};
class BankService
{
private:
	LQueue<Client> q;//опашка,на която се нареждат клиентите
	Cashier *cash;//всички касиери
	Cashier *free;//свободните касиери
	int nCashiers; //брой на касиерите
	int maxLengthQueue;//за максималната дължина на опашката
	double wholeTimeWaiting;//общото количество време,прекарано 
	//в чакане
	double time;//времето на работа на банката
	double averageLength; //средна дължина на опашката
    int maxServingTime; //определя максимално колко време е отнело на всеки касиер
	//да обслужи клиент
	int maxDelayTime; //определя през колко максимално време идват клиентите
public:
	BankService(int n,int t,int mS,int mD):nCashiers(n),time(t),maxLengthQueue(0),wholeTimeWaiting(0),
	averageLength(0)
	{
		cash=new Cashier[n];
	    free=new Cashier[n];
		maxServingTime=mS;
		maxDelayTime=mD;
	}//при създаването на обслужването се подава колко наброй са касиерите
	//колко минути е работното време
	//колко минути максимално ще отнема обслужването 
	//и през колко минути максимално ще постъпва клиент
	BankService():nCashiers(2),time(10),maxLengthQueue(0),
	wholeTimeWaiting(0),averageLength(0),maxServingTime(5),maxDelayTime(2){}
	~BankService()
	{
		delete[] cash;
		delete[] free;
	}
	
	void Servicing();//тук се извършва самото обслужване
	
	void set_maxLengthQueue(int len); //сменя максималната дължина на 
	//опашката като я заменя с новата len дължина само ако len > сегашната
	//максимална дължина
	void set_averageLength(double a);//задава колко е сбора на дължините на опашките
	void set_time(double time);//задава общо време се е чакало от всеки клиент

	int get_clientsServed()const; //връща броя само на обслужените клиенти 
	int get_maxLengthQueue()const;//връща максималната дължина на опашката
	double get_time()const;//връща колко е общото време,прекарано в чакане от всеки един клиент
	double get_averageTime()const;//връща средното време на чакане
	double get_averageLength()const;//връща средната дължина на опашката
	
	void CheckIfReady(int minute);//в дадена минута проверява кои касиери са готови и 
	//на готовите указва,че вече са свободни
	int FreeCashiers();//разглежда всички касиери и вижда кои са свободните касиери като ги
	//отделя в отделен масив от касиери -> free
	void situation(int minute);//извежда информация за това какво се случва с всеки един от касиерите
	//в дадена минута и ако касиер е свободен в тази минута,то увеличава времето,в което е бил свободен с минута
	void clientsServedByEachCashier();//извежда статистика за броя на обслужените клиенти от всеки 
	//касиер
	void timeWhenCashiersAreFree();//извежда статистика за процента от времето,когато касиерите 
	//са били свободни 
};
#endif BANK_H
