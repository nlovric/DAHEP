#define Analyzer_cxx
#include "Analyzer.h"


void Analyzer::PlotHistogram(TString input_file_name)
{
	// Create canvas for lepton histograms
	c = new TCanvas("c","c",900,700);
  	c->Divide(2,2);

  	// Create canvas for reconstructed Higgs histogram
	c1 = new TCanvas("c1","c1",900,700);

	
	// Define histograms
  	for (int i = 0; i < 4; i++)
  	{
   		histo_name = "LeptonPt_histo_" + to_string(i+1);
    	LeptonPt_histo[i] = new TH1F(histo_name, "Transverse momentum", 50, 0., 150.);

    	histo_name = "LeptonEta_histo_" + to_string(i+1);
    	LeptonEta_histo[i] = new TH1F(histo_name, "Rapidity", 50, -2.5, 2.5);

    	histo_name = "LeptonPhi_histo_" + to_string(i+1);
    	LeptonPhi_histo[i] = new TH1F(histo_name, "Azimuthal angle", 40, -4.0, 4.0);

    	histo_name = "LeptonBDT_histo_" + to_string(i+1);
    	LeptonBDT_histo[i] = new TH1F(histo_name, "BDT score", 20, -1.0, 1.0);

  	}
  	// Prva (losija) verzija:
	//l1_Pt_histo = new TH1F("l1_Pt_histo","Histogram of the 1st leptons p_T", 50, 0., 150.);
	//l2_Pt_histo = new TH1F("l2_Pt_histo","Histogram of the 2nd leptons p_T", 50, 0., 150.);
	//l3_Pt_histo = new TH1F("l3_Pt_histo","Histogram of the 3rd leptons p_T", 50, 0., 150.);
	//l4_Pt_histo = new TH1F("l4_Pt_histo","Histogram of the 4th leptons p_T", 50, 0., 150.);
	Higgs_recMass_histo = new TH1F("Higgs_pT_histo", "Histogram of Higgs p_T", 50, 90., 140.);

  	input_file = new TFile(input_file_name);

  	hCounters = (TH1F*)input_file->Get("ZZTree/Counters");
  	gen_sum_weights = (Long64_t)hCounters->GetBinContent(40);

  	input_tree = (TTree*)input_file->Get("ZZTree/candTree");
  	Init(input_tree);

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

      	for (int i = 0; i < 4; i++)
      	{
    		LeptonPt_histo[i]->Fill(LepPt->at(i), _event_weight);
    		LeptonEta_histo[i]->Fill(LepEta->at(i), _event_weight);
        	LeptonPhi_histo[i]->Fill(LepPhi->at(i), _event_weight);
        	LeptonBDT_histo[i]->Fill(LepBDT->at(i), _event_weight);
      	}

      	// Reconstruct Higgs from decay products
      	l1.SetPtEtaPhiM(LepPt->at(0), LepEta->at(0), LepPhi->at(0), 0.);
      	l2.SetPtEtaPhiM(LepPt->at(1), LepEta->at(1), LepPhi->at(1), 0.);
      	l3.SetPtEtaPhiM(LepPt->at(2), LepEta->at(2), LepPhi->at(2), 0.);
      	l4.SetPtEtaPhiM(LepPt->at(3), LepEta->at(3), LepPhi->at(3), 0.);

      	if ((LepLepId->at(0) + LepLepId->at(1)) == 0 && (LepLepId->at(2) + LepLepId->at(3)) == 0)
      	{
        	Z1 = l1 + l2;
        	Z2 = l3 + l4;

        	H = Z1 + Z2;
      	}

      	// Calculate event weight
      	_event_weight = (137.0 * 1000 * xsec * overallEventWeight ) / gen_sum_weights; //1000 jer prebacujemo iz fb u pb

      	Higgs_recMass_histo->Fill(H.M(), _event_weight);
   }

   //Plotting of the histograms

   for (int i = 0; i < 4; i++)
   {
     	// Remove stat box
     	LeptonPt_histo[i]->SetStats(0);
    	LeptonEta_histo[i]->SetStats(0);
     	LeptonPhi_histo[i]->SetStats(0);
     	LeptonBDT_histo[i]->SetStats(0);

     	// Set axis titles
     	LeptonPt_histo[i]->GetXaxis()->SetTitle("p_{T} [GeV]");
     	LeptonPt_histo[i]->GetXaxis()->SetLabelSize(0.04);
     	LeptonPt_histo[i]->GetYaxis()->SetTitle("Events / 3 GeV");
     	LeptonPt_histo[i]->GetYaxis()->SetTitleOffset(1.9);
     	LeptonPt_histo[i]->GetYaxis()->SetLabelSize(0.04);

     	LeptonPt_histo[i]->SetMaximum(1.6*LeptonPt_histo[3]->GetMaximum());

     	LeptonEta_histo[i]->GetXaxis()->SetTitle("#eta");
     	LeptonEta_histo[i]->GetXaxis()->SetLabelSize(0.04);
     	LeptonEta_histo[i]->GetYaxis()->SetTitle("Events / 0.1");
     	LeptonEta_histo[i]->GetYaxis()->SetTitleOffset(1.8);
     	LeptonEta_histo[i]->GetYaxis()->SetLabelSize(0.04);

     	LeptonEta_histo[i]->SetMaximum(1.8*LeptonEta_histo[3]->GetMaximum());

     	LeptonPhi_histo[i]->GetXaxis()->SetTitle("#Phi");
     	LeptonPhi_histo[i]->GetXaxis()->SetLabelSize(0.04);
     	LeptonPhi_histo[i]->GetYaxis()->SetTitle("Events / 0.2");
     	LeptonPhi_histo[i]->GetYaxis()->SetTitleOffset(1.8);
     	LeptonPhi_histo[i]->GetYaxis()->SetLabelSize(0.04);

     	LeptonPhi_histo[i]->SetMaximum(1.8*LeptonPhi_histo[3]->GetMaximum());

     	LeptonBDT_histo[i]->GetXaxis()->SetTitle("BDT Score");
     	LeptonBDT_histo[i]->GetXaxis()->SetLabelSize(0.04);
     	LeptonBDT_histo[i]->GetYaxis()->SetTitle("Events / 0.1");
     	LeptonBDT_histo[i]->GetYaxis()->SetTitleOffset(1.8);
     	LeptonBDT_histo[i]->GetYaxis()->SetLabelSize(0.04);

     	LeptonBDT_histo[i]->SetMaximum(200*LeptonBDT_histo[3]->GetMaximum());
   }
   // Remove stat box for Higgs
   Higgs_recMass_histo->SetStats(0);
   // Set title and axis titles for Higgs
   Higgs_recMass_histo->SetTitle("Reconstructed four-lepton mass");
   Higgs_recMass_histo->GetXaxis()->SetTitle("m_{4l} [GeV]");
   //Higgs_recMass_histo->GetXaxis()->SetLabelSize(0.04);
   Higgs_recMass_histo->GetYaxis()->SetTitle("Events / 2 GeV");
   //Higgs_recMass_histo->GetYaxis()->SetLabelSize(0.04);
   //Higgs_recMass_histo->GetYaxis()->SetTitleOffset(1.5);

   Higgs_recMass_histo->SetMaximum(1.5*Higgs_recMass_histo->GetMaximum());

   // Coloring
   LeptonPt_histo[0]->SetLineColor(kRed - 2);
   LeptonEta_histo[0]->SetLineColor(kRed - 2);
   LeptonPhi_histo[0]->SetLineColor(kRed - 2);
   LeptonBDT_histo[0]->SetLineColor(kRed - 2);

   LeptonPt_histo[0]->SetFillColor(kRed - 2);
   LeptonEta_histo[0]->SetFillColor(kRed - 2);
   LeptonPhi_histo[0]->SetFillColor(kRed - 2);
   LeptonBDT_histo[0]->SetFillColor(kRed - 2);

   LeptonPt_histo[1]->SetLineColor(kBlue - 2);
   LeptonEta_histo[1]->SetLineColor(kBlue - 2);
   LeptonPhi_histo[1]->SetLineColor(kBlue - 2);
   LeptonBDT_histo[1]->SetLineColor(kBlue - 2);

   LeptonPt_histo[1]->SetLineStyle(kDashed);
   LeptonEta_histo[1]->SetLineStyle(kDashed);
   LeptonPhi_histo[1]->SetLineStyle(kDashed);
   LeptonBDT_histo[1]->SetLineStyle(kDashed);

   LeptonPt_histo[2]->SetLineColor(kGreen - 2);
   LeptonEta_histo[2]->SetLineColor(kGreen - 2);
   LeptonPhi_histo[2]->SetLineColor(kGreen - 2);
   LeptonBDT_histo[2]->SetLineColor(kGreen - 2);

   LeptonPt_histo[2]->SetLineStyle(kDashed);
   LeptonEta_histo[2]->SetLineStyle(kDashed);
   LeptonPhi_histo[2]->SetLineStyle(kDashed);
   LeptonBDT_histo[2]->SetLineStyle(kDashed);

   LeptonPt_histo[3]->SetLineColor(kGray);
   LeptonEta_histo[3]->SetLineColor(kGray);
   LeptonPhi_histo[3]->SetLineColor(kGray);
   LeptonBDT_histo[3]->SetLineColor(kGray);

   LeptonPt_histo[3]->SetLineStyle(kDashed);
   LeptonEta_histo[3]->SetLineStyle(kDashed);
   LeptonPhi_histo[3]->SetLineStyle(kDashed);
   LeptonBDT_histo[3]->SetLineStyle(kDashed);

   // Coloring for Higgs
   Higgs_recMass_histo->SetLineColor(kRed + 2);
   Higgs_recMass_histo->SetFillColor(kRed + 2);

   // Drawing histograms for lepton variables
   c->cd(1);
   gPad->SetLeftMargin(0.15);

   LeptonPt_histo[0]->Draw("HIST");
   LeptonPt_histo[1]->Draw("HIST SAME");
   LeptonPt_histo[2]->Draw("HIST SAME");
   LeptonPt_histo[3]->Draw("HIST SAME");

   TLegend *legend = new TLegend(0.5,0.7,0.9,0.9); //za dodatnu česticu dodaješ 0.04 na 1. i 3. mjesto
   legend->AddEntry(LeptonPt_histo[0], "First lepton","f");
   legend->AddEntry(LeptonPt_histo[1], "Second lepton", "f");
   legend->AddEntry(LeptonPt_histo[2], "Third lepton","f");
   legend->AddEntry(LeptonPt_histo[3], "Fourth lepton", "f");
   legend->SetTextSize(0.03);
   legend->Draw();

   c->cd(2);
   gPad->SetLeftMargin(0.15);

   LeptonEta_histo[0]->Draw("HIST");
   LeptonEta_histo[1]->Draw("HIST SAME");
   LeptonEta_histo[2]->Draw("HIST SAME");
   LeptonEta_histo[3]->Draw("HIST SAME");

   legend = new TLegend(0.5,0.7,0.9,0.9); //za dodatnu česticu dodaješ 0.04 na 1. i 3. mjesto
   legend->AddEntry(LeptonEta_histo[0], "First lepton","f");
   legend->AddEntry(LeptonEta_histo[1], "Second lepton", "f");
   legend->AddEntry(LeptonEta_histo[2], "Third lepton","f");
   legend->AddEntry(LeptonEta_histo[3], "Fourth lepton", "f");
   legend->SetTextSize(0.03);
   legend->Draw();

   c->cd(3);
   gPad->SetLeftMargin(0.15);

   LeptonPhi_histo[0]->Draw("HIST");
   LeptonPhi_histo[1]->Draw("HIST SAME");
   LeptonPhi_histo[2]->Draw("HIST SAME");
   LeptonPhi_histo[3]->Draw("HIST SAME");

   legend = new TLegend(0.5,0.7,0.9,0.9); //za dodatnu česticu dodaješ 0.04 na 1. i 3. mjesto
   legend->AddEntry(LeptonPhi_histo[0], "First lepton","f");
   legend->AddEntry(LeptonPhi_histo[1], "Second lepton", "f");
   legend->AddEntry(LeptonPhi_histo[2], "Third lepton","f");
   legend->AddEntry(LeptonPhi_histo[3], "Fourth lepton", "f");
   legend->SetTextSize(0.03);
   legend->Draw();

   c->cd(4);
   gPad->SetLeftMargin(0.15);
   gPad->SetLogy();

   LeptonBDT_histo[0]->Draw("HIST");
   LeptonBDT_histo[1]->Draw("HIST SAME");
   LeptonBDT_histo[2]->Draw("HIST SAME");
   LeptonBDT_histo[3]->Draw("HIST SAME");

   legend = new TLegend(0.5,0.7,0.9,0.9); //za dodatnu česticu dodaješ 0.04 na 1. i 3. mjesto
   legend->AddEntry(LeptonBDT_histo[0], "First lepton","f");
   legend->AddEntry(LeptonBDT_histo[1], "Second lepton", "f");
   legend->AddEntry(LeptonBDT_histo[2], "Third lepton","f");
   legend->AddEntry(LeptonBDT_histo[3], "Fourth lepton", "f");
   legend->SetTextSize(0.03);
   legend->Draw();

   // Drawing reconstructed Higgs
   c1->cd();
   gPad->SetLeftMargin(0.15);

   Higgs_recMass_histo->Draw("HIST");

   TLegend *legend_Higgs = new TLegend(0.5,0.8,0.9,0.9);
   legend_Higgs->AddEntry(Higgs_recMass_histo,"gluon-gluon fusion","f");
   legend_Higgs->SetTextSize(0.03);
   legend_Higgs->Draw();

   // Calculate the expected number of reconstructed Higgs bosons at 137/fb
   cout << "Ocekivani broj rekonstruiranih Higgsovih bozona za 137/fb je " << Higgs_recMass_histo->Integral() << endl;
   
   SavePlots(c, "LeptonsVariables");
   SavePlots(c1, "HiggsReconstructedMass");
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
