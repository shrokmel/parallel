// Copyleft Arvind Ravichandran
// Mon Mar 16 17:25:26 CET 2015
// init.cpp
// Description: Initialization

#include "main.h"

using namespace std;

// Pseudo random number generator with Mersenne Twister algorithm
MTRand randi;

// Variables for initVelocities()
double *sumv = new double [dim];	// COM velocity
double sumv2;				// Kinetic energy
//double fs;				// Scale factor

void initialize(){
	
	// Initializations (N = 4*M**2 for 2-D and N = 4*M**3 for 3-D)
	R = new double* [N];	// Positions 
	V = new double* [N];	// Velocities
	F = new double* [N];	// Forces 
	phi = new double[N]; 	// Orientation
	
	// Define global variable L - the length of box
	L = pow(N/rho, 1.0/dim);	

	for (int i = 0; i<N; i++) {
		R[i] = new double[dim];
		V[i] = new double[dim];
		F[i] = new double[dim];
	}

	for (int i=0; i<N; i++){
		phi[i] = 2*PI*randi.rand();
	}

	initPositions();	// Populate r array in cubic lattice
	initVelocities();	// Populate v array with random velocities
}

void initPositions(){

	// Find M large enough to fit npart atoms on an fcc lattice
	int M = 1;

	// For 2-D, find M
	if (2 == dim){
		while (4*M*M<N) {
			++M;
		}
	}
	
	// For 3-D, find M
	if (3 == dim){
		while (4*M*M*M<N) {
			++M;
		}
	}
	
	// Prepare a FCC cubic cell
	double a2 = L/M;				// define unit size
	double xCell[4] = {0.25, 0.75, 0.75, 0.25};	
	double yCell[4] = {0.25, 0.75, 0.25, 0.75};
	double zCell[4] = {0.25, 0.25, 0.75, 0.75};

	// Populate cubic/planar lattice
	int n = 0;
	if (2 == dim){
		for (int x = 0; x < M; x++){
			for (int y = 0; y < M; y++){
				for (int k = 0; k < 4; k++){
					if (n < N){
						R[n][0] = (x + xCell[k])*a2;
						R[n][1] = (y + yCell[k])*a2;
						++n;
					}
				}
			}
		}
	}
	else if (3 == dim){
		for (int x = 0; x < M; x++){
			for (int y = 0; y < M; y++){
				for (int z = 0; z < M; z++){	
					for (int k = 0; k < 4; k++){
						if (n < N){
							R[n][0] = (x + xCell[k])*a2;
							R[n][1] = (y + yCell[k])*a2;
							R[n][2] = (z + zCell[k])*a2;
							++n;
						}
					}
				}
			}
		}
	}
}


void initVelocities(){

	// Initialize the PRNG with time
   	unsigned int saat = (unsigned int)time(0);
   	randi.seed(saat);

	sumv[0] = 0; sumv[1] = 0;

	// Set random velocities
	for (int i = 0; i<N; i++){
		for (int k = 0; k<dim; k++){
			// Random number between -0.5 and 0.5 for all components
			V[i][k] = randi.rand()-0.5;	
		}
	
		for (int k = 0; k<dim; k++){
			// COM velocity
			sumv[k] += V[i][k];
		}
		
		for (int k = 0; k<dim; k++){		
			// Kinetic energy
			sumv2 += V[i][k] * V[i][k];
		}
	}

	// COM velocity	
	for (int k = 0; k<dim; k++){
		sumv[k] = sumv[k]/N;
	}		
			
	// Mean squared velocity
	sumv2 = sumv2/N;

	// Scale factor of velocities
	double fs = sqrt(2*T/sumv2);
		
	// Scale velocities appropriately
	for (int i = 0; i<N; i++){
		for (int k = 0; k<dim; k++){
			V[i][k] = (V[i][k] - sumv[k])*fs;
		}
	}
}	
