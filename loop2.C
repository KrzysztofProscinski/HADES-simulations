#define loop_cxx
#include "loop2.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


void loop2::Loop()
{
//   In a ROOT session, you can do:
//      root> .L loop2.C
//      root> loop2 t
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

//fChain->SetBranchStatus("*",0);
//fChain->SetBranchStatus("minv",1);

   if (fChain == 0) return;
  
   Long64_t nentries = fChain->GetEntriesFast();

// histograms: definitions

	TH2F *ee_theta = new TH2F("ee_theta","e^{+} and e^{-} angles;e^{+} angle (degree);e^{-} angle (degree)",180,0,180,180,0,180);
	TH2F *pp_theta = new TH2F("pp_theta","p_{1} and p_{2} angles;p_{1} angle (degree);p_{2} angle (degree)",180,0,180,180,0,180);
	TH2F *ee_p = new TH2F("ee_p","e^{+} and e^{-} momenta;e^{+} momentum (GeV);e^{-} momentum (GeV)",200,0,4,200,0,4);
	TH2F *pp_p = new TH2F("pp_p","p_{1} and p_{2} momenta;p_{1} momentum (GeV);p_{2} momentum (GeV)",200,0,5,200,0,5);
	TH1F *cos_omegacom = new TH1F("cos(omega)com","cos(#theta) in C.o.M;cos(#theta);Counts",401,-1.01,1.01);
	TH1F *cos_omegalab = new TH1F("cos(omega)lab","cos(#theta) in LAB;cos(#theta);Counts",401,-1.01,1.01);
	TH1F *rap_omega = new TH1F("rapidity(omega)","rapidity;y;Counts",250,0.,2.5);
	TH1F *hm_ee = new TH1F("hm_ee","Invariant mass of e^{+}, e^{-};Invariant mass (GeV);Counts",250,0.,1.0);
	TH1F *hm_eepp = new TH1F("hm_eepp","Invariant mass of e^{+}, e^{-}, p_{1}, p_{2};Invariant mass (GeV);Counts",400,0.,4.);
	TH1F *hm_pp = new TH1F("hm_pp","Invariant mass of p_{1}, p_{2};Invariant mass (GeV);Counts",300,1.5,3.0);


// a loop

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);

// histograms: filling
	ee_theta->Fill(ep_theta*57.2958,em_theta*57.2958);
	pp_theta->Fill(p1_theta*57.2958,p2_theta*57.2958);
	ee_p->Fill(ep_p,em_p);
	pp_p->Fill(p1_p,p2_p);
	cos_omegacom->Fill(coswcom);
	cos_omegalab->Fill(coswlab);
	rap_omega->Fill(rap);
	hm_ee->Fill(minvee);
	hm_eepp->Fill(minveepp);
	hm_pp->Fill(minvpp);

// end part of the loop

      nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }	//tu petla sie konczy

// errors
for(Int_t i=1;i<=900; i++)
{
	Int_t bin1 = cos_omegacom->GetBinContent(i);
		if(bin1!=0){cos_omegacom->SetBinError(i, TMath::Sqrt(bin1));}
	Int_t bin2 = cos_omegalab->GetBinContent(i);
		if(bin2!=0){cos_omegalab->SetBinError(i, TMath::Sqrt(bin2));}
	Int_t bin3 = rap_omega->GetBinContent(i);
		if(bin3!=0){rap_omega->SetBinError(i, TMath::Sqrt(bin3));}
	Int_t bin4 = hm_ee->GetBinContent(i);
		if(bin4!=0){hm_ee->SetBinError(i, TMath::Sqrt(bin4));}
	Int_t bin5 = hm_eepp->GetBinContent(i);
		if(bin5!=0){hm_eepp->SetBinError(i, TMath::Sqrt(bin5));}
	Int_t bin6 = hm_pp->GetBinContent(i);
		if(bin6!=0){hm_pp->SetBinError(i, TMath::Sqrt(bin5));}
}


// drawing of the chosen histogram
	ee_theta->Draw("colz");
//	pp_theta->Draw("colz");
//	ee_p->Draw("colz");
//	pp_p->Draw("colz");
//	cos_omegacom->Draw();
//	cos_omegalab->Draw();
//	rap_omega->Draw();
//	hm_ee->Draw();
//	hm_eepp->Draw();
//	hm_pp->Draw();

}
