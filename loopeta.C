#define loopeta_cxx
#include "loopeta.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void loopeta::Loop()
{
//   In a ROOT session, you can do:
//      root> .L loopeta.C
//      root> loopeta t
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

// histograms: definitions

	TH2F *ee_theta = new TH2F("ee_theta","e^{+} and e^{-} angles;e^{+} angle (degree);e^{-} angle (degree)",180,0,180,180,0,180);
	TH1F *hg_theta = new TH1F("g_theta","#gamma angle;#gamma angle (degree);Counts",180,0,180);
	TH2F *pp_theta = new TH2F("pp_theta","p_{1} and p_{2} angles;p_{1} angle (degree);p_{2} angle (degree)",180,0,180,180,0,180);
	TH2F *ee_p = new TH2F("ee_p","e^{+} and e^{-} momenta;e^{+} momentum (GeV);e^{-} momentum (GeV)",200,0,4,200,0,4);
	TH1F *hg_p = new TH1F("g_p","#gamma momentum;#gamma momentum (GeV);Counts",400,0,4);
	TH2F *pp_p = new TH2F("pp_p","p_{1} and p_{2} momenta;p_{1} momentum (GeV);p_{2} momentum (GeV)",200,0,5,200,0,5);
	TH1F *cos_etacom = new TH1F("cos(eta)com","cos(#theta) in C.o.M;cos(#theta);Counts",401,-1.01,1.01);
	TH1F *cos_etalab = new TH1F("cos(eta)lab","cos(#theta) in LAB;cos(#theta);Counts",401,-1.01,1.01);
	TH1F *rap_eta = new TH1F("rapidity(eta)","rapidity;y;Counts",300,0.,3.);
	TH1F *hm_ee = new TH1F("hm_ee","Invariant mass of e^{+}, e^{-};Invariant mass (GeV);Counts",300,0.,0.6);
	TH1F *hm_eeg = new TH1F("hm_eeg","Invariant mass of e^{+}, e^{-}, #gamma;Invariant mass (GeV);Counts",350,0.,0.7);
	TH1F *hm_eepp = new TH1F("hm_eepp","Invariant mass of e^{+}, e^{-}, p_{1}, p_{2};Invariant mass (GeV);Counts",400,0.,4.);
	TH1F *hm_g = new TH1F("hm_g","Invariant mass of #gamma;Invariant mass (GeV);Counts",100,0.,0.00000004);
	TH1F *hm_pp = new TH1F("hm_pp","Invariant mass of p_{1}, p_{2};Invariant mass (GeV);Counts",400,1.5,3.5);

// a loop

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);

// histograms: filling
	ee_theta->Fill(ep_theta*57.2958,em_theta*57.2958,w);
	hg_theta->Fill(g_theta*57.2958,w);
	pp_theta->Fill(p1_theta*57.2958,p2_theta*57.2958,w);
	ee_p->Fill(ep_p,em_p,w);
	hg_p->Fill(g_p,w);
	pp_p->Fill(p1_p,p2_p,w);//
	cos_etacom->Fill(cosncom,w);
	cos_etalab->Fill(cosnlab,w);
	rap_eta->Fill(rap,w);
	hm_ee->Fill(minvee,w);
	hm_eeg->Fill(minveeg,w);
	hm_eepp->Fill(minveepp,w);
	hm_g->Fill(minvg,w);
	hm_pp->Fill(minvpp,w);

// end part of the loop

      nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }	//tu petla sie konczy

// errors
for(Int_t i=1;i<=900; i++)
{		
	Int_t bin1 = hg_theta->GetBinContent(i);
		if(bin1!=0){hg_theta->SetBinError(i, TMath::Sqrt(bin1));}
	Int_t bin2 = hg_p->GetBinContent(i);
		if(bin2!=0){hg_p->SetBinError(i, TMath::Sqrt(bin2));}
	Int_t bin3 = cos_etacom->GetBinContent(i);
		if(bin3!=0){cos_etacom->SetBinError(i, TMath::Sqrt(bin3));}
	Int_t bin4 = cos_etalab->GetBinContent(i);
		if(bin4!=0){cos_etalab->SetBinError(i, TMath::Sqrt(bin4));}
	Int_t bin5 = rap_eta->GetBinContent(i);
		if(bin5!=0){rap_eta->SetBinError(i, TMath::Sqrt(bin5));}
	Int_t bin6 = hm_ee->GetBinContent(i);
		if(bin6!=0){hm_ee->SetBinError(i, TMath::Sqrt(bin6));}
	Int_t bin7 = hm_eeg->GetBinContent(i);
		if(bin7!=0){hm_eeg->SetBinError(i, TMath::Sqrt(bin7));}
	Int_t bin8 = hm_eepp->GetBinContent(i);
		if(bin8!=0){hm_eepp->SetBinError(i, TMath::Sqrt(bin8));}
	Int_t bin9 = hm_g->GetBinContent(i);
		if(bin9!=0){hm_g->SetBinError(i, TMath::Sqrt(bin9));}
	Int_t bin10 = hm_pp->GetBinContent(i);
		if(bin10!=0){hm_pp->SetBinError(i, TMath::Sqrt(bin10));}
}

// drawing of the chosen histogram
//	ee_theta->Draw("colz");
//	hg_theta->Draw("colz");
//	pp_theta->Draw("colz");
//	ee_p->Draw("colz");
//	hg_p->Draw();
//	pp_p->Draw("colz");
//	cos_etacom->Draw();
//	cos_etalab->Draw();
	rap_eta->Draw();
//	hm_ee->Draw();
//	hm_eeg->Draw();
//	hm_eepp->Draw();
//	hm_g->Draw();
//	hm_pp->Draw();

}
