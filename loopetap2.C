#define loopetap2_cxx
#include "loopetap2.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void loopetap2::Loop()
{
//   In a ROOT session, you can do:
//      root> .L loopetap2.C
//      root> loopetap2 t
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
	TH2F *pipi_theta = new TH2F("pipi_theta","#pi^{+} and #pi^{-} angles;#pi^{+} angle (degree);#pi^{-} angle (degree)",180,0,180,180,0,180);
	TH2F *pipi_p = new TH2F("pipi_p","#pi^{+} and #pi^{-} momenta;#pi^{+} momentum (GeV);#pi^{-} momentum (GeV)",200,0,5,200,0,5);
	TH1F *heta_theta = new TH1F("heta_theta","#eta angle;#eta angle (degree);Counts",180,0,180);
	TH1F *heta_p = new TH1F("heta_p","#eta momentum;#eta momentum (GeV);Counts",200,0,4);
	TH2F *gg_theta = new TH2F("gg_theta","#gamma_{1} and #gamma_{2} angles;#gamma_{1} angle (degree);#gamma_{2} angle (degree)",180,0,180,180,0,180);
	TH2F *gg_p = new TH2F("gg_p","#gamma_{1} and #gamma_{2} momenta;#gamma_{1} momentum (GeV);#gamma_{2} momentum (GeV)",200,0,4,200,0,4);
	TH1F *cos_etacom = new TH1F("cos(eta)com","cos(#theta) in C.o.M;cos(#theta);Counts",401,-1.01,1.01);
	TH1F *cos_etalab = new TH1F("cos(eta)lab","cos(#theta) in LAB;cos(#theta);Counts",401,-1.01,1.01);
	TH1F *rap_eta = new TH1F("rapidity(eta)","rapidity;y;Counts",250,0.,2.5);
	TH1F *hm_pipi = new TH1F("hm_pipi","Invariant mass of #pi^{+}, #pi^{-};Invariant mass (GeV);Counts",300,0.2,0.5);
	TH1F *hm_pipigg = new TH1F("hm_pipigg","Invariant mass of #pi^{+}, #pi^{-}, #gamma_{1}, #gamma_{2};Invariant mass (GeV);Counts",200,0.9,1.1);
	TH1F *hm_pipipp = new TH1F("hm_pipipp","Invariant mass of #pi^{+}, #pi^{-}, p_{1}, p_{2};Invariant mass (GeV);Counts",400,2.,4.);
	TH1F *hm_gg = new TH1F("hm_gg","Invariant mass of #gamma_{1}, #gamma_{2};Invariant mass (GeV);Counts",250,0.4,0.65);
	TH1F *hm_pp = new TH1F("hm_pp","Invariant mass of p_{1}, p_{2};Invariant mass (GeV);Counts",200,1.7,2.7);

// a loop

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);
      
// histograms: filling
	pp_theta->Fill(p1_theta*57.2958,p2_theta*57.2958,w);
	pp_p->Fill(p1_p,p2_p,w);
	pipi_theta->Fill(pip_theta*57.2958,pim_theta*57.2958,w);
	pipi_p->Fill(pip_p,pim_p,w);
	gg_theta->Fill(g1_theta*57.2958,g2_theta*57.2958,w);
	gg_p->Fill(g1_p,g2_p,w);
	cos_etacom->Fill(cosncom,w);
	cos_etalab->Fill(cosnlab,w);
	rap_eta->Fill(rap,w);
	hm_pipi->Fill(minvpipi,w);
	hm_pipigg->Fill(minvpipigg,w);
	hm_pipipp->Fill(minvpipipp,w);
	hm_gg->Fill(minvgg,w);
	hm_pp->Fill(minvpp,w);

// end part of the loop

      nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }	// here the loop ends

// errors
for(Int_t i=1;i<=900; i++)
{	
	Int_t bin1 = cos_etacom->GetBinContent(i);
		if(bin1!=0){cos_etacom->SetBinError(i, TMath::Sqrt(bin1));}
	Int_t bin2 = cos_etalab->GetBinContent(i);
		if(bin2!=0){cos_etalab->SetBinError(i, TMath::Sqrt(bin2));}
	Int_t bin3 = rap_eta->GetBinContent(i);
		if(bin3!=0){rap_eta->SetBinError(i, TMath::Sqrt(bin3));}
	Int_t bin4 = hm_pipi->GetBinContent(i);
		if(bin4!=0){hm_pipi->SetBinError(i, TMath::Sqrt(bin4));}
	Int_t bin5 = hm_pipigg->GetBinContent(i);
		if(bin5!=0){hm_pipigg->SetBinError(i, TMath::Sqrt(bin5));}
	Int_t bin6 = hm_pipipp->GetBinContent(i);
		if(bin6!=0){hm_pipipp->SetBinError(i, TMath::Sqrt(bin6));}
	Int_t bin7 = hm_gg->GetBinContent(i);
		if(bin7!=0){hm_gg->SetBinError(i, TMath::Sqrt(bin7));}
	Int_t bin8 = hm_pp->GetBinContent(i);
		if(bin8!=0){hm_pp->SetBinError(i, TMath::Sqrt(bin8));}
}


// drawing of the chosen histogram
//	pp_theta->Draw("colz");
//	pp_p->Draw("colz");
//	pipi_theta->Draw("colz");
//	pipi_p->Draw("colz");
//	gg_theta->Draw("colz");
//	gg_p->Draw("colz");
//	cos_etacom->Draw();
//	cos_etalab->Draw();
	rap_eta->Draw();
//	hm_pipi->Draw();
//	hm_pipigg->Draw();
//	hm_pipipp->Draw();
//	hm_gg->Draw();
//	hm_pp->Draw();
}
