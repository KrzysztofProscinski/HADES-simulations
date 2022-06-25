{
//R__LOAD_LIBRARY ($PLUTOLIBDIR/libPluto.so);
//gSystem->CompileMacro( "PHadesAcc.C");

// output file
	TFile *out = new TFile("pp_ppomega.root","recreate");


	
// definition of reaction
	PReaction my_reaction("4.5","p","p","p p w [pi0 [g g] dilepton [e+ e-] ] ", "reakcja1", 1, 0, 0,1); //Dalitz decay

// ntuple
	TNtuple *nt = new TNtuple("nt","pp_ppomega","minvgg:minvpp:minvee:minveegg:minveepp:ep_p:ep_theta:em_p:em_theta:p1_p:p1_theta:p2_p:p2_theta:pi_p:pi_theta:g1_p:g1_theta:g2_p:g2_theta:coswlab:coswcom:rap:minv:w:hadacc:opang");

// loading PHadesAcc()
	my_reaction.AddBulk(new PHadesAcc());	




// histograms: definitions
//	TH1F *h_acc = new TH1F("histogramacc","Weight;Acc;Counts",14,0.2,1.2);		//acceptance
//	TH2F *h_dalitz = new TH2F("dalitz","Dalitz;(Invariant mass p_{1} #omega (GeV))^{2};(Invariant mass p_{2} #omega (GeV))^{2}",100,2.0,7.0,100,2.0,7.0); //Dalitz plot

// histograms: filling
//	my_reaction.Do(h_acc,"acc=_hadacc;_x=acc"); //acceptance
//	my_reaction.Do(h_dalitz,"minv1=([p,1]+[omega,1])->M();minv2=([p,2]+[omega,1])->M();msq1=minv1*minv1;msq2=minv2*minv2;_x=msq1;_y=msq2");


// boost from LAB frame to C.o.M. frame
	my_reaction.Do("_q1=[w,1];_q2=([p,1]+[p,2]+[w,1]);_q1->Boost(_q2)");
	
// filling ntuple
my_reaction.Output(nt,"minvgg=([g,1]+[g,2])->M();minvpp=([p,1]+[p,2])->M();minvee=([e+,1]+[e-,1])->M();minveegg=([e+,1]+[e-,1]+[g,1]+[g,2])->M();minveepp=([e+,1]+[e-,1]+[p,1]+[p,2])->M();ep_p=[e+,1]->P();ep_theta=[e+,1]->Theta();em_p=[e-,1]->P();em_theta=[e-,1]->Theta();pi_p=[pi0,1]->P();pi_theta=[pi0,1]->Theta();g1_p=[g,1]->P();g1_theta=[g,1]->Theta();g2_p=[g,2]->P();g2_theta=[g,2]->Theta();p1_p=[p,1]->P();p1_theta=[p,1]->Theta();p2_p=[p,2]->P();p2_theta=[p,2]->Theta();minv=([e+,1]+[e-,1])->M();coswlab=cos([omega,1]->Theta()); coswcom=cos(_q1->Theta()); rap=[omega,1]->Rapidity(); w=_hadacc*_opang; hadacc=_hadacc; opang=_opang"); //Dalitz decay



// loop
	my_reaction.Print();
	my_reaction.Preheating(100);
//	my_reaction.Loop(1000); //shorter loop
	my_reaction.Loop(1000000); //longer loop


// histograms: drawing
//	TCanvas *c1 = new TCanvas("mass", "invmass",800,500);
//	h_acc->Draw();			//acceptance
//	h_dalitz->Draw("colz");

// saving to file
	out->cd();
	nt->Print();
	nt->Write();
//	out->Close();
}
