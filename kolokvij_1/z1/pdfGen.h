#include<iostream>
#include<fstream>
#include<sstream>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<string>
#include<vector>
#include <TH1F.h>
#include <TCanvas.h>
#include <TString.h>
#include <TLegend.h>

//C++ libraries
#include <iostream>
#include <vector>
using namespace std;

class PdfGen{
public:
	PdfGen();
	~PdfGen();

	float GenerateQuadraticPDF();
	virtual void PlotHistogram( );

private:
   TCanvas *c;
   float x, y;
   TH1F *histo;

   void SavePlots(TCanvas *c, TString name);
	
};
