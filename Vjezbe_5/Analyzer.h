//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Nov  3 14:11:42 2019 by ROOT version 6.18/04
// from TTree t/decay particle analysis
// found on file: Analysis.root
//////////////////////////////////////////////////////////

#ifndef Analyzer_h
#define Analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TString.h>
#include <TLegend.h>
#include <TLorentzVector.h>

// Header file for the classes stored in the TTree if any.
#include<string>
#include <iostream>
#include<fstream>
using namespace std;

class Analyzer {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           evnum;
   Short_t         n1;
   Bool_t          isB1;
   Float_t         m1;
   Float_t         px1;
   Float_t         py1;
   Float_t         pz1;
   Float_t         E1;
   Float_t         pT1;
   Short_t         n2;
   Bool_t          isB2;
   Float_t         m2;
   Float_t         px2;
   Float_t         py2;
   Float_t         pz2;
   Float_t         E2;
   Float_t         pT2;

   // List of branches
   TBranch        *b__EventNumber;   //!
   TBranch        *b__product1_Name;   //!
   TBranch        *b__product1_isBoson;   //!
   TBranch        *b__product1_mass_product1_px;   //!
   TBranch        *b__product1_px;   //!
   TBranch        *b__product1_py;   //!
   TBranch        *b__product1_pz;   //!
   TBranch        *b__product1_E;   //!
   TBranch        *b__product1_pT;   //!
   TBranch        *b__product2_Name;   //!
   TBranch        *b__product2_isBoson;   //!
   TBranch        *b__product2_mass_product1_px;   //!
   TBranch        *b__product2_px;   //!
   TBranch        *b__product2_py;   //!
   TBranch        *b__product2_pz;   //!
   TBranch        *b__product2_E;   //!
   TBranch        *b__product2_pT;   //!

   Analyzer(TTree *tree=0);
   virtual ~Analyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   virtual void PlotHistogram();

private:
   TH1F *pT1_histo;
   TH1F *pT2_histo;
   TH1F *Higgs_pT_histo;
   TCanvas *c;
   TLorentzVector *Higgs;

   void SavePlots(TCanvas *c, TString name);
};

#endif

#ifdef Analyzer_cxx
Analyzer::Analyzer(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Analysis.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Analysis.root");
      }
      f->GetObject("t",tree);

   }
   Init(tree);
}

Analyzer::~Analyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Analyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Analyzer::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Analyzer::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("evnum", &evnum, &b__EventNumber);
   fChain->SetBranchAddress("n1", &n1, &b__product1_Name);
   fChain->SetBranchAddress("isB1", &isB1, &b__product1_isBoson);
   fChain->SetBranchAddress("m1", &m1, &b__product1_mass_product1_px);
   fChain->SetBranchAddress("px1", &px1, &b__product1_px);
   fChain->SetBranchAddress("py1", &py1, &b__product1_py);
   fChain->SetBranchAddress("pz1", &pz1, &b__product1_pz);
   fChain->SetBranchAddress("E1", &E1, &b__product1_E);
   fChain->SetBranchAddress("pT1", &pT1, &b__product1_pT);
   fChain->SetBranchAddress("n2", &n2, &b__product2_Name);
   fChain->SetBranchAddress("isB2", &isB2, &b__product2_isBoson);
   fChain->SetBranchAddress("m2", &m2, &b__product2_mass_product1_px);
   fChain->SetBranchAddress("px2", &px2, &b__product2_px);
   fChain->SetBranchAddress("py2", &py2, &b__product2_py);
   fChain->SetBranchAddress("pz2", &pz2, &b__product2_pz);
   fChain->SetBranchAddress("E2", &E2, &b__product2_E);
   fChain->SetBranchAddress("pT2", &pT2, &b__product2_pT);
   Notify();
}

Bool_t Analyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Analyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Analyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Analyzer_cxx
