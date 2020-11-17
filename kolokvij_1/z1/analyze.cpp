#include <pdfGen.h>

int main()
{
	PdfGen *pdfGen;
	pdfGen = new PdfGen();

	pdfGen->PlotHistogram();

	pdfGen->~PdfGen();

	return 0;
}
