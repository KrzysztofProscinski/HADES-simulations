{
// obtaining needed distribution from the file
	TFile *fin = new TFile("ffppomega.root");
	h_4pi = (TH1F*)fin->Get("h_4pi");
	h_hades = (TH1F*)fin->Get("h_hades");
	h_qed_4pi = (TH1F*)fin->Get("h_qed_4pi");
	h_acc = (TH1F*)fin->Get("h_acc");

	TH1F *h_4pi_d = new TH1F("h_4pi_d","Invariant mass of e^{+}e^{-} without cuts;Mass (GeV);Counts",80,0.,0.8); //minv without cuts
	TH1F *h_hades_d = new TH1F("h_hades_d","Invariant mass of e^{+}e^{-} with cuts;Mass (GeV);Counts",80,0.,0.8); //minv with cuts
	TH1F *h_acc_d = new TH1F("h_acc_d","Acceptance;Mass (GeV);Acceptance",80,0.,0.8); //acceptance as a function of mass
	TH1F *h_qed_hades_d = new TH1F("h_qed_hades_d","Invariant mass of point-like e^{+}e^{-} with cuts;Mass (GeV);Counts",80,0.,0.8); //minv for point-like omega, with cuts
	TH1F *h_ff_hades_d = new TH1F("h_ff_hades_d","Form factor with cuts;Mass (GeV);Form factor^{2}",80,0.,0.8); //form factor z cieciami

// needed parameters
	TRandom2 r;
	r.SetSeed();
	Double_t rand1=0;
	Double_t rand2=0;
	Double_t bin;

// finding a maximum of the h_4pi distribution
	Double_t binmax=0;
	for(Int_t i=1;i<=80; i++)
	{bin = h_4pi->GetBinContent(i);
		if(bin>binmax){binmax=bin;}
	}

// histogram filling: rejection sampling method; number 1378944 corresponds to predicted statistic for the HADES experiment
	for(Int_t i=1;i<=1378944; i++)
	{
		rand2=r.Rndm ()*binmax;
		rand1=r.Rndm ();
		bin = h_4pi->GetBinContent(rand1*100);

		while(rand2>bin)
			{rand2=r.Rndm ()*binmax;
			rand1=r.Rndm ();
			bin = h_4pi->GetBinContent(rand1*100);}
		h_4pi_d->Fill(rand1);
	}

// finding a maximum of the h_hades distribution
	binmax=0;	
	for(Int_t i=1;i<=80; i++)
	{bin = h_hades->GetBinContent(i);
		if(bin>binmax){binmax=bin;}
	}

// histogram filling: rejection sampling method; number 40855 corresponds to predicted statistic for the HADES experiment
	for(Int_t i=1;i<=40855; i++)
	{
		rand2=r.Rndm ()*binmax;
		rand1=r.Rndm ();
		bin = h_hades->GetBinContent(rand1*100);

		while(rand2>bin)
			{rand2=r.Rndm ()*binmax;
			rand1=r.Rndm ();
			bin = h_hades->GetBinContent(rand1*100);}
		h_hades_d->Fill(rand1);
	}

	h_4pi_d->Draw();

// needed parameters
	Double_t a;
	Double_t a1;
	Double_t da;
	Double_t b;
	Double_t b1;
	Double_t db;
	Double_t ff;
	Double_t dff;	


// acceptance
// acceptance: filling the histogram
for(Int_t i=0; i<81;i++)
	{
	a=h_hades_d->GetBinContent(i);
	b=h_4pi_d->GetBinContent(i);
	
	if(b==0) {ff=0; dff=0;}
	else {ff=a/b;dff=TMath::Sqrt(a)/b+(TMath::Sqrt(b))*a/b/b;}

	h_acc_d->SetBinContent(i,ff);
	h_acc_d->SetBinError(i,dff);
	}


// minv for point-like omega, with cuts
// minv for point-like omega, with cuts: filling the histogram
for(Int_t i=0; i<81;i++)
	{
	a=h_qed_4pi->GetBinContent(i);
	b=h_acc_d->GetBinContent(i);

	db=h_acc_d->GetBinError(i);
	
	if(b==0) {ff=0; dff=0;}
	else {ff=a*b;dff=db*a;}

	h_qed_hades_d->SetBinContent(i,ff);
	h_qed_hades_d->SetBinError(i,dff);
	}


// form factor with cuts
// form factor with cuts: data for normalization
Int_t j=6;
while(b1==0){a1=h_hades_d->GetBinContent(j); b1=h_qed_hades_d->GetBinContent(j);j=j+1;}

// form factor with cuts: filling the histogram
for(Int_t i=0; i<81;i++)
	{
	a=h_hades_d->GetBinContent(i);
	b=h_qed_hades_d->GetBinContent(i)*a1/b1;

	da=h_hades_d->GetBinError(i);
	db=h_qed_hades_d->GetBinError(i)*a1/b1;

	if(b==0) {ff=0; dff=0;}
	else {ff=a/b;dff=da/b+db*a/b/b;}

	h_ff_hades_d->SetBinContent(i,ff);
	h_ff_hades_d->SetBinError(i,dff);
	}

// drawing the chosen histogram
//	h_4pi_d->Draw();
//	h_hades_d->Draw();
//	h_acc_d->Draw();
//	h_qed_hades_d->Draw();
	h_ff_hades_d->Draw();


}
