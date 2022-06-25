#define loopeta2_cxx
#include "loopeta2.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void loopeta2::Loop()
{
//   In a ROOT session, you can do:
//      root> .L loopeta2.C
//      root> loopeta2 t
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

// histograms: definitions
	TH2F *ee_theta = new TH2F("ee_theta","e^{+} and e^{-} angles;e^{+} angle (degree);e^{-} angle (degree)",180,0,180,180,0,180);
	TH2F *pipi_theta = new TH2F("pipi_theta","#pi^{+} and #pi^{-} angles;#pi^{+} angle (degree);#pi^{-} angle (degree)",180,0,180,180,0,180);
	TH2F *pp_theta = new TH2F("pp_theta","p_{1} and p_{2} angles;p_{1} angle (degree);p_{2} angle (degree)",180,0,180,180,0,180);
	TH1F *hp1_theta = new TH1F("p1_theta","p_{1} and p_{2} angles;p_{1} angle (degree);p_{2} angle (degree)",180,0,180);
	TH2F *ee_p = new TH2F("ee_p","e^{+} and e^{-} momenta;e^{+} momentum (GeV);e^{-} momentum (GeV)",200,0,4,200,0,4);
	TH2F *pipi_p = new TH2F("pipi_p","#pi^{+} and #pi^{-} momenta;#pi^{+} momentum (GeV);#pi^{-} momentum (GeV)",200,0,5,200,0,5);
	TH2F *pp_p = new TH2F("pp_p","p_{1} and p_{2} momenta;p_{1} momentum (GeV);p_{2} momentum (GeV)",200,0,6.,200,0,6.);
	TH1F *cos_etacom = new TH1F("cos(eta)com","cos(#theta) in C.o.M;cos(#theta);Counts",401,-1.01,1.01);
	TH1F *cos_etalab = new TH1F("cos(eta)lab","cos(#theta) in LAB;cos(#theta);Counts",401,-1.01,1.01);
	TH1F *rap_eta = new TH1F("rapidity(eta)","rapidity;y;Counts",300,0.,3.);
	TH1F *hm_ee = new TH1F("hm_ee","Invariant mass of e^{+}, e^{-};Invariant mass (GeV);Counts",300,0.,0.6);
	TH1F *hm_eepipi = new TH1F("hm_eepipi","Invariant mass of e^{+}, e^{-}, #pi^{+}, #pi^{-};Invariant mass (GeV);Counts",100,0.5,0.6);
	TH1F *hm_eepp = new TH1F("hm_eepp","Invariant mass of e^{+}, e^{-}, p_{1}, p_{2};Invariant mass (GeV);Counts",400,0.,4.);
	TH1F *hm_pipi = new TH1F("hm_pipi","Invariant mass of #pi^{+}, #pi^{-};Invariant mass (GeV);Counts",200,0.2,0.6);
	TH1F *hm_pp = new TH1F("hm_pp","Invariant mass of p_{1}, p_{2};Invariant mass (GeV);Counts",400,0.,4.);

// attention: here you can choose if you want to draw a histogram of the CP symmetry violation with 2 or with 20 bins
// 2 bins:
	TH1F *hcp2 = new TH1F("hcp2","CP symmetry violation;sin(#theta_{e #pi})cos(#theta_{e #pi});Counts",2,-0.5,0.5);
	TH1F *hcp2a = new TH1F("hcp2a","CP symmetry violation",1,0.,0.5);
	TH1F *hcp2b = new TH1F("hcp2b","CP symmetry violation",1,0.,0.5);
// 20 bins:
	TH1F *hcp = new TH1F("hcp","CP symmetry violation;sin(#theta_{e #pi})cos(#theta_{e #pi});Counts",20,-0.5,0.5);
	TH1F *hcpa = new TH1F("hcpa","CP symmetry violation",10,0.,0.5);
	TH1F *hcpb = new TH1F("hcpb","CP symmetry violation",10,0.,0.5);

	TH1F *hcpalt = new TH1F("hcp2alt","CP symmetry violation",20,-1.,1.);

	hcp->SetMinimum(0);
	hcpa->SetLineColor(4);
	hcpb->SetLineColor(2);
	hcp2a->SetLineColor(4);
	hcp2b->SetLineColor(2);


// a loop


   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);

