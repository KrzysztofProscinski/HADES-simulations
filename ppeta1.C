{
//R__LOAD_LIBRARY ($PLUTOLIBDIR/libPluto.so);
//gSystem->CompileMacro( "PHadesAcc.C");

// output file
	TFile *out = new TFile("pp_ppeta.root","recreate");


	
// definition of reaction
	PReaction my_reaction(Ekin,"p","p","p p eta [g dilepton [e- e+] ]");

// ntuple
	TNtuple *nteta = new TNtuple("nteta","pp_eta","minvg:minvpp:minvee:minveeg:minveepp:eta_p:eta_theta:ep_p:ep_theta:em_p:em_theta:p1_p:p1_theta:p2_p:p2_theta:g_p:g_theta:minv:cosnlab:cosncom:rap:w:hadacc:opang");

// loading PHadesAcc()
	my_reaction.AddBulk(new PHadesAcc());




// histograms: definitions
//	TH2F *h_dalitz = new TH2F("dalitz","Dalitz;(Invariant mass p_{1} #eta (GeV))^{2};(Invariant mass p_{2} #eta (GeV))^{2}",100,1.0,9.0,100,1.0,9.0); //Dalitz plot

// histograms: filling
//	my_reaction.Do(h_dalitz,"minv1=([p,1]+[eta,1])->M();minv2=([p,2]+[eta,1])->M();msq1=minv1*minv1;msq2=minv2*minv2;_x=msq1;_y=msq2");


// boost from LAB frame to C.o.M. frame
	my_reaction.Do("_q1=[eta,1];_q2=([p,1]+[p,2]+[eta,1]);_q1->Boost(_q2)");

// filling ntuple
	my_reaction.Output(nteta,"minvpp=([p,1]+[p,2])->M();minvg=([g,1])->M();minvee=([e+,1]+[e-,1])->M();minveeg=([e+,1]+[e-,1]+[g,1])->M();minveepp=([e+,1]+[e-,1]+[p,1]+[p,2])->M();eta_p=[eta,1]->P();eta_theta=[eta,1]->Theta();ep_p=[e+,1]->P();ep_theta=[e+,1]->Theta();em_p=[e-,1]->P();em_theta=[e-,1]->Theta();p1_p=[p,1]->P();p1_theta=[p,1]->Theta();p2_p=[p,2]->P();p2_theta=[p,2]->Theta();g_p=[g,1]->P();g_theta=[g,1]->Theta();minv=([e+,1]+[e-,1])->M();cosnlab=cos([eta,1]->Theta());cosncom=cos(_q1->Theta());rap=[eta,1]->Rapidity();w=_opang*_hadacc; hadacc=_hadacc; opang=_opang; cosnlab=cos([eta,1]->Theta()); cosncom=cos(_q1->Theta())");



// loop
	my_reaction.Print();

	my_reaction.Preheating(100);
//	my_reaction.Loop(1000); //shorter loop
	my_reaction.Loop(1000000); //longer loop


// histograms: drawing
//	TCanvas *c1 = new TCanvas("mass", "invmass",800,500);
//	h_dalitz->Draw("colz");

// saving to file
	out->cd();
	nteta->Print();
	nteta->Write();
	out->Close();
}
