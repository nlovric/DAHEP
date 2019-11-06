#define Analyzer_cxx
#include "Analyzer.h"


void Analyzer::PlotHistogram(){
	// Create canvas
	c = new TCanvas("c","c",900,700);
	c1 = new TCanvas("c1","c1",900,700);
	c->Divide(2,2);

	TLorentzVector l1,l2,l3,l4,Z1,Z2,H;

	
	// Define histograms
	l1_Pt_histo = new TH1F("l1_Pt_histo","Histogram of the 1st leptons p_T", 50, 0., 150.);
	l2_Pt_histo = new TH1F("l2_Pt_histo","Histogram of the 2nd leptons p_T", 50, 0., 150.);
	l3_Pt_histo = new TH1F("l3_Pt_histo","Histogram of the 3rd leptons p_T", 50, 0., 150.);
	l4_Pt_histo = new TH1F("l4_Pt_histo","Histogram of the 4th leptons p_T", 50, 0., 150.);
	Higgs_recMass_histo = new TH1F("Higgs_pT_histo", "Histogram of Higgs p_T", 50, 90., 140.);

	//Remove stat box (event number and average value)
	l1_Pt_histo->SetStats(0);
	l2_Pt_histo->SetStats(0);
	l3_Pt_histo->SetStats(0);
	l4_Pt_histo->SetStats(0);
	Higgs_recMass_histo->SetStats(0);

	//Set axis titles
	l1_Pt_histo->GetXaxis()->SetTitle("p_T [GeV]");
	l1_Pt_histo->GetXaxis()->SetLabelSize(0.04);
	l1_Pt_histo->GetYaxis()->SetTitle("Events / 3 GeV");
	l1_Pt_histo->GetYaxis()->SetLabelSize(0.04);
	l1_Pt_histo->GetYaxis()->SetTitleOffset(1.5);

	l2_Pt_histo->GetXaxis()->SetTitle("p_T [GeV]");
	l2_Pt_histo->GetXaxis()->SetLabelSize(0.04);
	l2_Pt_histo->GetYaxis()->SetTitle("Events / 3 GeV");
	l2_Pt_histo->GetYaxis()->SetLabelSize(0.04);
	l2_Pt_histo->GetYaxis()->SetTitleOffset(1.5);

	l3_Pt_histo->GetXaxis()->SetTitle("p_T [GeV]");
	l3_Pt_histo->GetXaxis()->SetLabelSize(0.04);
	l3_Pt_histo->GetYaxis()->SetTitle("Events / 3 GeV");
	l3_Pt_histo->GetYaxis()->SetLabelSize(0.04);
	l3_Pt_histo->GetYaxis()->SetTitleOffset(1.5);

	l4_Pt_histo->GetXaxis()->SetTitle("p_T [GeV]");
	l4_Pt_histo->GetXaxis()->SetLabelSize(0.04);
	l4_Pt_histo->GetYaxis()->SetTitle("Events / 3 GeV");
	l4_Pt_histo->GetYaxis()->SetLabelSize(0.04);
	l4_Pt_histo->GetYaxis()->SetTitleOffset(1.5);

	Higgs_recMass_histo->GetXaxis()->SetTitle("p_T [GeV]");
	Higgs_recMass_histo->GetXaxis()->SetLabelSize(0.04);
	Higgs_recMass_histo->GetYaxis()->SetTitle("Events / 3 GeV");
	Higgs_recMass_histo->GetYaxis()->SetLabelSize(0.04);
	Higgs_recMass_histo->GetYaxis()->SetTitleOffset(1.5);

	// Coloring
	l1_Pt_histo->SetLineColor(kBlue -2);
  	l1_Pt_histo->SetFillColor(kBlue -2);

  	l2_Pt_histo->SetLineColor(kBlue +1);

  	l3_Pt_histo->SetLineColor(kGreen -2);
  	l3_Pt_histo->SetFillColor(kGreen -2);

  	l4_Pt_histo->SetLineColor(kGreen +1);

  	Higgs_recMass_histo->SetLineColor(kRed + 2);
  	Higgs_recMass_histo->SetFillColor(kRed + 2);

  	if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      // Reconstruct Higgs from decay products
     l1.SetPtEtaPhiM(LepPt->at(0), LepEta->at(0), LepPhi->at(0), 0);
     l2.SetPtEtaPhiM(LepPt->at(1), LepEta->at(1), LepPhi->at(1), 0);
     l3.SetPtEtaPhiM(LepPt->at(2), LepEta->at(2), LepPhi->at(2), 0);
     l4.SetPtEtaPhiM(LepPt->at(3), LepEta->at(3), LepPhi->at(3), 0);

     Z1 = l1 + l2;
     Z2 = l3 + l4;
     H = Z1 + Z2;

     l1_Pt_histo->Fill(l1.Pt());
     l2_Pt_histo->Fill(l2.Pt());
     l3_Pt_histo->Fill(l3.Pt());
     l4_Pt_histo->Fill(l4.Pt());

     Higgs_recMass_histo->Fill(H.M());
   }

   c->cd(1);

   l1_Pt_histo->Draw();
   l2_Pt_histo->Draw("HIST SAME");
   l3_Pt_histo->Draw("HIST SAME");
   l4_Pt_histo->Draw("HIST SAME");

   TLegend *legend = new TLegend(0.13,0.8,0.17,0.9);
   legend->AddEntry(l1_Pt_histo, "First lepton","f");
   legend->AddEntry(l2_Pt_histo, "Second lepton", "f");
   legend->AddEntry(l3_Pt_histo, "Third lepton","f");
   legend->AddEntry(l4_Pt_histo, "Fourth lepton", "f");
   legend->SetTextSize(0.03);
   legend->Draw();

   c->cd(2);

   c->cd(3);

   c->cd(4);

   c1->cd();

   Higgs_recMass_histo->Draw();

   TLegend *legend_Higgs = new TLegend(0.1,0.8,0.5,0.9);
   legend_Higgs->AddEntry(Higgs_recMass_histo,"Reconstructed Higgs","f");
   legend_Higgs->SetTextSize(0.03);
   legend_Higgs->Draw();
   
   SavePlots(c, "LeptonsVariables");
   SavePlots(c1, "HiggsReconstructedMass");
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
