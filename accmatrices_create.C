{
// file where acceptance matrices will be saved
	TFile *out = new TFile("acc_matrices.root","recreate");

// reading needed histograms from the file "sum_omega.root"
	TFile *f = new TFile("sum_omega.root");
	hist1p = (TH2F*)f->Get("ep_thetavsMom");
	hist2p = (TH2F*)f->Get("ep_thetavsMom_4pi");
	hist1m = (TH2F*)f->Get("em_thetavsMom");
	hist2m = (TH2F*)f->Get("em_thetavsMom_4pi");

// definitions of histograms
	TH2F *acc_ep = new TH2F("acc_ep","Acceptance for e^{+};Momentum (GeV);Angle (Degree)",50,0,3,90,0.,180);
	TH2F *acc_em = new TH2F("acc_em","Acceptance for e^{-};Momentum (GeV);Angle (Degree)",50,0,3,90,0.,180);


// needed parameters
	Double_t a;
	Double_t da;
	Double_t b;
	Double_t db;
	Double_t acc;
	Double_t dacc;

// rebining histograms from the file "sum_omega.root"
	hist1p->Rebin2D(20,2);
	hist2p->Rebin2D(20,2);
	hist1m->Rebin2D(20,2);
	hist2m->Rebin2D(20,2);

// creating the acceptance matrix for positrons
for(Int_t j=0; j<51;j++){
for(Int_t i=0; i<91;i++)
	{
	a=hist1p->GetBinContent(j,i);
	b=hist2p->GetBinContent(j,i);

	if(b==0) {acc=0;}
	else if(a>b) {acc=1.;}
	else {acc=a/b;}

	if(acc<0.05){acc=0;}

	acc_ep->SetBinContent(j,i,acc);
	}}

// creating the acceptance matrix for electrons
for(Int_t j=0; j<51;j++){
for(Int_t i=0; i<91;i++)
	{
	a=hist1m->GetBinContent(j,i);
	b=hist2m->GetBinContent(j,i);

	if(b==0) {acc=0;}
	else if(a>b) {acc=1.;}
	else {acc=a/b;}

	if(acc<0.05){acc=0;}

	acc_em->SetBinContent(j,i,acc);
	}}
	

// saving acceptance matrices to the file
/*	out->cd();
	acc_ep->Write();
	acc_em->Write();
	out->Close();*/
}