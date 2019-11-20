#include<Statistics.h>

Statistics::Statistics(){}

Statistics::~Statistics(){}

void Statistics::CalculatePi(int num_events)
{
	srand (time(NULL));
	int N_uk=0, N_krug=0;

	for (int i=0; i < num_events; i++)
	{
		x = (float) (rand()%100 - 50);
		y = (float) (rand()%100 - 50);

		r = sqrt(x*x + y*y);

		if (r <= 50.){
			N_krug++;
		}

		N_uk++;
	}

	pi = 4. * (float) (N_krug) / (float) (N_uk);
	cout << "Pi je: " << pi << endl;
}

void Statistics::NormalDistribution(int x, float mu, float sig)
{
	P = exp(-(x-mu)*(x-mu)/(2*sig*sig))/(sig*sqrt(2*3.14));

	cout << "P je: " << P << endl;
}