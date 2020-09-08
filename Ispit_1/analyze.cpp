#include <Analyzer.h>

int main(){
	// Declare Analyzer
	Analyzer *analyzer = new Analyzer();

	analyzer->DrawHisto();

	delete analyzer;

	return 0;
}