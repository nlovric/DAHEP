#include <Analyzer.h>

int main(){
	// Declare Analyzer
	Analyzer *analyzer = new Analyzer();

	analyzer->PlotHistogram("/home/public/data/ggH125/ZZ4lAnalysis.root");
 	analyzer->PlotHistogram("/home/public/data/qqZZ/ZZ4lAnalysis.root");

 	analyzer->PlotMass();
 	analyzer->PlotDkin();
 	
	delete analyzer;

	return 0;
}