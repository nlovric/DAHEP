#include<iostream>
#include<cmath>
#include<cstdlib>
#include<ctime>

using namespace std;


class ElementaryParticle{
	public:
		ElementaryParticle(string n, float m, bool iB);
		ElementaryParticle();
		~ElementaryParticle(); //radi samo kada je konstruktor istog imena kao i klasa!

		float E,px,py,pz;
		string name;
		float p_T;
		float mass;
		bool isBoson;

		void setP(float, float, float);

		void printP4();

		void setInfo(string, float, bool);

		void transverseP();

		void printInfo();

		void bosonDecay(ElementaryParticle *particle_1, ElementaryParticle *particle_2);

	private:
		int random_number;
		int random_number_x, random_number_y, random_number_z;
};
