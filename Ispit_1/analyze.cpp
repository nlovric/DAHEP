#include <Analyzer.h>

int main(){
	// Declare Analyzer
	Analyzer *analyzer = new Analyzer();

	analyzer->DrawHisto("/home/public/data/HiggsSearch/CMSData.root");

	delete analyzer;

	return 0;
}