#define Analyzer_cxx
#include "Analyzer.h"

Analyzer::Analyzer()
{

  Mass_histo_signal = new TH1F("Mass_histo_signal", "Reconstructed four lepton invariant mass", 50, 70., 170.);
  Mass_histo_background = new TH1F("Mass_histo_background", "Reconstructed four lepton invariant mass", 50, 70., 170.);

  Dkin_histo_signal = new TH1F("Dkin_histo_signal", "Kinematic discriminant", 1000, 0., 1.);
  Dkin_histo_background = new TH1F("Dkin_histo_background", "Kinematic discriminant", 1000, 0., 1.);

  histo_signal = new TH2F("histo_signal", "Mass vs KD", 50, 70., 170., 20, 0., 1.0);
  histo_background = new TH2F("histo_background", "Mass vs KD", 50, 70., 170., 20, 0., 1.0);
}

Analyzer::~Analyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

void Analyzer::PlotHistogram(TString input_file_name)
{
	// Create canvas for lepton histograms
	c = new TCanvas("c","c",900,700);
  	c->Divide(2,2);

	
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

      	Dkin = 1/(1+p_QQB_BKG_MCFM/p_GG_SIG_ghg2_1_ghz1_1_JHUGen);

      	// Calculate event weight
      	_event_weight = (137.0 * 1000 * xsec * overallEventWeight ) / gen_sum_weights; //1000 jer prebacujemo iz fb u pb

        if(input_file_name.Contains("ggH125"))
      	{
        	Mass_histo_signal->Fill(H.M(), _event_weight);
        	Dkin_histo_signal->Fill(Dkin, _event_weight);
        	histo_signal->Fill(H.M(),Dkin, _event_weight );
      	}
      	if(input_file_name.Contains("qqZZ"))
      	{
        	Mass_histo_background->Fill(H.M(), _event_weight);
        	Dkin_histo_background->Fill(1/(1+70.*p_QQB_BKG_MCFM/p_GG_SIG_ghg2_1_ghz1_1_JHUGen), _event_weight);
        	histo_background->Fill(H.M(),Dkin, _event_weight );
      	}

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

   

   // Drawing histograms for lepton variables
   c->cd(1);
   gPad->SetLeftMargin(0.15);

   LeptonPt_histo[0]->Draw("HIST");
   LeptonPt_histo[1]->Draw("HIST SAME");
   LeptonPt_histo[2]->Draw("HIST SAME");
   LeptonPt_histo[3]->Draw("HIST SAME");

   legend = CreateLegend(LeptonPt_histo[0], LeptonPt_histo[1], LeptonPt_histo[2], LeptonPt_histo[3]);
   legend->Draw();

   c->cd(2);
   gPad->SetLeftMargin(0.15);

   LeptonEta_histo[0]->Draw("HIST");
   LeptonEta_histo[1]->Draw("HIST SAME");
   LeptonEta_histo[2]->Draw("HIST SAME");
   LeptonEta_histo[3]->Draw("HIST SAME");

   legend = CreateLegend(LeptonEta_histo[0], LeptonEta_histo[1], LeptonEta_histo[2], LeptonEta_histo[3]);
   legend->Draw();

   c->cd(3);
   gPad->SetLeftMargin(0.15);

   LeptonPhi_histo[0]->Draw("HIST");
   LeptonPhi_histo[1]->Draw("HIST SAME");
   LeptonPhi_histo[2]->Draw("HIST SAME");
   LeptonPhi_histo[3]->Draw("HIST SAME");

   legend = CreateLegend(LeptonPhi_histo[0], LeptonPhi_histo[1], LeptonPhi_histo[2], LeptonPhi_histo[3]);
   legend->Draw();

   c->cd(4);
   gPad->SetLeftMargin(0.15);
   gPad->SetLogy();

   LeptonBDT_histo[0]->Draw("HIST");
   LeptonBDT_histo[1]->Draw("HIST SAME");
   LeptonBDT_histo[2]->Draw("HIST SAME");
   LeptonBDT_histo[3]->Draw("HIST SAME");

   legend = CreateLegend(LeptonBDT_histo[0], LeptonBDT_histo[1], LeptonBDT_histo[2], LeptonBDT_histo[3]);
   legend->Draw();

  

   if(input_file_name.Contains("ggH125")) SavePlots(c, "Leptons_signal");
   if(input_file_name.Contains("qqZZ")) SavePlots(c, "Leptons_background");

}

