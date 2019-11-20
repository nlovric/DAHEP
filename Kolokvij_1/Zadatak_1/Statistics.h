#include<iostream>
#include<fstream>
#include<sstream>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<string>
#include<vector>
using namespace std;

class Statistics{
public:
	Statistics();
	~Statistics();

	void CalculatePi(int);
	void NormalDistribution(int, float, float);

private:
	float _pi;
	float random_number;
	float P;
};