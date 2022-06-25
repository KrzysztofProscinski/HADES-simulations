//TITLE <UserClass> Very small acceptance filter (setting variables for batch) including opening angle.

//loading of needed macros
#include "../include/PBulkInterface.h"
//#include "../src/PBulkInterface.cc"
#include "../include/PUtils.h"
//#include "../src/PUtils.cc"
#include "../include/TH2.h"
#include "../include/TFile.h"
#include <TClass.h>

// a PBulkInterface function
class PHadesAcc : public PBulkInterface {

private:
    Double_t *hadacc, *opang, *opang2;
    TH2F *histm, *histp;

 public:
    
    PHadesAcc();

    Bool_t Modify(PParticle ** stack, int *decay_done, int * num, int stacksize);  //bulk interface

    ClassDef(PHadesAcc,0) 
};

// acceptance distributions
PHadesAcc::PHadesAcc() {
    hadacc = makeStaticData()->GetBatchValue("_hadacc");
    opang  = makeStaticData()->GetBatchValue("_opang");

// obtaining acceptance matrices from a file
    TFile *fin = new TFile("acc_matrices.root");
    histp = (TH2F*)fin->Get("acc_ep");
    histm = (TH2F*)fin->Get("acc_em");

}

// modifying loop
bool PHadesAcc::Modify(PParticle ** stack, int *decay_done, int * num, int stacksize) {


// acceptance 100%
    *hadacc=1.;

    for (int i=0; i< *num; i++) {
	PParticle * cur = stack[i];
//	cur->Print();

	
// particles which we want to have cuts on
// ATTENTION: one have to uncomment one set of particles, which we want to have the cuts on
// another sets have to be commented out:

//if ( cur->Is("e+") || cur->Is("e-")) {
//if ( cur->Is("e+") || cur->Is("e-") || cur->Is("p")) {
if ( cur->Is("e+") || cur->Is("e-") || cur->Is("g")) {
//if ( cur->Is("pi+") || cur->Is("pi-") || cur->Is("p")) {
//if ( cur->Is("pi+") || cur->Is("pi-") || cur->Is("g")) {
//if ( cur->Is("e+") || cur->Is("e-") || cur->Is("pi+") || cur->Is("pi-")) {
//if ( cur->Is("p") || cur->Is("K+") || cur->Is("pi+") || cur->Is("pi-")) {
//if ( cur->Is("K+")|| cur->Is("pi+") || cur->Is("pi-")) {

// smearing for angle and momentum measurements
	    double mom = cur->P();

	    double theta = cur->Theta();
	    double phi   = cur->Phi();

	    double momentum_resolution = 0.038; //parametryzacja dla pedow >1 GeV
	    if(mom<1.)
	    {momentum_resolution = 0.0109*mom+0.01071;} // parametrization for momenta <1 GeV

	    double angular_resolution = 0.1*TMath::Pi()/180.;

	    double mom_measured   = PUtils::sampleGaus(mom, mom*momentum_resolution);
	    double theta_measured = PUtils::sampleGaus(theta, angular_resolution);
	    double phi_measured   = PUtils::sampleGaus(phi, angular_resolution);

	    cur->SetRho(mom_measured);
	    cur->SetTheta(theta_measured);
	    cur->SetPhi(phi_measured);

 	    cur->ResetE();

// cuts on angles and momenta

	if (cur->Is("g") || cur->Is("p")){
	    if (cur->Is("g")){
	    	if (cur->Theta() > ((45./180)*TMath::Pi())){*hadacc=0.;}
	    	if (cur->Theta() < ((18./180)*TMath::Pi())){*hadacc=0.;}
	   }
	    else{
		if (cur->Theta() > ((88./180)*TMath::Pi())){*hadacc=0.;}
	    	if (cur->Theta() < ((18./180)*TMath::Pi()) && cur->Theta() > ((7./180)*TMath::Pi())){*hadacc=0.;}
	    }
	    
	    if (cur->P() < 0.1)  {
		*hadacc=0.;
	    }
	}

// acceptance from acceptance matrices
	    double acc=1.;
	    double had=*hadacc;
if(had!=0){    if (cur->Is("e+") || cur->Is("K+") || cur->Is("pi+")){acc=histp->GetBinContent(mom*50./3.,theta*57.2958/2.);}
		   if (cur->Is("e-") || cur->Is("pi-")){acc=histm->GetBinContent(mom*50./3.,theta*57.2958/2.);}

	    *hadacc=acc*had;}


	}

    }

// cuts on opening angle
    *opang=1.;

    //the opang:
    for (int i=0; i< *num; i++) {
	PParticle * ep = stack[i];
	if (ep->Is("e+")) {
	    for (int i=0; i< *num; i++) {
		PParticle * em = stack[i];
		if (em->Is("e-")) {
		    Double_t oa= ep->Vect().Angle(em->Vect());
		    if (oa < ((4./180)*TMath::Pi())){
			*opang=0.;
		    }
		}
	    }
	    
	}
    }


    return kTRUE;
};
