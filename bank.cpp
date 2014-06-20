#include "Bank.h"
int Cashier::get_servingTime() const
{
	return servingTime;	
}
int Cashier::get_startTime() const
{
	return startTime;	
}
int Cashier::get_endTime() const
{
	return endTime;	
}
bool Cashier::get_isFree() const
{
	return isFree;
}
int Cashier::get_number() const
{
	return number;
}
int Cashier::get_clientsCount() const
{
	return clientsCount;
}
int Cashier::get_timeWhenFree() const
{
	return timeWhenFree;
}
void Cashier::set_servingTime(int Max)
{
	servingTime = 1 + ( rand() % Max);
}
void Cashier::set_startTime(int start)
{
	startTime = start;
}
void Cashier::set_endTime()
{
	endTime = get_startTime() + get_servingTime();
}
void Cashier::set_number(int n)
{
	number=n;
}
void Cashier::set_isFree(bool n)
{
	isFree=n;
}
void Cashier::set_clientsCount(int c)
{
	clientsCount=c;
}
void Cashier::set_timeWhenFree(int t)
{
	timeWhenFree=t;
}
ostream& operator << (ostream& out,Cashier& c)
{
	out<<"------cashier number "<<c.get_number()<<"------\n"<<
	     "service started at minute: "<<c.get_startTime()<<
		 "\nsevice took "<<c.get_servingTime()<<" minutes"<<
		 "\nservice finished at the "<<c.get_endTime()<<" minute"<<
	     "\nclients served by this cashier:"<<c.get_clientsCount()<<
		 "\nat the moment this cashier is ";
	
	if(!c.get_isFree())
		cout<<"not ";
	cout<<"free\n";
	return out;
}



void Client::set_commingTime(int time,int maxDelay)
{
	commingTime = time + (rand() % maxDelay);
}
int Client::get_commingTime() const 
{
	return commingTime;
}
ostream& operator << (ostream& out,Client& c)
{
	out<<"this client came at "<<c.get_commingTime()<<"minute\n";
	return out;
}



void BankService::Servicing()
{
	for(int i=0;i<nCashiers;i++)
		cash[i].set_number(i);
	int j,i,t;
	for(i=0;i<time;i++)
	{
			Client newCommer(i,maxDelayTime);
			if(newCommer.get_commingTime() < time)
				t=newCommer.get_commingTime();
			else t=time-1;
			for(int p=i;p<=t;p++)
			{
				set_averageLength(get_averageLength() + size(q)/time);
				CheckIfReady(p);
				j=FreeCashiers(); 
				if(j!=0 && !q.empty())
				{
					while(j && !q.empty())
					{
						Client client;
						q.pop(client);
						set_time(get_time()+ (p - client.get_commingTime()));
						int choice = rand()%j;
						cash[free[choice].get_number()].set_isFree(0);
						cash[free[choice].get_number()].set_startTime(p);
						cash[free[choice].get_number()].set_servingTime(maxServingTime);
						cash[free[choice].get_number()].set_endTime();
						cash[free[choice].get_number()].set_clientsCount(cash[free[choice].get_number()].get_clientsCount()+1);
						FreeCashiers();
						j--;
					}
			 	}
				if(p!=newCommer.get_commingTime())
				situation(p);
			}
			if(newCommer.get_commingTime()<time)
			{
				CheckIfReady(newCommer.get_commingTime());
				j=FreeCashiers(); 
				if(j!=0 && q.empty())
				{
					int choice = rand()%j;
					cash[free[choice].get_number()].set_isFree(0);
					cash[free[choice].get_number()].set_startTime(newCommer.get_commingTime());
					cash[free[choice].get_number()].set_servingTime(maxServingTime);
					cash[free[choice].get_number()].set_endTime();
					cash[free[choice].get_number()].set_clientsCount(cash[free[choice].get_number()].get_clientsCount()+1);
				}
				if(j==0)
				{
					q.push(newCommer);	
					set_maxLengthQueue(size(q));
				}
			}
			i=newCommer.get_commingTime();
			if(i<time)
			situation(i);
	}
}
int BankService::FreeCashiers()
{
	int j=0;
	for(int i=0;i<nCashiers;i++)
	{
		if(cash[i].get_isFree())
		{
			free[j] = cash[i]; 
			j++;
		}
	}
	return j;
}

void BankService::CheckIfReady(int minute)
{
	for(int i=0;i<nCashiers;i++)
		if(cash[i].get_endTime() == minute && minute!=0)
			cash[i].set_isFree(1);
}
void BankService::set_maxLengthQueue(int len)
{
	if(len>get_maxLengthQueue())
		maxLengthQueue=len;
}
void BankService::set_averageLength(double a)
{
		averageLength=a;
}
void BankService::set_time(double time)
{
	wholeTimeWaiting=time;
}
int BankService::get_clientsServed()const
{
	int allClients=0;
	for(int i=0;i<nCashiers;i++)
	{
		allClients+=cash[i].get_clientsCount();
	}
	return allClients;
}
int BankService::get_maxLengthQueue()const
{
	return maxLengthQueue;
}
double BankService::get_time()const
{
	return wholeTimeWaiting;
}
double BankService::get_averageTime()const
{
	return get_time()/get_clientsServed();
}
double BankService::get_averageLength()const
{
	return averageLength;
}
void BankService::situation(int minute)
{
	for(int i=0;i<nCashiers;i++)
	{
		if(cash[i].get_isFree())
			cash[i].set_timeWhenFree(cash[i].get_timeWhenFree()+1);
	}
}
void BankService::clientsServedByEachCashier()
{
	cout<<"\n\nstatistic about clients served by each cashier:\n";
	for(int i=0;i<nCashiers;i++)
	cout<<"cashier "<<cash[i].get_number()<<
	" served "<<cash[i].get_clientsCount()<<" clients.\n----------------------------\n"; 
	cout<<endl;
}
void BankService::timeWhenCashiersAreFree()
{
	for(int i=0;i<nCashiers;i++)
	{
		cout<<"cashier "<<i<<" was free: "<<cash[i].get_timeWhenFree()
			<<" minutes => "<<(cash[i].get_timeWhenFree()/(double)time)*100<<"% \n";
	}
}
