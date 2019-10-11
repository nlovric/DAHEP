#include<iostream>
using namespace std;

class ElementaryParticle
{
	public:
		ElementaryParticle(string n = "bla", float m = 2.0, string iB = "bla"){
			cout << "Constructor called." << endl;
			name = n;
			mass = m;
			isBoson = iB;
		}

		void printInfo()
		{
			cout << "Particle name is: "<< name << endl;
			cout << "Particle mass is: " << mass << " GeV" << endl;
			cout << "Is particle a boson? " << isBoson << endl;
		}

	private:
		string name;
		float mass;
		string isBoson;
};

int main()
{
	ElementaryParticle H("Higgs boson", 126, "Yes");
	ElementaryParticle t("top quark", 173, "No");
	ElementaryParticle Z("Z boson", 91.2, "Yes");
	ElementaryParticle *ptrElePart;    //Declare pointer to the class ElementaryParticle.

	//Drugi način
	ptrElePart = &Z;
	ptrElePart->printInfo();

	ptrElePart = &H;
	ptrElePart->printInfo();

	ptrElePart = &t;
	ptrElePart->printInfo();

	//Prvi način
	/*Higgs.name = "Higgs boson";
	Higgs.mass = 126;
	Higgs.isBoson = "Yes";

	t.name = "top quark";
	t.mass = 173;
	t.isBoson = "No";

	Higgs.printInfo();
	t.printInfo();*/


	return 0;
}
