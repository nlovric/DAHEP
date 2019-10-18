#include <ElementaryParticle.h>

ElementaryParticle::ElementaryParticle(string n = "bla", float m = 2.0, string iB = "bla"){
			cout << "Constructor called." << endl;
			name = n;
			mass = m;
			isBoson = iB;
		}

void ElementaryParticle::printInfo()
		{
			cout << "Particle name is: "<< name << endl;
			cout << "Particle mass is: " << mass << " GeV" << endl;
			cout << "Is particle a boson? " << isBoson << endl;
		}