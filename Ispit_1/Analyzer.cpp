#define Analyzer_cxx
#include "Analyzer.h"


void Analyzer::DrawHisto()
{
    //inicijalizacija objekata koje smo u Analyzer.h deklarirali
	c = new TCanvas("c","c", 1400,900); //platno
    c->Divide(2); //na 2 dijela

    // Define histograms
  	pT1_histo = new TH1F("pT1_histo", "Transverse momentum", 50, 0., 250.);//# binova, liva x granica, desna x granica --> razlika/#binova=širina bina
  	pT2_histo = new TH1F("pT2_histo", "Transverse momentum", 50, 0., 250.);
    recM_histo = new TH1F("recM_histo", "Invariant mass", 50, 0., 200.);

    function=new TF1("function","[0]*TMath::Exp(-x/[1])",0.,200); //[] i brojevi u njima označavaju redak nize zadane parametre funkcije
    function->SetParameters(1.,100.);

    // petlja po dogadjajima preuzeta iz metode Loop (nize) koja je automatski generirana pozivom metode MakeClass od strane TTree objekta
  	if (fChain == 0) return;

   	Long64_t nentries = fChain->GetEntriesFast();

   	Long64_t nbytes = 0, nb = 0;
   
   	for (Long64_t jentry=0; jentry<nentries; jentry++)
   	{
      	Long64_t ientry = LoadTree(jentry);
      	if (ientry < 0) break;
      	nb = fChain->GetEntry(jentry);   nbytes += nb;
      	// if (Cut(ientry) < 0) continue;

      	//if ( jentry > 10000 ) break;

        //za svaki event se pune potrebni histogrami; za p1 i p2 se na ovaj način za svaki novi event postave 4momenti;
        //recP za svaki event se postavi zbrajanjem trenutnih p1 i p2; metoda M() vraca masu objekta klase TLorentzVector koji ju je pozvao
      	pT1_histo->Fill(TMath::Sqrt(particle1_px*particle1_px + particle1_py*particle1_py));
      	pT2_histo->Fill(TMath::Sqrt(particle2_px*particle2_px + particle2_py*particle2_py));
        p1.SetPxPyPzE(particle1_px,particle1_py,particle1_pz,particle1_E);
        p2.SetPxPyPzE(particle2_px,particle2_py,particle2_pz,particle2_E);
        recP=p1+p2;
        recM_histo->Fill(recP.M());
    }

    // Remove stat box
    //sve postavke za prvi histogram
    pT2_histo->SetStats(0);
    pT2_histo->GetXaxis()->SetTitle("p_{T} [GeV]");
    pT2_histo->GetXaxis()->SetLabelSize(0.04);
    pT2_histo->GetYaxis()->SetTitle("Events / 5 GeV");
    pT2_histo->GetYaxis()->SetLabelSize(0.04);
    pT2_histo->GetYaxis()->SetTitleOffset(1.9);
    pT2_histo->SetLineColor(kBlue - 2);

    //sve postavke za drugi histogram (nije potrebno postavljati naslove jer je na istom platnu s prvim)
    pT1_histo->SetStats(0);
    pT1_histo->SetLineColor(kRed);
    pT1_histo->SetLineStyle(kDashed);

    legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(pT1_histo,"Particle 1", "f");//"f": draw a box with fill associated wit TAttFill if obj inherits TAttFill
    legend->AddEntry(pT2_histo,"Particle 2", "f");


    recM_histo->SetStats(0);
    recM_histo->GetXaxis()->SetTitle("m_{invariant} [GeV]");
    recM_histo->GetYaxis()->SetTitle("Events / 4 GeV");
    recM_histo->GetYaxis()->SetTitleOffset(1.8);
    recM_histo->SetMarkerColor(kBlack);
    recM_histo->SetMarkerStyle(7);

    gStyle->SetOptFit();
    //function->SetLineColor(kRed);

    legend_recP = new TLegend(0.7,0.7,0.9,0.9);
    legend_recP->AddEntry(recM_histo,"Invariant mass","p"); // "p": draw polymarker associated with TAttMarker if obj inherits from TAttMarker
    legend_recP->AddEntry(function,"Exp function","l"); // "l" stands for: draw line associated with TAttLine if obj inherits from TAttLine
    legend_recP->SetTextSize(0.03);

    //pT1_histo->SetMaximum(1.6*pT1_histo->GetMaximum());
    //pT2_histo->SetMaximum(1.6*pT2_histo->GetMaximum());

    c->cd(1);
    gPad->SetLeftMargin(0.15);

    pT2_histo->Draw("");
    pT1_histo->Draw("SAME");
    legend->Draw();

    c->cd(2);
    gPad->SetLeftMargin(0.15);

    recM_histo->Draw("P");//"P" is an option that stands for: Draw current marker at each bin except empty bins.
    recM_histo->Fit(function);// ovo obavezno mora biti ispod c->cd(#); kojem pripada, inace se nece nacrtati obje strane nego samo ta na kojoj je fit
    legend_recP->Draw();

    SavePlots(c, "ispit");
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

/*
#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH1F.h>
#include <TF1.h>
#include <TLorentzVector.h>

void Analyzer::Loop()
{
   TCanvas *c = new TCanvas("c","c");
   TH1F *histoPt1 = new TH1F("histoPt1","Transverse momentum",50,0.,250.); 
   TH1F *histoPt2 = new TH1F("histoPt2","Transverse momentum",50,0.,250.); 
   TH1F *recoMass = new TH1F("recoMass","Invariant mass",50,0,200);
   TF1 *function = new TF1("function","[0]*TMath::Exp(-x/[1])",0,200);
   function-> SetParameters(1.,100.);
   TLorentzVector particle1, particle2, newParticle;
   c->Divide(2);
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      histoPt1->Fill(TMath::Sqrt(particle1_px*particle1_px+particle1_py*particle1_py));
      histoPt2->Fill(TMath::Sqrt(particle2_px*particle2_px+particle2_py*particle2_py));
      particle1.SetPxPyPzE(particle1_px,particle1_py,particle1_pz,particle1_E);
      particle2.SetPxPyPzE(particle2_px,particle2_py,particle2_pz,particle2_E);
      newParticle = particle1 + particle2;
      recoMass->Fill(newParticle.M());
   }
  c->cd(1);
  gPad->SetLeftMargin(0.15);
  histoPt1->SetStats(0);
  histoPt2->SetStats(0);
 
  histoPt2->GetXaxis()->SetTitle("p_{T} [GeV]");
  histoPt2->GetXaxis()->SetLabelSize(0.04);
  histoPt2->GetYaxis()->SetTitle("Events / 5 GeV");
  histoPt2->GetYaxis()->SetTitleOffset(1.8);
  histoPt2->GetYaxis()->SetLabelSize(0.04);
  histoPt2->SetLineColor(kBlue -2);
  histoPt1->SetLineColor(kRed);
  histoPt1->SetLineStyle(kDashed);
  histoPt2->Draw();
  histoPt1->Draw("SAME");
  TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
  leg->AddEntry(histoPt1,"Particle 1", "f");
  leg->AddEntry(histoPt2,"Particle 2", "f");
  leg->Draw();

  c->cd(2);
  gPad->SetLeftMargin(0.15);
  recoMass->SetStats(0);
  recoMass->GetXaxis()->SetTitle("m_{2} [GeV]");
  recoMass->GetYaxis()->SetTitle("Events / 4 GeV");
  recoMass->GetYaxis()->SetTitleOffset(1.5);

  recoMass->SetMarkerColor(kBlack);
  recoMass->SetMarkerStyle(7);
  gStyle->SetOptFit();
  recoMass->Fit(function);
  //function->SetTitle("Invariant mass;m_{2} [GeV];Events / 4 GeV");
  //function->SetLineColor(kRed);
  recoMass->Draw("P");
  TLegend *leg1 = new TLegend(0.6,0.7,0.9,0.9);
  leg1->AddEntry(recoMass,"Data Invariant mass","p");
  leg1->AddEntry(function,"Exponential function","l");
  leg1->Draw();


  c->SaveAs("histogram2.pdf");
}
*/
