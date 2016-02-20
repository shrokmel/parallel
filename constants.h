//constants.h

#pragma once

extern int dt;		// Time Step
extern int total_steps;	// Total Steps
extern int N;		// Number of particles 
extern int dim;		// Dimensions


// Diffusion
extern double gam=10;
extern double kT=1.0;
extern double Dr=0.01;
extern double Dt=kT/gam;
 		 
// Lennard Jones
extern double eps=1.0;
extern double sig=1.0;
extern double eps48=48.0*eps;
extern double sig2=sig*sig;
extern double rcut=2.5*sig;
extern double rcut2=rcut*rcut;
 		
