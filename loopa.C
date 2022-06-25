#define loopa_cxx
#include "loopa.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


void loopa::Loop()
{
//   In a ROOT session, you can do:
//      root> .L loopa.C
//      root> loopa t
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

	TH2F *pipi_theta = new TH2F("pipi_theta","#pi^{+} and #pi^{-} angles;#pi^{+} angle (degree);#pi^{-} angle (degree)",180,0,180,180,0,180);
	TH2F *kk_theta = new TH2F("kk_theta","K^{+} and K_{S}^{0} angles;K^{+} angle (degree);K_{S}^{0} angle (degree)",180,0,180,180,0,180);
	TH2F *pn_theta = new TH2F("pn_theta","p and n angles;p angle (degree);n angle (degree)",180,0,180,180,0,180);
	TH2F *pipi_p = new TH2F("pipi_p","#pi^{+} and #pi^{-} momenta;#pi^{+} momentum (GeV);#pi^{-} momentum (GeV)",200,0,4,200,0,4);
	TH2F *kk_p = new TH2F("kk_p","K^{+} and K_{S}^{0} momenta;K^{+} momentum (GeV);K_{S}^{0} momentum (GeV)",400,0,4,400,0,4);
	TH2F *pn_p = new TH2F("pn_p","p and n momenta;p momentum (GeV);n momentum (GeV)",200,0,5,200,0,5);
	TH1F *cos_acom = new TH1F("cos(a)com","cos(#theta) in C.o.M;cos(#theta);Counts",401,-1.01,1.01);
	TH1F *cos_alab = new TH1F("cos(a)lab","cos(#theta) in LAB;cos(#theta);Counts",401,-1.01,1.01);
	TH1F *rap_a = new TH1F("rapidity(a^{+})","rapidity;y;Counts",250,0.,2.5);
	TH1F *hm_pipi = new TH1F("hm_pipi","Invariant mass of #pi^{+}, #pi^{-};Invariant mass (GeV);Counts",100,0.45,0.55);
	TH1F *hm_pipik = new TH1F("hm_pipik","Invariant mass of #pi^{+}, #pi^{-}, K^{+};Invariant mass (GeV);Counts",300,0.9,1.5);
	TH1F *hm_pipipk = new TH1F("hm_pipipk","Invariant mass of #pi^{+}, #pi^{-}, p, K^{+};Invariant mass (GeV);Counts",400,1.8,2.6);
	TH1F *hm_pk = new TH1F("hm_pk","Invariant mass of p, K^{+};Invariant mass (GeV);Counts",400,1.3,2.1);
	TH1F *hm_k = new TH1F("hm_k","Invariant mass of K^{+};Invariant mass (GeV);Counts",50,0.492,0.496);

// attention: following histograms shows diference off the kaons' momenta in three different ways:
	// difference:
	TH1F *h_pdiff = new TH1F("h_pdiff","Difference between momenta of K_{S}^{0} and K^{+};Momentum of K_{S}^{0} - momentum of K^{+};Counts",300,-1.5,1.5);
	// symmetry of difference with respect to 0:
	TH1F *h_pdiff_a = new TH1F("h_pdiffa","Difference between momenta of K_{S}^{0} and K^{+};Momentum of K_{S}^{0} - momentum of K^{+};Counts",150,0.,1.5);
	TH1F *h_pdiff_b = new TH1F("h_pdiffb","Difference between momenta of K_{S}^{0} and K^{+};Momentum of K_{S}^{0} - momentum of K^{+};Counts",150,0.,1.5);
	// absolute value of difference:
	TH1F *h_pdiff_alt = new TH1F("h_pdiffalt","Difference between momenta of K_{S}^{0} and K^{+};Momentum of K_{S}^{0} - momentum of K^{+};Counts",150,0.,1.5);

	h_pdiff_a->SetLineColor(4);
	h_pdiff_b->SetLineColor(2);

// a loop

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);

