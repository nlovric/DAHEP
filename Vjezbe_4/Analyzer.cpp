#include<Analyzer.h>

Analyzer::Analyzer(){}

Analyzer::~Analyzer(){}

void Analyzer::readFile(string _inFileName){
	ifstream _inFile;
	string line;

	_inFile.open(_inFileName.c_str());

		if (_inFile.is_open()){
		while (getline(_inFile, line)){
			stringstream linestream(line);

			// Since we know that first line of the file only describes data skip reading it into variables
	

			//Read the file line and store it in dedicated variables.
			linestream >> _EventNumber >> _product1_Name >> _product1_isBoson >> _product1_mass >> _product1_px >> _product1_py >> _product1_pz >> _product1_E >> _product1_pT
										>> _product2_Name >> _product2_isBoson >> _product2_mass >> _product2_px >> _product2_py >> _product2_pz >> _product2_E >> _product2_pT;


		}
	}
}

void Analyzer::ConvertTxtToRootFile(string _inFileName){
	ifstream _inFile;
	string line;

	TFile *_outFile = new TFile("Analysis.root", "recreate");
	// create a TTree
	TTree *tree = new TTree("t", "decay particle analysis");
	// key = t
	// title = decay particle analysis

	tree->Branch("evnum", &_EventNumber, "_EventNumber/I");

	tree->Branch("n1", &_product1_Name, "_product1_Name/S");
	tree->Branch("isB1", &_product1_isBoson, "_product1_isBoson/O");
	tree->Branch("m1", &_product1_mass, "_product1_mass_product1_px/F");
	tree->Branch("px1", &_product1_px, "_product1_px/F");
	tree->Branch("py1", &_product1_py, "_product1_py/F");
	tree->Branch("pz1", &_product1_pz, "_product1_pz/F");
	tree->Branch("E1", &_product1_E, "_product1_E/F");
	tree->Branch("pT1", &_product1_pT, "_product1_pT/F");

	tree->Branch("n2", &_product2_Name, "_product2_Name/S");
	tree->Branch("isB2", &_product2_isBoson, "_product2_isBoson/O");
	tree->Branch("m2", &_product2_mass, "_product2_mass_product1_px/F");
	tree->Branch("px2", &_product2_px, "_product2_px/F");
	tree->Branch("py2", &_product2_py, "_product2_py/F");
	tree->Branch("pz2", &_product2_pz, "_product2_pz/F");
	tree->Branch("E2", &_product2_E, "_product2_E/F");
	tree->Branch("pT2", &_product2_pT, "_product2_pT/F");

	_inFile.open(_inFileName.c_str());

		if (_inFile.is_open()){
		while (getline(_inFile, line)){
			stringstream linestream(line);

			// Since we know that first line of the file only describes data skip reading it into variables
	

			//Read the file line and store it in dedicated variables.
			linestream >> _EventNumber >> _product1_Name >> _product1_isBoson >> _product1_mass >> _product1_px >> _product1_py >> _product1_pz >> _product1_E >> _product1_pT
										>> _product2_Name >> _product2_isBoson >> _product2_mass >> _product2_px >> _product2_py >> _product2_pz >> _product2_E >> _product2_pT;

			tree->Fill();
		}
	}
	tree->Write();
	_outFile->Close();
}