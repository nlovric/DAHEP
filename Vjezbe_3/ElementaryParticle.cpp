#include <ElementaryParticle.h>

ElementaryParticle::ElementaryParticle(string n = "bla", float m = 2.0, bool iB = false){
			cout << "Constructor called." << endl;
			name = n;
			mass = m;
			isBoson = iB;
		}

ElementaryParticle::ElementaryParticle(){
			cout << "Constructor called." << endl;
			name = "";
			mass = 0;
			isBoson = false;
		}

void ElementaryParticle::printInfo(){
			cout << "Particle name is: "<< name << endl;
			cout << "Particle mass is: " << mass << " GeV" << endl;
			cout << "Is particle a boson? " << isBoson << endl;
		}

void ElementaryParticle::ParticleMomentum(double _px, double _py, double _pz){
		px=_px;
		py=_py;
		pz=_pz;
		E=sqrt(px*px+py*py+pz*pz+mass*mass);
	}

void ElementaryParticle::transMomentum(){
		p_T=sqrt(px*px+py*py);
		cout << "Particle transverse momentum is: "<< p_T << endl;
	}