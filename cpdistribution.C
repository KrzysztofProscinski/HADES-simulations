{
// obtaining a distribution from the file
	TFile *fin = new TFile("eta2cp.root");
	hcp = (TH1F*)fin->Get("hcp");

// histogram: difinition
	TH1F *hcp_d = new TH1F("hcp_d","CP symmetry violation;sin(#theta_{e #pi})cos(#theta_{e #pi});Counts",20,-0.5,0.5);

// needed parameters
	TRandom2 r;
	r.SetSeed();
	Double_t rand1=0;
	Double_t rand1mod=0;
	Double_t rand2=0;
	Double_t bin;

// finding a maximum of the distribution
	Double_t binmax=0;
	for(Int_t i=1;i<=20; i++)
	{bin = hcp->GetBinContent(i);
		if(bin>binmax){binmax=bin;}
	}

// histogram filling: rejection sampling method; number 4666 corresponds to predicted statistic for the HADES experiment
	for(Int_t i=1;i<=4666; i++)
	{
		rand2=r.Rndm ()*binmax;
		rand1=r.Rndm ();
		bin = hcp->GetBinContent(rand1*20);

		while(rand2>bin)
			{rand2=r.Rndm ()*binmax;
			rand1=r.Rndm ();
			bin = hcp->GetBinContent(rand1*20);}
		rand1=rand1-0.5;
		hcp_d->Fill(rand1);
	}

	hcp_d->SetMinimum(0);

// drawing the histogram
	hcp_d->Draw("e");
}
