#include<pdfGen.h>

PdfGen::PdfGen(){
printf("Objekt je uspjesno kreiran.");
}

PdfGen::~PdfGen(){}

float PdfGen::GenerateQuadraticPDF()
{
	srand (time(NULL));

	float rand_y = (float) (rand()%1000 - 500);
	x = sqrt(1.0-4.0*rand_y/3.0);

	if(x<=1.&&x>=-1.){
		return x;
	}
	else{
		return 100.;
	}
}

void PdfGen::PlotHistogram()
{
  // Create TCanvas
  c = new TCanvas("c","c",900,700);

  histo=new TH1F("histo", "Histogram of events satisfying the given PDF", 20, -1.0, 1.0);

  for(int i=0;i<10000;i++){
    if(GenerateQuadraticPDF()!=100.){
  	histo->Fill(GenerateQuadraticPDF());
    }
  }

  // Remove stat box
  histo->SetStats(0);

  // Set axis titles
  histo->GetXaxis()->SetTitle("x");
  histo->GetXaxis()->SetLabelSize(0.04);
  histo->GetYaxis()->SetTitle("Events / 0.1");
  histo->GetYaxis()->SetTitleOffset(2.5);
  histo->GetYaxis()->SetLabelSize(0.04);

  histo->Draw("HIST");

  SavePlots(c,"PDF_histo");

}

void PdfGen::SavePlots(TCanvas *c, TString name)
{
  c->SaveAs(name + ".pdf");
  c->SaveAs(name + ".png");
}
