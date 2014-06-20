#include "Bank.h"
void statistics(BankService& e)
{
	e.Servicing();
	cout<<endl<<"number of clients served:"<<e.get_clientsServed()<<endl;
	e.clientsServedByEachCashier();
	cout<<endl<<"average time waiting:"<<e.get_averageTime()<<endl;
	cout<<endl<<"average size of queue:"<<(int)e.get_averageLength();
	cout<<"\nmax Queue size:"<<e.get_maxLengthQueue()<<endl;
	cout<<"\npercent when cashiers were free:\n";
	e.timeWhenCashiersAreFree();
}
int main()
{
	srand(time(NULL));
	int cashiers,time,mS,mD;
	cout<<"how many are the cashiers? ->";
	cin>>cashiers;
	cout<<"what's the working time? ->";
	cin>>time;
	cout<<"what's the maxServing time? ->";
	cin>>mS;
	cout<<"what's the maxDelay time?->";
	cin>>mD;
	BankService e(cashiers,time,mS,mD);
	statistics(e);
	//още примери:
	cout<<"-------------------------------------------------------\n";
	cout<<"Another BankService(2 cashiers,100 minutes,5 minutes maxServing time,5 minutes maxDelay time)\n";
	BankService m(2,100,5,5);
	statistics(m);
	cout<<"-------------------------------------------------------\n";
	cout<<"Another BankService(4 cashiers,150 minutes,6 minutes maxServing time,4 minutes maxDelay time)\n";
	BankService l(4,150,6,4);
	statistics(l);
	system("pause");
	return 0;
}
