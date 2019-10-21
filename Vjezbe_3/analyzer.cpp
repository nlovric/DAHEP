#include<iostream>
#include<fstream>
#include <ElementaryParticle.h>

using namespace std; //zašto i ovdje i u ElementaryParticle.h?

int main(){
	int x_rand, y_rand, z_rand;
	srand(time(NULL));

	ofstream file;
	file.open ("Analysis.txt");

	ElementaryParticle *Higgs;

	Higgs = new ElementaryParticle("Higgs", 125.6, true); //deklaracija Higgsa koji ce se raspadati

	ElementaryParticle *product_1, *product_2; //deklaracija dviju čestica koje su produkti raspada
	product_1 = new ElementaryParticle();
	product_2 = new ElementaryParticle();

	file << "EventNumber Product1_Name Product1_isBoson Product1_mass Product1_px Product1_py Product1_pz Product1_E Product1_pT" <<
						" Product2_Name Product2_isBoson Product2_mass Product2_px Product2_py Product2_pz Product2_E Product2_pT" << endl;

	for(int i = 0; i < 10000; i++){
		x_rand = -100 + rand() % 200;
		y_rand = -100 + rand() % 200;
		z_rand = -100 + rand() % 200;

		Higgs->setP(x_rand, y_rand, z_rand); //trebaju nam komponente u rasponu od -100 do 100 GeV

		Higgs->bosonDecay(product_1, product_2);

		file << i << " " << product_1->name << " " << product_1->isBoson << " " << product_1->mass << " "
						 << product_1->px << " " << product_1->py << " " << product_1->pz << " " << product_1->E << " " << product_1->p_T << " "
						 << product_2->name << " " << product_2->isBoson << " " << product_2->mass << " "
						 << product_2->px << " " << product_2->py << " " << product_2->pz << " " << product_2->E << " " << product_2->p_T << endl;
	}

	file.close();

	Higgs->~ElementaryParticle();
	product_1->~ElementaryParticle();
	product_2->~ElementaryParticle();

	return 0;
}