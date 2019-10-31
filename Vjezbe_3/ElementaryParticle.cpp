#include <ElementaryParticle.h>

ElementaryParticle::ElementaryParticle(string _name, float _mass, bool _isBoson){
			cout << "Constructor called." << endl;
			name = _name;
			mass = _mass;
			isBoson = _isBoson;
		}

ElementaryParticle::ElementaryParticle(){
			cout << "Constructor called." << endl;
			name = "";
			mass = 0;
			isBoson = false;
		}

ElementaryParticle::~ElementaryParticle(){

}

void ElementaryParticle::printInfo(){
			cout << "Particle name is: "<< name << endl;
			cout << "Particle mass is: " << mass << " GeV" << endl;
			cout << "Particle IS ";
			if(!isBoson) cout << "NOT ";
			cout << "a boson." << endl;
		}

void ElementaryParticle::setP(float _px, float _py, float _pz){
		px=_px;
		py=_py;
		pz=_pz;
		E=sqrt(px*px+py*py+pz*pz+mass*mass);
	}

void ElementaryParticle::printP4(){
	cout << "(" << px << ", " << py << ", " << pz << ", " << E << ")" << endl;
}

void ElementaryParticle::setInfo(string _name, float _mass, bool _isBoson){
	name=_name;
	mass=_mass;
	isBoson=_isBoson;
}

void ElementaryParticle::transverseP(){
		p_T=sqrt(px*px+py*py);
		cout << "Particle transverse momentum is: "<< p_T << endl;
	}

void ElementaryParticle::set_pT(){
		p_T=sqrt(px*px+py*py);
	}

void ElementaryParticle::bosonDecay(ElementaryParticle *particle_1, ElementaryParticle *particle_2){
	if(!isBoson){
		cout << "Only boson decays are supported and " << name << " is not a boson." << endl;
		return;
	}

	random_number = rand()%1000 + 1;

	if(random_number < 214){
		particle_1->setInfo("W+", 80.4, true);
		particle_2->setInfo("W-", 80.4, true);
	}
	else if(random_number < 214 + 64){
		particle_1->setInfo("tau+", 1.77, false);
		particle_2->setInfo("tau-", 1.77, false);
	}
	else if(random_number < 214 +64 + 26){
		particle_1->setInfo("Z", 91.2, true);
		particle_2->setInfo("Z", 91.2, true);
	}
	else{
		particle_1->setInfo("b", 4.18, false);
		particle_2->setInfo("b", 4.18, false);
	}

	random_number_x = rand()%100 + 1;

	if(random_number_x == 100){
		random_number_y = 0;
		random_number_z = 0;
	}
	else{
		random_number_y = rand() % (100 - random_number_x) + 1;
		random_number_z = 100 - random_number_x - random_number_y;
	}

	particle_1->setP(px*(random_number_x/100.), py*(random_number_y/100.), pz*(random_number_z/100.));
	particle_1->set_pT();

	particle_2->setP(px - particle_1->px, py - particle_1->py, pz - particle_1->pz);
	particle_2->set_pT();
}
