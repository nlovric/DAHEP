#include <Analyzer.h>

int main(){

	Analyzer *analyzer;
	analyzer = new Analyzer();

	//analyzer->readFile("Analysis.txt");
	analyzer->ConvertTxtToRootFile("Analysis.txt");

	analyzer->~Analyzer();

	return 0;
}