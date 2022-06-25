#define loopetap1_cxx
#include "loopetap1.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void loopetap1::Loop()
{
//   In a ROOT session, you can do:
//      root> .L loopetap1.C
//      root> loopetap1 t
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
	TH2F *pp_theta = new TH2F("pp_theta","p_{1} and p_{2} angles;p_{1} angle (degree);p_{2} angle (degree)",180,0,180,180,0,180);
	TH2F *pp_p = new TH2F("pp_p","p_{1} and p_{2} momenta;p_{1} momentum (GeV);p_{2} momentum (GeV)",200,0,5,200,0,5);
	TH2F *rhog_theta = new TH2F("rhog_theta","#rho^{0} and #gamma angles;#rho^{0} angle (degree);#gamma angle (degree)",180,0,180,180,0,180);
	TH2F *rhog_p = new TH2F("rhog_p","#rho^{0} and #gamma momenta;#rho^{0} momentum (GeV);#gamma momentum (GeV)",200,0,5,200,0,5);
	TH1F *hg_theta = new TH1F("hg_theta","#gamma angle;#gamma angle (degree);Counts",180,0,180);
	TH1F *hg_p = new TH1F("hg_p","#gamma momentum;#gamma momentum (GeV);Counts",300,0,1.5);
	TH2F *pipi_theta = new TH2F("pipi_theta","#pi^{+} and #pi^{-} angles;#pi^{+} angle (degree);#pi^{-} angle (degree)",180,0,180,180,0,180);
	TH2F *pipi_p = new TH2F("pipi_p","#pi^{+} and #pi^{-} momenta;#pi^{+} momentum (GeV);#pi^{-} momentum (GeV)",200,0,5,200,0,5);
	TH1F *cos_etacom = new TH1F("cos(eta)com","cos(#theta) in C.o.M;cos(#theta);Counts",401,-1.01,1.01);
	TH1F *cos_etalab = new TH1F("cos(eta)lab","cos(#theta) in LAB;cos(#theta);Counts",401,-1.01,1.01);
	TH1F *rap_eta = new TH1F("rapidity(eta)","rapidity;y;Counts",250,0.,2.5);
	TH1F *hm_pipi = new TH1F("hm_pipi","Invariant mass of #pi^{+}, #pi^{-};Invariant mass (GeV);Counts",200,0.6,1.0);
	TH1F *hm_pipig = new TH1F("hm_pipig","Invariant mass of #pi^{+}, #pi^{-}, #gamma;Invariant mass (GeV);Counts",300,0.8,1.1);
	TH1F *hm_pipipp = new TH1F("hm_pipipp","Invariant mass of #pi^{+}, #pi^{-}, p_{1}, p_{2};Invariant mass (GeV);Counts",400,2.8,3.6);
	TH1F *hm_g = new TH1F("hm_g","Invariant mass of #gamma;Invariant mass (GeV);Counts",240,0.0,0.000000012);
	TH1F *hm_pp = new TH1F("hm_pp","Invariant mass of p_{1}, p_{2};Invariant mass (GeV);Counts",300,1.5,3.);

// a loop

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);
      
// histograms: filling
	pp_theta->Fill(p1_theta*57.2958,p2_theta*57.2958,w);
	pp_p->Fill(p1_p,p2_p,w);
	rhog_theta->Fill(rho_theta*57.2958,g_theta*57.2958,w);
	rhog_p->Fill(rho_p,g_p,w);
	hg_theta->Fill(g_theta*57.2958,w);
	hg_p->Fill(g_p,w);
	pipi_theta->Fill(pip_theta*57.2958,pim_theta*57.2958,w);
	pipi_p->Fill(pip_p,pim_p,w);
	cos_etacom->Fill(cosncom,w);
	cos_etalab->Fill(cosnlab,w);
	rap_eta->Fill(rap,w);
	hm_pipi->Fill(minvpipi,w);
	hm_pipig->Fill(minvpipig,w);
	hm_pipipp->Fill(minvpipipp,w);
	hm_g->Fill(minvg,w);
	hm_pp->Fill(minvpp,w);

// end part of the loop

      nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }	//here the loop ends

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
	Int_t bin6 = hm_pipi->GetBinContent(i);
		if(bin6!=0){hm_pipi->SetBinError(i, TMath::Sqrt(bin6));}
	Int_t bin7 = hm_pipig->GetBinContent(i);
		if(bin7!=0){hm_pipig->SetBinError(i, TMath::Sqrt(bin7));}
	Int_t bin8 = hm_pipipp->GetBinContent(i);
		if(bin8!=0){hm_pipipp->SetBinError(i, TMath::Sqrt(bin8));}
	Int_t bin9 = hm_g->GetBinContent(i);
		if(bin9!=0){hm_g->SetBinError(i, TMath::Sqrt(bin9));}
	Int_t bin10 = hm_pp->GetBinContent(i);
		if(bin10!=0){hm_pp->SetBinError(i, TMath::Sqrt(bin10));}
}

// drawing of the chosen histogram
	pp_theta->Draw("colz");
//	pp_p->Draw("colz");
//	rhog_theta->Draw("colz");
//	rhog_p->Draw("colz");
//	hg_theta->Draw();
//	hg_p->Draw();
//	pipi_theta->Draw("colz");
//	pipi_p->Draw("colz");
//	cos_etacom->Draw();
//	cos_etalab->Draw();
//	rap_eta->Draw();
//	hm_pipi->Draw();
//	hm_pipig->Draw();
//	hm_pipipp->Draw();
//	hm_g->Draw();
//	hm_pp->Draw();
}
