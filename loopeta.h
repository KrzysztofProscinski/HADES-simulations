//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Nov  4 18:16:07 2021 by ROOT version 6.22/06
// from TTree nteta/pp_eta
// found on file: pp_ppeta.root
//////////////////////////////////////////////////////////

#ifndef loopeta_h
#define loopeta_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class loopeta {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         eta_p;
   Float_t         eta_theta;
   Float_t         ep_p;
   Float_t         ep_theta;
   Float_t         em_p;
   Float_t         em_theta;
   Float_t         p1_p;
   Float_t         p1_theta;
   Float_t         p2_p;
   Float_t         p2_theta;
   Float_t         g_p;
   Float_t         g_theta;
   Float_t         minv;
   Float_t         w;
   Float_t         hadacc;
   Float_t         opang;
   Float_t	cosnlab;
   Float_t	cosncom;
   Float_t	rap;
   Float_t	minvee;
   Float_t	minveepp;
   Float_t	minveeg;
   Float_t	minvpp;
   Float_t	minvg;

   // List of branches
   TBranch        *b_eta_p;   //!
   TBranch        *b_eta_theta;   //!
   TBranch        *b_ep_p;   //!
   TBranch        *b_ep_theta;   //!
   TBranch        *b_em_p;   //!
   TBranch        *b_em_theta;   //!
   TBranch        *b_p1_p;   //!
   TBranch        *b_p1_theta;   //!
   TBranch        *b_p2_p;   //!
   TBranch        *b_p2_theta;   //!
   TBranch        *b_g_p;   //!
   TBranch        *b_g_theta;   //!
   TBranch        *b_minv;   //!
   TBranch        *b_w;   //!
   TBranch        *b_hadacc;   //!
   TBranch        *b_opang;   //!
   TBranch        *b_cosnlab;
   TBranch        *b_cosncom;
   TBranch        *b_rap;
   TBranch        *b_minvee;
   TBranch        *b_minveepp;
   TBranch        *b_minveeg;
   TBranch        *b_minvpp;
   TBranch        *b_minvg;
   
   loopeta(TTree *tree=0);
   virtual ~loopeta();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef loopeta_cxx
loopeta::loopeta(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("pp_ppeta.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("pp_ppeta.root");
      }
      f->GetObject("nteta",tree);

   }
   Init(tree);
}

loopeta::~loopeta()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t loopeta::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t loopeta::LoadTree(Long64_t entry)
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

void loopeta::Init(TTree *tree)
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

   fChain->SetBranchAddress("eta_p", &eta_p, &b_eta_p);
   fChain->SetBranchAddress("eta_theta", &eta_theta, &b_eta_theta);
   fChain->SetBranchAddress("ep_p", &ep_p, &b_ep_p);
   fChain->SetBranchAddress("ep_theta", &ep_theta, &b_ep_theta);
   fChain->SetBranchAddress("em_p", &em_p, &b_em_p);
   fChain->SetBranchAddress("em_theta", &em_theta, &b_em_theta);
   fChain->SetBranchAddress("p1_p", &p1_p, &b_p1_p);
   fChain->SetBranchAddress("p1_theta", &p1_theta, &b_p1_theta);
   fChain->SetBranchAddress("p2_p", &p2_p, &b_p2_p);
   fChain->SetBranchAddress("p2_theta", &p2_theta, &b_p2_theta);
   fChain->SetBranchAddress("g_p", &g_p, &b_g_p);
   fChain->SetBranchAddress("g_theta", &g_theta, &b_g_theta);
   fChain->SetBranchAddress("minv", &minv, &b_minv);
   fChain->SetBranchAddress("w", &w, &b_w);
   fChain->SetBranchAddress("hadacc", &hadacc, &b_hadacc);
   fChain->SetBranchAddress("opang", &opang, &b_opang);
   fChain->SetBranchAddress("cosnlab", &cosnlab, &b_cosnlab);
   fChain->SetBranchAddress("cosncom", &cosncom, &b_cosncom);
   fChain->SetBranchAddress("rap", &rap, &b_rap);
   fChain->SetBranchAddress("minvee", &minvee, &b_minvee);
   fChain->SetBranchAddress("minveepp", &minveepp, &b_minveepp);
   fChain->SetBranchAddress("minveeg", &minveeg, &b_minveeg);
   fChain->SetBranchAddress("minvpp", &minvpp, &b_minvpp);
   fChain->SetBranchAddress("minvg", &minvg, &b_minvg);
   Notify();
}

Bool_t loopeta::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void loopeta::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t loopeta::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef loopeta_cxx
