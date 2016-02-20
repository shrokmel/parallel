// Copyleft Arvind Ravichandran & Ozer Duman
// Fri Feb 19 23:53:11 CET 2016
// main.cpp
// Description: The world's most awesome MD parallel code!!
 
#include "main.h"

using namespace std;

// Random number generator

MTRand randi;

///////////////////////////////////////////////////////
// Get gaussian random number for mu=0, sigma=1

inline double get_ran_gaussian()
{
  double a1 = 0.;
  double a2 = 0.;
  static bool store = false;
  static double stored_a2 = 0.;
  double p, q;

  // use stored number
  if (store) {
    store = false;
    return stored_a2;
  }
  do {
    a1 = 2.*randi.randExc()-1.;
    a2 = 2.*randi.randExc()-1.;
    q = a1*a1 + a2*a2;
  } while (q >= 1. || q == 0.);
  p = sqrt(-2.*log(q)/q);
  // recycle second number
  stored_a2 = a2*p;
  store = true;
  return a1*p;
}

///////////////////////////////////////////////////////
// Get gaussian random number for arbitrary mu,sigma
inline double get_ran_gaussian(double mu, double sigma)

{
  double a1 = 0.;
  double a2 = 0.;
  static bool store = false;
  static double stored_a2 = 0.;
  double p, q;

  // use stored number
  if (store) {
    store = false;
    return mu - sigma*stored_a2;
  }

  do {
    a1 = 2.*randi.randExc()-1.;
    a2 = 2.*randi.randExc()-1.;
    q = a1*a1 + a2*a2;
  } while (q >= 1. || q == 0.);
  p = sqrt(-2.*log(q)/q);
  
  // recycle second number
  stored_a2 = a2*p;
  store = true;
  return mu - sigma*a1*p;
}
 


int main()
{
	// Initialize	
	initialize();

	// Main Loop
	for (int t=0; t<total_steps; t++){
		for(int n=0; n<N; n++){
			
			// Rotational Diffusion
			phi[n] += sqrt(2*Dr*dt)*get_ran_gaussian(); 		

			// Propogate x,y,z positions
			for (int d=0; d<dim; d++){
				// Velocity
				V[N][d] += 1/(2*m)*F[N][d];
			
				// Position
				R[N][d] += sqrt(2*Dt*dt)*get_ran_gaussian() + V[N][d]*dt;
			}
		}	
		// Force Calculation
		for (int n1=0; n1<N-1; n1++){
			for (int n2=n1+1; n2<N; n2++){
				double dx = R[n2][0]-R[n1][0];
				double dy = R[n2][1]-R[n1][1];
				double dz = R[n2][2]-R[n1][2];

				double dr2 = dx*dx + dy*dy + dz*dz;

				if (dr2<rcut2){
					double p3 = sig2/dr2;
					p3 = p3*p3*p3;
					double tempFx = eps48*(p3*p3 - p3/2.)*dx/dr2;
					double tempFy = eps48*(p3*p3 - p3/2.)*dy/dr2;
					double tempFz = eps48*(p3*p3 - p3/2.)*dz/dr2;

					F[n1][0] -= tempFx;
					F[n1][1] -= tempFy;
					F[n1][2] -= tempFz;

					F[n2][0] += tempFx;
					F[n2][1] += tempFy;
					F[n2][2] += tempFz;
				}
			}
		}					
		
		// Half velocity propogation or whatever
		for (int n=0; n<N; n++){
			for (int d=0; d<dim; d++){
				// Velocity
				V[N][d] += 1/(2*m)*F[N][d];
			}
		}
	} // End of Simulation
	return 0;
}
