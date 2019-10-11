#include<iostream>
using namespace std;

class ElementaryParticle
{
	public:
		ElementaryParticle(string n, float m, string iB);


		void printInfo();

	private:
		string name;
		float mass;
		string isBoson;
};