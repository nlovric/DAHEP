#include <Analyzer.h>

int main(){
	// Declare Analyzer
	Analyzer *analyzer = new Analyzer();

	analyzer->PlotHistogram("/home/public/data/ggH125/ZZ4lAnalysis.root");

	delete analyzer;

	return 0;
}