// histograms: filling
	ee_theta->Fill(ep_theta*57.2958,em_theta*57.2958,w);
	pipi_theta->Fill(pip_theta*57.2958,pim_theta*57.2958,w);
	pp_theta->Fill(p1_theta*57.2958,p2_theta*57.2958,w);
	hp1_theta->Fill(p1_theta*57.2958,w);
	ee_p->Fill(ep_p,em_p,w);
	pipi_p->Fill(pip_p,pim_p,w);
	pp_p->Fill(p1_p,p2_p,w);
	cos_etacom->Fill(cosncom,w);
	cos_etalab->Fill(cosnlab,w);
	rap_eta->Fill(rap,w);
	hcp->Fill(cp);
	hcp2->Fill(cp);
	hm_ee->Fill(minvee,w);
	hm_eepipi->Fill(minveepipi,w);
	hm_eepp->Fill(minveepp,w);
	hm_pipi->Fill(minvpipi,w);
	hm_pp->Fill(minvpp,w);

// end part of the loop

      nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }	//here the loop ends


// filling histograms for the CP violation where we check symmetry with respect to 0 (version for 2 bins)
for(Int_t i=1;i<2; i++)
{		
	Int_t binh1 = hcp2->GetBinContent(i+1);
		hcp2a->SetBinContent(i, binh1);
	Int_t binh2 = hcp2->GetBinContent(i);
		hcp2b->SetBinContent(i, binh2);
}

// filling histograms for CP violation where we check symmetry with respect to 0(version for 20 bins)
for(Int_t i=1;i<11; i++)
{		
	Int_t binh1 = hcp->GetBinContent(i+10);
		hcpa->SetBinContent(i, binh1);
	Int_t binh2 = hcp->GetBinContent(11-i);
		hcpb->SetBinContent(i, binh2);
}


// errors
for(Int_t i=1;i<=900; i++)
{		
	Int_t bin1 = cos_etacom->GetBinContent(i);
		if(bin1!=0){cos_etacom->SetBinError(i, TMath::Sqrt(bin1));}
	Int_t bin2 = cos_etalab->GetBinContent(i);
		if(bin2!=0){cos_etalab->SetBinError(i, TMath::Sqrt(bin2));}
	Int_t bin3 = rap_eta->GetBinContent(i);
		if(bin3!=0){rap_eta->SetBinError(i, TMath::Sqrt(bin3));}
	Int_t bin4 = hcp->GetBinContent(i);
		if(bin4!=0){hcp->SetBinError(i, TMath::Sqrt(bin4));}
	Int_t bin5 = hcp2->GetBinContent(i);
		if(bin5!=0){hcp2->SetBinError(i, TMath::Sqrt(bin5));}
	Int_t bin6 = hm_ee->GetBinContent(i);
		if(bin6!=0){hm_ee->SetBinError(i, TMath::Sqrt(bin6));}
	Int_t bin7 = hm_eepipi->GetBinContent(i);
		if(bin7!=0){hm_eepipi->SetBinError(i, TMath::Sqrt(bin7));}
	Int_t bin8 = hm_eepp->GetBinContent(i);
		if(bin8!=0){hm_eepp->SetBinError(i, TMath::Sqrt(bin8));}
	Int_t bin9 = hm_pipi->GetBinContent(i);
		if(bin9!=0){hm_pipi->SetBinError(i, TMath::Sqrt(bin9));}
	Int_t bin10 = hm_pp->GetBinContent(i);
		if(bin10!=0){hm_pp->SetBinError(i, TMath::Sqrt(bin10));}
	Int_t bin11 = hcpa->GetBinContent(i);
		if(bin11!=0){hcpa->SetBinError(i, TMath::Sqrt(bin11));}
	Int_t bin12 = hcpb->GetBinContent(i);
		if(bin12!=0){hcpb->SetBinError(i, TMath::Sqrt(bin12));}
	Int_t bin13 = hcp2a->GetBinContent(i);
		if(bin13!=0){hcp2a->SetBinError(i, TMath::Sqrt(bin13));}
	Int_t bin14 = hcp2b->GetBinContent(i);
		if(bin14!=0){hcp2b->SetBinError(i, TMath::Sqrt(bin14));}

}

// drawing of the chosen histogram
//	ee_theta->Draw("colz");
//	pipi_theta->Draw("colz");
//	pp_theta->Draw("colz");
//	ee_p->Draw("colz");
//	pipi_p->Draw("colz");
//	pp_p->Draw("colz");
//	cos_etacom->Draw();
//	cos_etalab->Draw();
//	rap_eta->Draw();
	hcp->Draw();
	hcp2->Draw();
//	hm_ee->Draw();
//	hm_eepipi->Draw();
//	hm_eepp->Draw();
//	hm_pipi->Draw();
//	hm_pp->Draw();
//	hcpa->Draw();
//	hcpb->Draw("same");
//	hcp2a->Draw();
//	hcp2b->Draw("same");

// saving the hcp in a .root file; this is needed if you want to use this histogram as a distribution for obtaining histogram for the experimental statistics
/*	TFile *out = new TFile("eta2cp.root","recreate");
	out->cd();
	hcp->Write();
	out->Close();*/
}

