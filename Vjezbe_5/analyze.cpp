#include <Analyzer.h>

int main(){
	// Declare Analyzer
	Analyzer *analyzer = new Analyzer();

	analyzer->PlotHistogram();

	delete analyzer;

	return 0;
}