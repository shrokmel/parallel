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

inline double get_ran_gaussian(MTRand& randi)
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
    
    ofstream fp("coords.xyz");
	// Initialize
	initialize();


	// Main Loop
	for (int t=0; t<total_steps; t++){
		for(int n=0; n<N; n++){
			
			// Rotational Diffusion
			phi[n] += sqrt(2*Dr*dt)*get_ran_gaussian(randi);
            theta[n] += sqrt(2*Dr*dt)*get_ran_gaussian(randi);

			// Propogate x,y,z positions
			for (int d=0; d<dim; d++){
				// Velocity
				V[n][d] += F[n][d]*dt/(2*m);
			
				// Position
				R[n][d] += sqrt(2*Dt*dt)*get_ran_gaussian(randi) + V[n][d]*dt;
			}
		}
        
        for (int n = 0; n < N; n++) {
            for (int d = 0; d < dim; d++) {
                F[n][d] = 0.;
            }
        }
//        
//        // Force Calculation
//		for (int n1=0; n1<(N-1); n1++){
//			for (int n2=n1+1; n2<N; n2++){
//                double dx = R[n1][0]-R[n2][0];
//                dx -= L*dnearbyint( dx/L );
//                double dy = R[n1][1]-R[n2][1];
//                dy -= L*dnearbyint( dy/L );
//                double dz = R[n1][2]-R[n2][2];
//                dz -= L*dnearbyint( dz/L );
//                
//                double dr2 = dx*dx + dy*dy + dz*dz;
//                if (dr2<rcut2){
//                    
//                    double p3 = sig2/dr2;
//                    p3 = p3*p3*p3;
//                    double tempFx = eps48*(p3*p3 - p3/2.)*dx/dr2;
//                    double tempFy = eps48*(p3*p3 - p3/2.)*dy/dr2;
//                    double tempFz = eps48*(p3*p3 - p3/2.)*dz/dr2;
//                    
//                    
//                    F[n1][0] += tempFx;
//                    F[n1][1] += tempFy;
//                    F[n1][2] += tempFz;
//                    
//                    F[n2][0] -= tempFx;
//                    F[n2][1] -= tempFy;
//                    F[n2][2] -= tempFz;
//                }
//			}
//		}
        
//        for (int n = 0; n < N; n++) {
//            F[n][0] -= gam*V[n][0];
//            F[n][1] -= gam*V[n][1];
//            F[n][2] -= gam*V[n][2];
//        }
        
        
        for (int n = 0; n < N; n++) {
            F[n][0] += Fmc*sin(theta[n])*cos(phi[n]) - gam*V[n][0];
            F[n][1] += Fmc*sin(theta[n])*sin(phi[n]) - gam*V[n][1];
            F[n][2] += Fmc*cos(theta[n]) - gam*V[n][2];
        }
		
		// Half velocity propogation or whatever
		for (int n=0; n<N; n++){
			for (int d=0; d<dim; d++){
				// Velocity
				V[n][d] += F[n][d]*dt/(2*m);
			}
		}
        
        // Write data
        if (t % nsamp == 0) {
            fp << N << "\n\n";
            for (int n = 0; n < N; n++) {
                fp << "C\t" << R[n][0]-L*ifloor(R[n][0]/L) << "\t" << R[n][1]-L*ifloor(R[n][1]/L) << "\t" << R[n][2]-L*ifloor(R[n][2]/L) << endl;
            }
        }
        
	} // End of Simulation
	return 0;
}