// histograms: filling
	pipi_theta->Fill(pip_theta*57.2958,pim_theta*57.2958,w);
	kk_theta->Fill(kp_theta*57.2958,k0_theta*57.2958,w);
	pn_theta->Fill(p_theta*57.2958,n_theta*57.2958,w);
	pipi_p->Fill(pip_p,pim_p,w);
	kk_p->Fill(kp_p,k0_p,w);
	pn_p->Fill(p_p,n_p,w);
	cos_acom->Fill(cosacom,w);
	cos_alab->Fill(cosalab,w);
	rap_a->Fill(rap,ww);
	hm_pipi->Fill(minvpipi,w);
	hm_pipik->Fill(minvpipik,w);
	hm_pipipk->Fill(minvpipipk,w);
	hm_pk->Fill(minvpk,w);
	hm_k->Fill(minvk,w);
	h_pdiff->Fill(pdiff,w);
	h_pdiff_alt->Fill(TMath::Abs(kp_p-k0_p,w));

// filling the h_pdiff_a and the h_pdiff_b histogram
for(Int_t i=1;i<151; i++)
{		
	Int_t binh1 = h_pdiff->GetBinContent(i+150);
		h_pdiff_a->SetBinContent(i, binh1);
	Int_t binh2 = h_pdiff->GetBinContent(151-i);
		h_pdiff_b->SetBinContent(i, binh2);
}

// end part of the loop

      nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }	//tu petla sie konczy

// errors
for(Int_t i=1;i<=900; i++)
{
	Int_t bin1 = cos_acom->GetBinContent(i);
		if(bin1!=0){cos_acom->SetBinError(i, TMath::Sqrt(bin1));}
	Int_t bin2 = cos_alab->GetBinContent(i);
		if(bin2!=0){cos_alab->SetBinError(i, TMath::Sqrt(bin2));}
	Int_t bin3 = rap_a->GetBinContent(i);
		if(bin3!=0){rap_a->SetBinError(i, TMath::Sqrt(bin3));}
	Int_t bin4 = hm_pipi->GetBinContent(i);
		if(bin4!=0){hm_pipi->SetBinError(i, TMath::Sqrt(bin4));}
	Int_t bin5 = hm_pipik->GetBinContent(i);
		if(bin5!=0){hm_pipik->SetBinError(i, TMath::Sqrt(bin5));}
	Int_t bin6 = hm_pipipk->GetBinContent(i);
		if(bin6!=0){hm_pipipk->SetBinError(i, TMath::Sqrt(bin6));}
	Int_t bin7 = hm_pk->GetBinContent(i);
		if(bin7!=0){hm_pk->SetBinError(i, TMath::Sqrt(bin7));}
	Int_t bin8 = hm_k->GetBinContent(i);
		if(bin8!=0){hm_k->SetBinError(i, TMath::Sqrt(bin8));}
	Int_t bin9 = h_pdiff->GetBinContent(i);
		if(bin9!=0){h_pdiff->SetBinError(i, TMath::Sqrt(bin9));}
	Int_t bin10 = h_pdiff_a->GetBinContent(i);
		if(bin10!=0){h_pdiff_a->SetBinError(i, TMath::Sqrt(bin10));}
	Int_t bin11 = h_pdiff_b->GetBinContent(i);
		if(bin11!=0){h_pdiff_b->SetBinError(i, TMath::Sqrt(bin11));}
	Int_t bin12 = h_pdiff_alt->GetBinContent(i);
		if(bin12!=0){h_pdiff_alt->SetBinError(i, TMath::Sqrt(bin12));}
}

// drawing of the chosen histogram
//	pipi_theta->Draw("colz");
//	kk_theta->Draw("colz");
//	pn_theta->Draw("colz");
//	pipi_p->Draw("colz");
//	kk_p->Draw("colz");
//	pn_p->Draw("colz");
//	cos_acom->Draw();
//	cos_alab->Draw();
//	rap_a->Draw();
//	hm_pipi->Draw();
//	hm_pipik->Draw();
//	hm_pipipk->Draw();
//	hm_pk->Draw();
//	hm_k->Draw();
//	h_pdiff->Draw();
//	h_pdiff_a->Draw();
//	h_pdiff_b->Draw("same");
	h_pdiff_alt->Draw();

}
