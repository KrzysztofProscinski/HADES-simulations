#include<iostream>


Bool_t rootlogon(void){

R__LOAD_LIBRARY ($PLUTOLIBDIR/libPluto.so);

//compilation the PHadesACC.C
gSystem->CompileMacro( "PHadesAcc.C");

return kTRUE;
}
