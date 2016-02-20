// Copyleft Arvind Ravichandran
// Sat Feb 20 17:09:38 CET 2016
// integrate.cpp
// Description: Propogator and Integrator
 
#include "main.h"
using namespace std;

MTRand randi;

inline double get_ran_gaussian(MTRand& randi);

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

void integ1(){
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
}

void integ2(){
    for (int n=0; n<N; n++){
        for (int d=0; d<dim; d++){
            // Velocity
            V[n][d] += F[n][d]*dt/(2*m);
        }
    }
}

void resetForce(){
    for (int n = 0; n < N; n++) {
        for (int d = 0; d < dim; d++) {
            F[n][d] = 0.;
        }
    }
}

void resetVelocity(){
    for (int n = 0; n < N; n++) {
        for (int d = 0; d < dim; d++) {
            V[n][d] = 0.;
        }
    }
}
