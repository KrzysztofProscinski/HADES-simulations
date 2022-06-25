macros:
- rootlogon.C			- makro executed during launching of the root; it loads Pluto libraries and executes PHadesAcc.C macro; for working it needs the acc_matrices.root file
- PHadesAcc.C			- makro for cuts and smearing for chosen particles, by default for e+ e-
- ppomega1.C			- simulation of the 1st reaction with omega
- ppomega2.C			- simulation of the 2nd reaction with omega
- ppeta1.C			- simulation of the 1st reaction with eta
- ppeta2.C			- simulation of the 2nd reaction with eta
- ppetap1.C			- simulation of the 1st reaction with eta'
- ppetap2.C			- simulation of the 2nd reaction with eta'
- ppa1.C			- simulation of the 1st reaction with a0+
- ffomega.C			- simulation of form factor of meson omega
- loop.C, loop.h		- drawing histograms from the simulation of the 1st reaction with omega
- loop2.C, loop2.h		- drawing histograms from the simulation of the 2nd reaction with omega
- loopeta.C, loopeta.h		- drawing histograms from the simulation of the 1st reaction with eta
- loopeta2.C, loopeta2.h	- drawing histograms from the simulation of the 2nd reaction with eta
- loopetap1.C, loopetap1.h	- drawing histograms from the simulation of the 1st reaction with eta'
- loopetap2.C, loopetap2.h	- drawing histograms from the simulation of the 2nd reaction with eta'
- loopa.C, loopa.h		- drawing histograms from the simulation of the 1st reaction with a0+


simulated reactions:
- omega 1st:	p p -> p p omega -> p p (e+ e- pi0) -> p p (e+ e- (g g))
- omega 2nd:	p p -> p p omega -> p p (e+ e-)
- eta 1st:	p p -> p p eta -> p p (e+ e- g)
- eta 2nd:	p p -> p p eta -> p p (e+ e- pi+ pi-)
- eta' 1st:	p p -> p p eta' -> p p (g rho0) -> p p (g (pi+ pi-))
- eta 2nd:	p p -> p p eta' -> p p (pi+ pi- eta) -> p p (pi+ pi- (e+ e-))
- a0+ 1st:	p p -> p n a0+ -> p n (K+ K0S) -> p n (K+ (pi+ + pi-))



macros executing:
- macros for simulations:
".x [name].C"
- macros for drawing histograms:
".x [name].C"
"[name] n"
"n.Loop()"



remarks:
- execution of macros is possible only after launching root
- "rootlogon.C" macro can be skipped, but one have to uncomment the first and the second line in macros for simulations
- to make histogram without cuts one have to delete part ",w" in a line where the histogram is being filled eg.:
    "ee_theta->Fill(ep_theta*57.2958,em_theta*57.2958,w);"
    change to:
    "ee_theta->Fill(ep_theta*57.2958,em_theta*57.2958);"
- to do simulation with cuts on different particles one have to edit "PHadesAcc.C" macro, uncomment a line with certain set of particles (lines 56-63) and comment out the line with previous chosen set of particles
  then one have to launch root again and then execute macro
- to draw another histogram in macro for drawing histograms one have to uncomment certain line in the end of the macro and comment out the line for previously drawn histogram
- to inspect content of .root files one have to write a command "new TBrowser" in the terminal
- for executing the "ffomega.C" macro, cuts must be applied on particles: e+, e-, g; otherwise the results will be incorrect