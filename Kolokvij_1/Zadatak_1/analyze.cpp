#include <Statistics.h>

int main()
{
	Statistics *statistics;
	statistics = new Statistics();

	statistics->CalculatePi(100000);
	statistics->NormalDistribution(185, 178.2, 6.4);
	statistics->NormalDistribution(205, 178.2, 6.4);
	statistics->NormalDistribution(185, 160.2, 7.2);

	statistics->~Statistics();

	return 0;
}