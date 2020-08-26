#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


void Analyzer::DrawHisto(TString input_file_name)
{
	TCanvas *c = new TCanvas("c","c",1200,800); //platno
    c->Divide(2); //na 2 dijela

    resP = new TLorentzVector();
    p1=new TLorentzVector(particle1_px, particle1_py, particle1_pz, particle1_E);
    p1=new TLorentzVector(particle2_px, particle2_py, particle2_pz, particle2_E);

    resP=p1+p2;

    // Define histograms
  	pT1_histo = new TH1F("pT1_histo", "Transverse momentum", 50, 0., 150.);
  	pT2_histo = new TH1F("pT2_histo", "Transverse momentum", 50, 0., 150.);
    resP_histo = new TH1F("resP_histo", "Histogram of Higgs p_T", 50, 90., 140.);


  	if (fChain == 0) return;

   	Long64_t nentries = fChain->GetEntriesFast();

   	Long64_t nbytes = 0, nb = 0;
   
   	for (Long64_t jentry=0; jentry<nentries; jentry++)
   	{
      	Long64_t ientry = LoadTree(jentry);
      	if (ientry < 0) break;
      	nb = fChain->GetEntry(jentry);   nbytes += nb;
      	// if (Cut(ientry) < 0) continue;

      	if ( jentry > 10000 ) break;

      	pT1_histo->Fill(sqrt(particle1_px*particle1_px + particle1_py*particle1_py));
      	pT2_histo->Fill(sqrt(particle2_px*particle2_px + particle2_py*particle2_py));

        resP_histo->Fill(resP->Pt());
    }

    // Remove stat box
    pT1_histo->SetStats(0);
    pT2_histo->SetStats(0);

    pT1_histo->SetTitle("Transverzalne kolicine gibanja");
    pT1_histo->GetXaxis()->SetTitle("pT");
    pT1_histo->GetYaxis()->SetTitle("Events");

    //pT1_histo->SetMaximum(1.6*pT1_histo->GetMaximum());

    pT2_histo->SetTitle("Transverzalne kolicine gibanja");
    pT2_histo->GetXaxis()->SetTitle("pT");
    pT2_histo->GetYaxis()->SetTitle("Events");

    //pT2_histo->SetMaximum(1.6*pT2_histo->GetMaximum());

    // Coloring
    pT2_histo->SetLineColor(kBlue - 2);

    pT1_histo->SetLineColor(kRed - 2);
    pT1_histo->SetLineStyle(kDashed);

    c->cd(1);
    gPad->SetLeftMargin(0.15);

    pT2_histo->Draw("HIST");
    pT1_histo->Draw("HIST SAME");

    c->cd(2);

    resP_histo->Draw();

    TLegend *legend_Higgs = new TLegend(0.1,0.8,0.5,0.9);
    legend_Higgs->AddEntry(resP_histo,"Reconstructed Higgs","f");
    legend_Higgs->SetTextSize(0.03);
    legend_Higgs->Draw();

    SavePlots(c, "zdkAB");
}

void Analyzer::SavePlots(TCanvas *_c, TString name)
{
  _c->SaveAs(name + ".pdf");
  _c->SaveAs(name + ".png");
  _c->SaveAs(name + ".root");
}


void Analyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analyzer.C
//      root> Analyzer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}
