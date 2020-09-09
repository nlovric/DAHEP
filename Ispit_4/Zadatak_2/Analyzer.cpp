#define Analyzer_cxx
#include "Analyzer.h"

void Analyzer::DrawHisto(){
	//inicijalizacija objekata koje smo u Analyzer.h deklarirali
	c = new TCanvas("c","c", 1400,900); //platno
    c->Divide(2); //na 2 dijela

    sig_histo = new TH1F("sig_histo", "Signal", 50, 0., 100.);//# binova, liva x granica, desna x granica --> razlika/#binova=širina bina
  	bac_histo = new TH1F("bac_histo", "Background", 50, 0., 100.);
  	D_histo = new TH2F("bac_histo", "Background", 50, 0., 100.,50, 0., 100.);

  

  	Init(background);
  	

  	 // petlja po dogadjajima preuzeta iz metode Loop (nize) koja je automatski generirana pozivom metode MakeClass od strane TTree objekta
  	//if (fChain == 0) return;

   	 Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry< nentries;jentry++)
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      	bac_histo->Fill(ele_pt);
    }

  	Init(signal);

  	 // petlja po dogadjajima preuzeta iz metode Loop (nize) koja je automatski generirana pozivom metode MakeClass od strane TTree objekta
  	//if (fChain == 0) return;

   	nentries = fChain->GetEntriesFast();

   nbytes = 0, nb = 0;

   for (Long64_t jentry=0; jentry< nentries;jentry++)
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      	sig_histo->Fill(ele_pt);
    }

    for (int i=0;i<50;i++)
	{
  		D_histo->Fill(sig_histo->GetBinContent(i), bac_histo->GetBinContent(i), 1);
	}

    c->cd(1);
     // Remove stat box
    //sve postavke za prvi histogram
    bac_histo->SetStats(0);
    bac_histo->Scale(1/bac_histo->Integral());
    sig_histo->Scale(1/sig_histo->Integral());
    bac_histo->GetXaxis()->SetTitle("ele_p_{T} [GeV]");
    bac_histo->GetXaxis()->SetLabelSize(0.04);
    bac_histo->GetYaxis()->SetTitle("Events / 2 GeV");
    bac_histo->GetYaxis()->SetLabelSize(0.04);
    bac_histo->GetYaxis()->SetTitleOffset(1.9);
    bac_histo->SetLineColor(kBlue);

    sig_histo->SetStats(0);
    sig_histo->SetLineColor(kRed);

    
    gPad->SetLeftMargin(0.15);

    bac_histo->Draw("HIST");
    sig_histo->Draw("HIST SAME");
    //legend->Draw();
    if ( sig_histo->GetMaximum() > bac_histo->GetMaximum()) bac_histo->SetMaximum(1.3*sig_histo->GetMaximum());


    c->cd(2);
    D_histo->SetStats(0);
    D_histo->GetXaxis()->SetTitle("sig_ele_p_{T} [GeV]");
    D_histo->GetXaxis()->SetLabelSize(0.04);
    D_histo->GetYaxis()->SetTitle("bac_ele_p_{T} [GeV]");
    D_histo->GetYaxis()->SetLabelSize(0.04);
    D_histo->GetYaxis()->SetTitleOffset(1.9);
    D_histo->Draw("COLZ");

    SavePlots(c, "ispit_4");

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
