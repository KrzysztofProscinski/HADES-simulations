//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Oct 19 11:46:48 2021 by ROOT version 6.22/06
// from TTree nt2/pp_ppa
// found on file: pp_ppa.root
//////////////////////////////////////////////////////////

#ifndef loopa_h
#define loopa_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class loopa {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         pip_p;
   Float_t         pip_theta;
   Float_t         pim_p;
   Float_t         pim_theta;
   Float_t         p_p;
   Float_t         p_theta;
   Float_t         n_p;
   Float_t         n_theta;
   Float_t         kp_p;
   Float_t         kp_theta;
   Float_t         k0_p;
   Float_t         k0_theta;
   Float_t         w;
   Float_t         hadacc;
   Float_t         opang;
   Float_t	cosalab;
   Float_t	cosacom;
   Float_t	rap;
   Float_t	minvpipi;
   Float_t	minvpipik;
   Float_t	minvpipipk;
   Float_t	minvk;
   Float_t	minvpk;
   Float_t	pdiff;

   // List of branches
   TBranch        *b_pip_p;   //!
   TBranch        *b_pip_theta;   //!
   TBranch        *b_pim_p;   //!
   TBranch        *b_pim_theta;   //!
   TBranch        *b_p_p;   //!
   TBranch        *b_p_theta;   //!
   TBranch        *b_n_p;   //!
   TBranch        *b_n_theta;   //!
   TBranch        *b_kp_p;   //!
   TBranch        *b_kp_theta;   //!
   TBranch        *b_k0_p;   //!
   TBranch        *b_k0_theta;   //!
   TBranch        *b_w;   //!
   TBranch        *b_hadacc;   //!
   TBranch        *b_opang;   //!
   TBranch        *b_cosalab;
   TBranch        *b_cosacom;
   TBranch        *b_rap;
   TBranch        *b_minvpipi;
   TBranch        *b_minvpipipk;
   TBranch        *b_minvpipik;
   TBranch        *b_minvpk;
   TBranch        *b_minvk;
   TBranch        *b_pdiff;

   loopa(TTree *tree=0);
   virtual ~loopa();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef loopa_cxx
loopa::loopa(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("pp_ppa.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("pp_ppa.root");
      }
      f->GetObject("nta",tree);

   }
   Init(tree);
}

loopa::~loopa()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t loopa::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t loopa::LoadTree(Long64_t entry)
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

void loopa::Init(TTree *tree)
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

   fChain->SetBranchAddress("pip_p", &pip_p, &b_pip_p);
   fChain->SetBranchAddress("pip_theta", &pip_theta, &b_pip_theta);
   fChain->SetBranchAddress("pim_p", &pim_p, &b_pim_p);
   fChain->SetBranchAddress("pim_theta", &pim_theta, &b_pim_theta);
   fChain->SetBranchAddress("p_p", &p_p, &b_p_p);
   fChain->SetBranchAddress("p_theta", &p_theta, &b_p_theta);
   fChain->SetBranchAddress("n_p", &n_p, &b_n_p);
   fChain->SetBranchAddress("n_theta", &n_theta, &b_n_theta);
   fChain->SetBranchAddress("kp_p", &kp_p, &b_kp_p);
   fChain->SetBranchAddress("kp_theta", &kp_theta, &b_kp_theta);
   fChain->SetBranchAddress("k0_p", &k0_p, &b_k0_p);
   fChain->SetBranchAddress("k0_theta", &k0_theta, &b_k0_theta);
   fChain->SetBranchAddress("w", &w, &b_w);
   fChain->SetBranchAddress("hadacc", &hadacc, &b_hadacc);
   fChain->SetBranchAddress("opang", &opang, &b_opang);
   fChain->SetBranchAddress("cosalab", &cosalab, &b_cosalab);
   fChain->SetBranchAddress("cosacom", &cosacom, &b_cosacom);
   fChain->SetBranchAddress("rap", &rap, &b_rap);
   fChain->SetBranchAddress("minvpipi", &minvpipi, &b_minvpipi);
   fChain->SetBranchAddress("minvpipipk", &minvpipipk, &b_minvpipipk);
   fChain->SetBranchAddress("minvpipik", &minvpipik, &b_minvpipik);
   fChain->SetBranchAddress("minvpk", &minvpk, &b_minvpk);
   fChain->SetBranchAddress("minvk", &minvk, &b_minvk);
   fChain->SetBranchAddress("pdiff", &pdiff, &b_pdiff);
   Notify();
}

Bool_t loopa::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void loopa::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t loopa::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef loop_cxx
