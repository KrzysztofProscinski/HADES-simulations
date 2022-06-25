{
//R__LOAD_LIBRARY ($PLUTOLIBDIR/libPluto.so);
//gSystem->CompileMacro( "PHadesAcc.C");
	
// output file
	TFile *out = new TFile("pp_ppa.root","recreate");



//new particle
	PStaticData *sd = makeStaticData();
	sd->AddParticle ( -1, "a0", 0.98);
	sd->SetParticleTotalWidth ("a0", 0.0972);

	sd->SetParticleMeson ("a0");
	sd->SetParticleCharge ("a0", 1);
	sd->SetParticleSpin ("a0", 0);
	sd->SetParticleIsospin ("a0", 1);

	sd->AddDecay("a0_decay", "a0", "K0S, K+", 1.0);



// definition of reaction
	PReaction my_reaction("4.50","p","p","p n a0 [K+ K0S [ pi+ pi- ] ] ", "reakcja1", 1, 0, 0,1);

// ntuple
	TNtuple *nta = new TNtuple("nta","pp_ppa","minvk:minvpk:minvpipi:minvpipik:minvpipipk:pip_p:pip_theta:pim_p:pim_theta:p_p:p_theta:n_p:n_theta:kp_p:kp_theta:k0_p:k0_theta:pdiff:cosalab:cosacom:rap:minv:w:hadacc:opang"); //ntuple

// loading PHadesAcc()
	my_reaction.AddBulk(new PHadesAcc());	




// histograms: definitions
	TH2F *h_dalitz = new TH2F("dalitz","Dalitz;(Invariant mass p_{1} #omega (GeV))^{2};(Invariant mass p_{2} #omega (GeV))^{2}",200,3.0,7.0,200,3.0,7.0); //Dalitz plot

// histograms: filling
	my_reaction.Do(h_dalitz,"minv1=([p,1]+[a0,1])->M();minv2=([n,1]+[a0,1])->M();msq1=minv1*minv1;msq2=minv2*minv2;_x=msq1;_y=msq2");


// boost from LAB frame to C.o.M. frame
	my_reaction.Do("_q1=[a0,1];_q2=([p,1]+[n,1]+[a0,1]);_q1->Boost(_q2)");

// filling ntuple
my_reaction.Output(nta,"minvk=([K+,1])->M();minvpk=([p,1]+[K+,1])->M();minvpipi=([pi+,1]+[pi-,1])->M();minvpipik=([pi+,1]+[pi-,1]+[K+,1])->M();minvpipipk=([pi+,1]+[pi-,1]+[p,1]+[K+,1])->M();pip_p=[pi+,1]->P();pip_theta=[pi+,1]->Theta();pim_p=[pi-,1]->P();pim_theta=[pi-,1]->Theta();p_p=[p,1]->P();p_theta=[p,1]->Theta();n_p=[n,1]->P();n_theta=[n,1]->Theta();kp_p=[K+,1]->P();kp_theta=[K+,1]->Theta();;k0_p=[K0S,1]->P();k0_theta=[K0S,1]->Theta();pdiff=k0_p-kp_p;cosalab=cos([a0,1]->Theta()); cosacom=cos(_q1->Theta()); rap=[a0,1]->Rapidity(); w=_hadacc*_opang; hadacc=_hadacc; opang=_opang");



// loop
	my_reaction.Print();
	my_reaction.Preheating(100);
	my_reaction.Loop(1000); //shorter loop
//	my_reaction.Loop(1000000); //longer loop


// histograms: drawing
//	TCanvas *c1 = new TCanvas("mass", "invmass",800,500);
	h_dalitz->Draw("colz");

// saving to file
	out->cd();
	nta->Print();
	nta->Write();
//	out->Close();
}
