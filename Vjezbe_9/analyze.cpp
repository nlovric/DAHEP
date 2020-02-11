#include <Analyzer.h>

int main(){
	// Declare Analyzer
	Analyzer *analyzer = new Analyzer();

	analyzer->MLFit();
 	
	delete analyzer;

	return 0;
}