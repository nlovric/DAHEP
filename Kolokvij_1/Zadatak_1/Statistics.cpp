#include<Statistics.h>

Statistics::Statistics(){}

Statistics::~Statistics(){}

void Statistics::CalculatePi(int _num_events)
{
	srand (time(NULL));
	int N_uk=0, N_krug=0;

	for (int i=0; i<_num_events; i++)
	{
		random_number = rand()%1;
		if (random_number < float(3.14/4.)){
			N_krug++;
		}

		N_uk++;
	}

	_pi = 4*(N_krug/N_uk);
	cout << "Pi je: " << _pi << endl;
}

void Statistics::NormalDistribution(int x, float mu, float sig)
{
	P = exp(-(x-mu)*(x-mu)/(2*sig*sig))/(sig*sqrt(2*3.14));

	cout << "P je: " << P << endl;
}