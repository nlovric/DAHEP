#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Analyzer::PlotHistogram(){
	// Create canvas
	c = new TCanvas("c","c",900,700);
	c->Divide(2);

	Higgs = new TLorentzVector();

	c->cd(1);
	// Define histograms
	pT1_histo = new TH1F("pT1_histo","Histogram of decay particle p_T",50,0.,150.);
	pT2_histo = new TH1F("pT2_histo","Histogram of decay particle p_T",50,0.,150.);
	Higgs_pT_histo = new TH1F("Higgs_pT_histo", "Histogram of Higgs p_T", 50, 0., 150.);

	//Remove stat box (event number and average value)
	pT1_histo->SetStats(0);
	pT2_histo->SetStats(0);
	Higgs_pT_histo->SetStats(0);

	//Set axis titles
	pT1_histo->GetXaxis()->SetTitle("p_T [GeV]");
	pT1_histo->GetXaxis()->SetLabelSize(0.04);
	pT1_histo->GetYaxis()->SetTitle("Events / 3 GeV");
	pT1_histo->GetYaxis()->SetLabelSize(0.04);
	pT1_histo->GetYaxis()->SetTitleOffset(1.5);

	pT2_histo->GetXaxis()->SetTitle("p_T [GeV]");
	pT2_histo->GetXaxis()->SetLabelSize(0.04);
	pT2_histo->GetYaxis()->SetTitle("Events / 3 GeV");
	pT2_histo->GetYaxis()->SetLabelSize(0.04);
	pT2_histo->GetYaxis()->SetTitleOffset(1.5);

	Higgs_pT_histo->GetXaxis()->SetTitle("p_T [GeV]");
	Higgs_pT_histo->GetXaxis()->SetLabelSize(0.04);
	Higgs_pT_histo->GetYaxis()->SetTitle("Events / 3 GeV");
	Higgs_pT_histo->GetYaxis()->SetLabelSize(0.04);
	Higgs_pT_histo->GetYaxis()->SetTitleOffset(1.5);

	// Coloring
	pT1_histo->SetLineColor(kBlue -2);
  	pT1_histo->SetFillColor(kBlue -2);

  	pT2_histo->SetLineColor(kBlue +1);

  	Higgs_pT_histo->SetLineColor(kRed + 2);
  	Higgs_pT_histo->SetFillColor(kRed + 2);

  	if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      pT1_histo->Fill(pT1);
      pT2_histo->Fill(pT2);

      // Reconstruct Higgs from decay products
     Higgs->SetPxPyPzE(px1 + px2, py1 + py2, pz1 + pz2, E1 + E2);

     Higgs_pT_histo->Fill(Higgs->Pt());
   }

   pT1_histo->Draw();
   pT2_histo->Draw("HIST SAME");

   TLegend *legend = new TLegend(0.5,0.8,0.9,0.9);
   legend->AddEntry(pT1_histo, "First decay particle","f");
   legend->AddEntry(pT2_histo, "Second decay particle", "f");
   legend->SetTextSize(0.03);
   legend->Draw();

   c->cd(2);

   Higgs_pT_histo->Draw();

   TLegend *legend_Higgs = new TLegend(0.1,0.8,0.5,0.9);
   legend_Higgs->AddEntry(Higgs_pT_histo,"Reconstructed Higgs","f");
   legend_Higgs->SetTextSize(0.03);
   legend_Higgs->Draw();
   
   SavePlots(c, "HiggsPt");
}

void Analyzer::SavePlots(TCanvas *c, TString name)
{
  c->SaveAs(name + ".pdf");
  c->SaveAs(name + ".png");
  c->SaveAs(name + ".root");
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
