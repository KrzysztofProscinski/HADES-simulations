{
//R__LOAD_LIBRARY ($PLUTOLIBDIR/libPluto.so);
//gSystem->CompileMacro( "PHadesAcc.C");

// output file
	TFile *out = new TFile("ffppomega.root","recreate");



// ntuple
	TNtuple *nt1ff = new TNtuple("nt1ff","ffomega31","minv4pi:w:acc"); //ntuple

// histograms
	TH1F *h_4pi = new TH1F("h_4pi","Invariant mass of e^{+}e^{-} without cuts;Mass (GeV);Counts",80,0.,0.8); //minv without cuts
	TH1F *h_hades = new TH1F("h_hades","Invariant mass of e^{+}e^{-} with cuts;Mass (GeV);Counts",80,0.,0.8); //minv with cuts
	TH1F *h_qed_4pi = new TH1F("h_qed_4pi","Invariant mass of point-like e^{+}e^{-};Mass (GeV);Counts",80,0.,0.8); //minv for point-like omega
	TH1F *h_acc = new TH1F("h_acc","Acceptance;Mass (GeV);Acceptance",80,0.,0.8); //acceptance as a function of mass
	TH1F *h_qed_hades = new TH1F("h_qed_hades","Invariant mass of point-like e^{+}e^{-} with cuts;Mass (GeV);Counts",80,0.,0.8); //minv for point-like omega, with cuts
	TH1F *h_ff_4pi = new TH1F("h_ff_4pi","Form factor;Mass (GeV);Form factor^{2}",80,0.,0.8); //form factor
	TH1F *h_ff_hades = new TH1F("h_ff_hades","Form factor with cuts;Mass (GeV);Form factor^{2}",80,0.,0.8); //form factor with cuts



// reaction 1
// reaction  1: minv histogram
	PReaction my_reaction1("4.5","p","p","p p w [pi0 [g g] dilepton [e+ e-] ] ", "reakcja1", 1, 0, 0,1); //definicja

// loading PHadesAcc()
	my_reaction1.AddBulk(new PHadesAcc());

	my_reaction1.Output(nt1ff,"minv4pi=([e+,1]+[e-,1])->M();w=_hadacc*_opang");

// reaction 1: loop
	my_reaction1.Preheating(100);
	my_reaction1.Loop(1000); //shorter loop
//	my_reaction1.Loop(10000000); //longer loop (warning: it may take a few hours)


// data have been saved in a tree, so now we want to use them to fill histograms
	TTree *tree = (TTree*) out->Get ("nt1ff");
	Float_t        minv4pi;
	Float_t        w;
	tree->SetBranchAddress ("minv4pi", &minv4pi);
	tree->SetBranchAddress ("w", &w);	

	Float_t		w2;
	for (int i=0; i<tree->GetEntries(); i++) {
		tree->GetEntry(i);		
		if(w<0.01){w2=0;} else{w2=1;}		
		h_4pi->Fill(minv4pi);
		h_hades->Fill(minv4pi,w2);
	}




// reaction 2: minv for point-like omega
// reaction 2: function from QED, which describes minv distribution
	TF1 *funkcja = new TF1("funkcja","2*x*TMath::Sqrt(1-4*0.000511/x*0.000511/x)*(1+2*0.000511*0.000511/x/x)*1/x/x*TMath::Sqrt((1+x*x/(0.782*0.782-0.135*0.135))*(1+x*x/(0.782*0.782-0.135*0.135)) - (4*x*x*0.782*0.782)/(0.782*0.782-0.135*0.135)/(0.782*0.782-0.135*0.135))*((1+x*x/(0.782*0.782-0.135*0.135))*(1+x*x/(0.782*0.782-0.135*0.135)) - (4*x*x*0.782*0.782)/(0.782*0.782-0.135*0.135)/(0.782*0.782-0.135*0.135))",0.001023,0.647);

// reaction 2: needed constants
	Double_t fy;
	Double_t fx;

// reaction 2: loop
for(Int_t i=1; i<410;i++)
	{
	fx=h_qed_4pi->GetBinCenter(i); //bin position - argument of the function from QED
	
	if(fx>0.001023&&fx<0.647)
		{fy=funkcja->Eval(fx);} //value of function for a certain bin
	else {fy=0;}
	
	h_qed_4pi->SetBinContent(i,fy); //histogram filling
	}





// needed constants
	Double_t a;
	Double_t a1;
	Double_t da;
	Double_t b;
	Double_t b1;
	Double_t db;
	Double_t ff;
	Double_t dff;	


// form factor without cuts
// form factor without cuts: data for proper normalization
	a1=h_4pi->GetBinContent(3);
	b1=h_qed_4pi->GetBinContent(3);
	if(b1==0){a1=h_4pi->GetBinContent(4); b1=h_qed_4pi->GetBinContent(4);}

// form factor without cuts: filling the histogram
for(Int_t i=0; i<81;i++)
	{
	a=h_4pi->GetBinContent(i);
	b=h_qed_4pi->GetBinContent(i)*a1/b1;

	da=h_4pi->GetBinError(i);

	if(b==0) {ff=0; dff=0;}
	else {ff=a/b;dff=da/b;}

	h_ff_4pi->SetBinContent(i,ff);
	h_ff_4pi->SetBinError(i,dff);
	}


// acceptance
// acceptance: filling the histogram
for(Int_t i=0; i<81;i++)
	{
	a=h_hades->GetBinContent(i);
	b=h_4pi->GetBinContent(i);
	
	if(b==0) {ff=0; dff=0;}
	else {ff=a/b;dff=TMath::Sqrt(a)/b+(TMath::Sqrt(b))*a/b/b;}

	h_acc->SetBinContent(i,ff);
	h_acc->SetBinError(i,dff);
	}


// minv for point-like omega, with cuts
// minv for point-like omega, with cuts: filling the histogram
for(Int_t i=0; i<81;i++)
	{
	a=h_qed_4pi->GetBinContent(i);
	b=h_acc->GetBinContent(i);

	db=h_acc->GetBinError(i);
	
	if(b==0) {ff=0; dff=0;}
	else {ff=a*b;dff=db*a;}

	h_qed_hades->SetBinContent(i,ff);
	h_qed_hades->SetBinError(i,dff);
	}


// form factor with cuts
// form factor with cuts: data for normalization
	a1=h_hades->GetBinContent(4);
	b1=h_qed_hades->GetBinContent(4);
	if(b1==0){a1=h_hades->GetBinContent(4); b1=h_qed_hades->GetBinContent(5);}

// form factor with cuts: filling the histogram
for(Int_t i=0; i<81;i++)
	{
	a=h_hades->GetBinContent(i);
	b=h_qed_hades->GetBinContent(i)*a1/b1;

	da=h_hades->GetBinError(i);
	db=h_qed_hades->GetBinError(i)*a1/b1;

	if(b==0) {ff=0; dff=0;}
	else {ff=a/b;dff=da/b+db*a/b/b;}

	h_ff_hades->SetBinContent(i,ff);
	h_ff_hades->SetBinError(i,dff);
	}


// saving the histograms and the ntuple
	out->cd();
	nt1ff->Print();
	nt1ff->Write();
	h_4pi->Write();
	h_hades->Write();
	h_acc->Write();
	h_qed_4pi->Write();
	h_qed_hades->Write();
	h_ff_4pi->Write();
	h_ff_hades->Write();
}
