#include<iostream>
#include<fstream>
#include <sstream>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<string>
#include<TROOT.h>
#include<TChain.h>
#include<TFile.h>
#include<TApplication.h>

using namespace std;

class Analyzer{
	public:
		Analyzer();
		~Analyzer();

		void readFile(string);
		void ConvertTxtToRootFile(string);

	private:
		int _EventNumber;

		string _product1_Name;
		bool _product1_isBoson;
		float _product1_mass;
		float _product1_px;
		float _product1_py;
		float _product1_pz;
		float _product1_E;
		float _product1_pT;
		
		string _product2_Name;
		bool _product2_isBoson;
		float _product2_mass;
		float _product2_px;
		float _product2_py;
		float _product2_pz;
		float _product2_E;
		float _product2_pT;
};