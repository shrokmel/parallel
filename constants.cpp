// Copyleft Arvind Ravichandran & Ozer Duman
// Sat Feb 20 00:06:01 CET 2016
// constants.cpp
// Description:
 
#include "main.h"

double dt=1e-3;            // Time Ste
double total_steps=1e+6;    // Total Steps
int nsamp = 1e+3;     // Sampling rate
int N=100;        	// Number of particles
int dim=3;		// Dimensions
double m=1.0;		// mass
double rho=0.5;		// density
double L;        // boxsize

// Diffusion
double gam=10;
double kT=0;
double Dr=0;
double Dt=kT/gam;

// Lennard Jones
double eps=1.;
double sig=1.0;
double eps48=48.0*eps;
double sig2=sig*sig;
double rcut=2.5*sig;
double rcut2=rcut*rcut;

// Self propulsion
double Fmc = 1.0;


