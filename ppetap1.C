{
//R__LOAD_LIBRARY ($PLUTOLIBDIR/libPluto.so);
//gSystem->CompileMacro( "PHadesAcc.C");

// output file
	TFile *out = new TFile("pp_ppetap1.root","recreate");	



// definition of reaction
	PReaction my_reaction(Ekin,"p","p","p p eta' [g rho0 [pi+ pi-] ]");

// ntuple
	TNtuple *ntetap1 = new TNtuple("ntetap1","pp_etap1","minvpp:minvg:minvpipi:minvpipipp:minvpipig:etap_p:etap_theta:p1_p:p1_theta:p2_p:p2_theta:rho_p:rho_theta:g_p:g_theta:pip_p:pip_theta:pim_p:pim_theta:cosnlab:cosncom:rap:minv:w:hadacc:opang");

// loading PHadesAcc()
	my_reaction.AddBulk(new PHadesAcc());





/// histograms: definitions
	TH2F *h_dalitz = new TH2F("dalitz","Dalitz;(Invariant mass p_{1} #eta' (GeV))^{2};(Invariant mass p_{2} #eta' (GeV))^{2}",150,3.0,6.0,150,3.0,6.0); //Dalitz plot

// histograms: filling
	my_reaction.Do(h_dalitz,"minv1=([p,1]+[eta',1])->M();minv2=([p,2]+[eta',1])->M();msq1=minv1*minv1;msq2=minv2*minv2;_x=msq1;_y=msq2");


//boost from LAB frame to C.o.M. frame
	my_reaction.Do("_q1=[eta',1];_q2=([p,1]+[p,2]+[eta',1]);_q1->Boost(_q2)");

// filling ntuple
	my_reaction.Output(ntetap1,"minvg=([g,1])->M();minvpp=([p,1]+[p,2])->M();minvpipi=([pi+,1]+[pi-,1])->M();minvpipig=([pi+,1]+[pi-,1]+[g,1])->M();minvpipipp=([pi+,1]+[pi-,1]+[p,1]+[p,2])->M();etap_p=[eta',1]->P();etap_theta=[eta',1]->Theta();p1_p=[p,1]->P();p1_theta=[p,1]->Theta();p2_p=[p,2]->P();p2_theta=[p,2]->Theta();rho_p=[rho0,1]->P();rho_theta=[rho0,1]->Theta();g_p=[g,1]->P();g_theta=[g,1]->Theta();minv=([g,1])->M();pip_p=[pi+,1]->P();pip_theta=[pi+,1]->Theta();pim_p=[pi-,1]->P();pim_theta=[pi-,1]->Theta();cosnlab=cos([eta',1]->Theta());cosncom=cos(_q1->Theta());rap=[eta',1]->Rapidity(); w=_hadacc*_opang; hadacc=_hadacc; opang=_opang");



// loop
	my_reaction.Print();

	my_reaction.Preheating(100);
//	my_reaction.Loop(1000); //shorter loop
	my_reaction.Loop(1000000); //longer loop


// histograms: drawing
//	TCanvas *c1 = new TCanvas("mass", "invmass",800,500);
	h_dalitz->Draw("colz");

// saving to file
	out->cd();
	ntetap1->Print();
	ntetap1->Write();
//	out->Close();
}
