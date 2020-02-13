// My own class
#include <Analyzer.h>

int main()
{
  // Declare Analyzer
  Analyzer *analyzer;

  analyzer = new Analyzer();

  analyzer->ChiSquareFit();

  delete analyzer;

  return 0;
}
