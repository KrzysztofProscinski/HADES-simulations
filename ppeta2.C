{
//R__LOAD_LIBRARY ($PLUTOLIBDIR/libPluto.so);
//gSystem->CompileMacro( "PHadesAcc.C");

// output file
	TFile *out = new TFile("pp_ppeta2.root","recreate");


	
// definition of reaction
	PReaction my_reaction(Ekin,"p","p","p p eta [ pi+ pi- e- e+ ]");

// ntuple
	TNtuple *nteta2 = new TNtuple("nteta2","pp_eta2","cp:minvpp:minvpipi:minvee:minveepp:minveepipi:eta_p:eta_theta:ep_p:ep_theta:em_p:em_theta:p1_p:p1_theta:p2_p:p2_theta:pip_p:pip_theta:pim_p:pim_theta:cosnlab:cosncom:rap:minv:w:hadacc:opang");

//loading PHadesAcc()
	my_reaction.AddBulk(new PHadesAcc());




// boost from LAB frame to C.o.M. frame
	my_reaction.Do("_q1=[eta,1];_q2=([p,1]+[p,2]+[eta,1]);_q1->Boost(_q2)");

// things needed for checking the CP symmetry violation
	my_reaction.Do("epx=[e+,1]->Px();epy=[e+,1]->Py();epz=[e+,1]->Pz();emx=[e-,1]->Px();emy=[e-,1]->Py();emz=[e-,1]->Pz();pipx=[pi+,1]->Px();pipy=[pi+,1]->Py();pipz=[pi+,1]->Pz();pimx=[pi-,1]->Px();pimy=[pi-,1]->Py();pimz=[pi-,1]->Pz();kex=epy*emz-epz*emy;key=epz*emx-epx*emz;kez=epx*emy-epy*emx;kpix=pipy*pimz-pipz*pimy;kpiy=pipz*pimx-pipx*pimz;kpiz=pipx*pimy-pipy*pimx;ken=sqrt(kex*kex+key*key+kez*kez);kpin=sqrt(kpix*kpix+kpiy*kpiy+kpiz*kpiz);kexn=kex/ken;keyn=key/ken;kezn=kez/ken;kpixn=kpix/kpin;kpiyn=kpiy/kpin;kpizn=kpiz/kpin;crossx=keyn*kpizn-kezn*kpiyn;crossy=kezn*kpixn-kexn*kpizn;crossz=kexn*kpiyn-keyn*kpixn;sc1sq=crossx*crossx+crossy*crossy+crossz+crossz;sc1=sqrt(abs(sc1sq))/sqrt(2);sc2=kexn*kpixn+keyn*kpiyn+kezn*kpizn");

// filling ntuple
	my_reaction.Output(nteta2,"minvpipi=([pi+,1]+[pi-,1])->M();minvpp=([p,1]+[p,2])->M();minvee=([e+,1]+[e-,1])->M();minveepipi=([e+,1]+[e-,1]+[pi+,1]+[pi-,1])->M();minveepp=([e+,1]+[e-,1]+[p,1]+[p,2])->M();eta_p=[eta,1]->P();eta_theta=[eta,1]->Theta();ep_p=[e+,1]->P();ep_theta=[e+,1]->Theta();em_p=[e-,1]->P();em_theta=[e-,1]->Theta();p1_p=[p,1]->P();p1_theta=[p,1]->Theta();p2_p=[p,2]->P();p2_theta=[p,2]->Theta();pip_p=[pi+,1]->P();pip_theta=[pi+,1]->Theta();pim_p=[pi-,1]->P();pim_theta=[pi-,1]->Theta();minv=(([e+,1]+[e-,1])->M();cosnlab=cos([eta,1]->Theta());cosncom=cos(_q1->Theta());rap=[eta,1]->Rapidity();w=_hadacc*_opang; hadacc=_hadacc; opang=_opang; cp=sc1*sc2");



// loop
	my_reaction.Print();

	my_reaction.Preheating(100);
//	my_reaction.Loop(1000); //shorter loop
	my_reaction.Loop(1000000); //longer loop
	

// saving to file
	out->cd();
	nteta2->Print();
	nteta2->Write();
	out->Close();
}
