//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Aug 26 10:10:26 2020 by ROOT version 6.22/00
// from TTree Tree/DiPhoton events
// found on file: ../../../public/data/HiggsSearch/CMSData.root
//////////////////////////////////////////////////////////

#ifndef Analyzer_h
#define Analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TLegend.h>
#include <TH1.h>
#include <TH2.h>
#include <TLorentzVector.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include<string>
#include <iostream>
#include<fstream>
using namespace std;

// Header file for the classes stored in the TTree if any.

class Analyzer {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         particle1_px;
   Float_t         particle1_py;
   Float_t         particle1_pz;
   Float_t         particle1_E;
   Float_t         particle2_px;
   Float_t         particle2_py;
   Float_t         particle2_pz;
   Float_t         particle2_E;

   // List of branches
   TBranch        *b_particle1_px;   //!
   TBranch        *b_particle1_py;   //!
   TBranch        *b_particle1_pz;   //!
   TBranch        *b_particle1_E;   //!
   TBranch        *b_particle2_px;   //!
   TBranch        *b_particle2_py;   //!
   TBranch        *b_particle2_pz;   //!
   TBranch        *b_particle2_E;   //!

   Analyzer(TTree *tree=0);
   virtual ~Analyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void     DrawHisto(TString);
   virtual void     SavePlots(TCanvas*, TString);

   private:
   TH1F *histo;
   TH1F *pT1_histo, *pT2_histo, *resP_histo;
   TCanvas *c;
   TLorentzVector *resP, *p1, *p2;
};

#endif

#ifdef Analyzer_cxx
Analyzer::Analyzer(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../../../public/data/HiggsSearch/CMSData.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../../../public/data/HiggsSearch/CMSData.root");
      }
      f->GetObject("Tree",tree);

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

   fChain->SetBranchAddress("particle1_px", &particle1_px, &b_particle1_px);
   fChain->SetBranchAddress("particle1_py", &particle1_py, &b_particle1_py);
   fChain->SetBranchAddress("particle1_pz", &particle1_pz, &b_particle1_pz);
   fChain->SetBranchAddress("particle1_E", &particle1_E, &b_particle1_E);
   fChain->SetBranchAddress("particle2_px", &particle2_px, &b_particle2_px);
   fChain->SetBranchAddress("particle2_py", &particle2_py, &b_particle2_py);
   fChain->SetBranchAddress("particle2_pz", &particle2_pz, &b_particle2_pz);
   fChain->SetBranchAddress("particle2_E", &particle2_E, &b_particle2_E);
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