void Analyzer::PlotMass()
{
  c = new TCanvas("c2","c2",900,900);
  THStack *stack = new THStack("stack", "stack");

  gPad->SetLeftMargin(0.15);

  Mass_histo_signal->SetLineColor(kRed - 2);
  Mass_histo_signal->SetFillColor(kRed - 2);
  Mass_histo_signal->SetStats(0);

  Mass_histo_background->SetLineColor(kBlue - 2);
  Mass_histo_background->SetFillColor(kBlue - 2);
  Mass_histo_background->SetStats(0);

  stack->SetTitle("Reconstructed four-lepton mass");

  cout << "Ocekivani broj rekonstruiranih signalnih Higgsovih bozona za 137/fb je " << Mass_histo_signal->Integral() << endl;
  cout << "Ocekivani broj rekonstruiranih pozadinskih Higgsovih bozona za 137/fb je " << Mass_histo_background->Integral() << endl;

  stack->Add(Mass_histo_background);
  stack->Add(Mass_histo_signal);

  stack->Draw("HIST");

  stack->SetMaximum(1.4*stack->GetMaximum());
  stack->GetXaxis()->SetTitle("m_{4l} [GeV]");
  stack->GetYaxis()->SetTitle("Events / 2 GeV");

  TLegend *leg;
  leg = new TLegend(0.5,0.8,0.9,0.9);

  leg->AddEntry(Mass_histo_signal, "gluon-gluon fusion", "f");
  leg->AddEntry(Mass_histo_background, "q#bar{q} #rightarrow ZZ", "f");
  leg->SetTextSize(0.03);

  leg->Draw();

  SavePlots(c,"MassHistogram");
}

void Analyzer::PlotDkin()
{
  c = new TCanvas("c3","c3",900,900);
  c->Divide(2,2);

  c->cd(2);
  gPad->SetLeftMargin(0.15);

  TGraph *ROC = new TGraph();

  Dkin_histo_signal->Scale(1./Dkin_histo_signal->Integral());
  Dkin_histo_background->Scale(1./Dkin_histo_background->Integral());

  for(int i=0; i < 1000; i++)
  {
      float x = 1. - Dkin_histo_background->Integral(1, i+1);
      float y = 1. - Dkin_histo_signal->Integral(1,i+1);
      if ( x > 0.001 && y > 0.001 && x < 1.0 && y < 1.0) ROC->SetPoint(int(i),x,y);
  }
  ROC->SetMinimum(0.95);
  ROC->SetMaximum(1.0);

  ROC->SetMarkerStyle(20);
  ROC->SetMarkerSize(0.4);

  ROC->Draw("ap");

  ROC->GetXaxis()->SetLimits(0.00,0.05);
  ROC->GetXaxis()->SetTitle("Background efficiency");
  ROC->GetXaxis()->SetTitleFont(61);
  ROC->GetYaxis()->SetTitle("Signal efficiency");
  ROC->GetYaxis()->SetTitleFont(61);
  ROC->SetTitle("ROC curve");
  ROC->Draw("ap");
  c->Update();


  c->cd(1);
  gPad->SetLeftMargin(0.15);

  Dkin_histo_signal->Rebin(50);
  Dkin_histo_signal->SetLineColor(kRed - 2);
  Dkin_histo_signal->SetLineWidth(4);
  Dkin_histo_signal->SetStats(0);

  Dkin_histo_signal->GetXaxis()->SetTitle("D_{kin}");
  Dkin_histo_signal->GetYaxis()->SetTitle("Events / 0.1");


  Dkin_histo_background->Rebin(50);
  Dkin_histo_background->SetLineColor(kBlue - 2);
  Dkin_histo_background->SetLineWidth(4);
  Dkin_histo_background->SetStats(0);

  Dkin_histo_background->GetXaxis()->SetTitle("D_{kin}");
  Dkin_histo_background->GetYaxis()->SetTitle("Events / 0.1");

  Dkin_histo_signal->Draw("HIST");
  Dkin_histo_background->Draw("HIST SAME");

  Dkin_histo_signal->SetMaximum(1.1);

  TLegend *leg;
  leg = new TLegend(0.5,0.8,0.9,0.9);

  leg->AddEntry(Dkin_histo_signal, "gluon-gluon fusion", "f");
  leg->AddEntry(Dkin_histo_background, "q#bar{q} #rightarrow ZZ", "f");
  leg->SetTextSize(0.03);

  leg->Draw();

  c->cd(3);
  histo_background->Draw("COLZ");
  histo_background->SetMinimum(-0.01);
  histo_background->SetStats(0);
  histo_background->SetTitle("m_{4l} vs D_{kin} for background");
  histo_background->GetXaxis()->SetTitle("m_{4l} [GeV]");
  histo_background->GetYaxis()->SetTitle("D_{kin}");

  c->cd(4);
  histo_signal->Draw("COLZ");
  histo_signal->SetMinimum(-0.01);
  histo_signal->SetStats(0);
  histo_signal->SetTitle("m_{4l} vs D_{kin} for signal");
  histo_signal->GetXaxis()->SetTitle("m_{4l} [GeV]");
  histo_signal->GetYaxis()->SetTitle("D_{kin}");

  SavePlots(c,"KinematicDiscriminant");
}

TLegend* Analyzer::CreateLegend(TH1F *lepton_1, TH1F *lepton_2, TH1F *lepton_3, TH1F *lepton_4)
{
  TLegend *leg;

  leg = new TLegend(0.5,0.7,0.9,0.9);

  leg->AddEntry(lepton_1, "Frist lepton", "f");
  leg->AddEntry(lepton_2, "Second lepton", "f");
  leg->AddEntry(lepton_3, "Third lepton", "f");
  leg->AddEntry(lepton_4, "Fourth lepton", "f");

  leg->SetTextSize(0.03);

  return leg;
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
