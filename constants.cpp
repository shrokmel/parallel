// Copyleft Arvind Ravichandran & Ozer Duman
// Sat Feb 20 00:06:01 CET 2016
// constants.cpp
// Description:
 
#include "main.h"

int dt=1e-3;            // Time Ste
int total_steps=1e3;    // Total Steps
int N=10;        	// Number of particles 
int dim=3;		// Dimensions
double m=1.0;		// mass
double rho=0.5;		// density

// Diffusion
double gam=10;
double kT=1.0;
double Dr=0.01;
double Dt=kT/gam;

// Lennard Jones
double eps=1.0;
double sig=1.0;
double eps48=48.0*eps;
double sig2=sig*sig;
double rcut=2.5*sig;
double rcut2=rcut*rcut;

