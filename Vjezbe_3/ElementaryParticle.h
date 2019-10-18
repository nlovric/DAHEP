#include<iostream>
#include<cmath>
using namespace std;

class ElementaryParticle
{
	public:
		ElementaryParticle(string n, float m, bool iB);
		ElementaryParticle();

		float E,px,py,pz;

		void ParticleMomentum(double, double, double);

		void transMomentum();

		void printInfo();

	private:
		float p_T;
		string name;
		float mass;
		bool isBoson;
};