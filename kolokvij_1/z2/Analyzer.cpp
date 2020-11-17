#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Analyzer::PlotHistogram()
{
  // Create TCanvas
  c = new TCanvas("c","c",900,700);
  c->Divide(2);

  
  // Define histograms
  ele_pt_histo = new TH1F("ele_pt_histo", "Histogram of train electron p_{T}", 50, 0.0, 150.0);
  pt_eta_histo = new TH2F("pt_eta_histo", "supercluster eta vs electron p_{T}", 50, 0.0, 150.0, 50, -2.5, 2.5);

  // Remove stat box
  ele_pt_histo->SetStats(0);
  pt_eta_histo->SetStats(0);

  // Set axis titles
  ele_pt_histo->GetXaxis()->SetTitle("p_{T}");
  ele_pt_histo->GetXaxis()->SetLabelSize(0.04);
  ele_pt_histo->GetYaxis()->SetTitle("Events / 3.0");
  ele_pt_histo->GetYaxis()->SetTitleOffset(1.5);
  ele_pt_histo->GetYaxis()->SetLabelSize(0.04);

  // Coloring
  ele_pt_histo->SetLineColor(kRed+2);

  counter=0;
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     // if (Cut(ientry) < 0) continue;

     ele_pt_histo->Fill(ele_pt);
     pt_eta_histo->Fill(ele_pt,scl_eta);
     counter++;
     if(counter==100000)break;
  }

  c->cd(1);
  ele_pt_histo->Draw("HIST");

  c->cd(2);
  pt_eta_histo->Draw("COLZ");
  pt_eta_histo->SetMinimum(-0.01);
  pt_eta_histo->SetStats(0);
  pt_eta_histo->SetTitle("scl_eta vs p_{T} for electrons");
  pt_eta_histo->GetXaxis()->SetTitle("p_{T}");
  pt_eta_histo->GetYaxis()->SetTitle("scl_eta");

  pt_eta_histo->GetXaxis()->SetLabelSize(0.04);
  pt_eta_histo->GetYaxis()->SetTitleOffset(1.5);
  pt_eta_histo->GetYaxis()->SetLabelSize(0.04);

  SavePlots(c,"TrainElectrons");
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
