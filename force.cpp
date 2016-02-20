// Copyleft Arvind Ravichandran
// Sat Feb 20 17:09:38 CET 2016
// force.cpp
// Description: All Forces

#include "main.h"

using namespace std;

void propulsion(){
    if(dim==2){
        for (int n = 0; n < N; n++) {
            F[n][0] += Fmc*cos(phi[n]) - gam*V[n][0];
            F[n][1] += Fmc*sin(phi[n]) - gam*V[n][1];
        }
    }
    else if (dim==3){
        for (int n = 0; n < N; n++) {
            F[n][0] += Fmc*sin(theta[n])*cos(phi[n]) - gam*V[n][0];
            F[n][1] += Fmc*sin(theta[n])*sin(phi[n]) - gam*V[n][1];
            F[n][2] += Fmc*cos(theta[n]) - gam*V[n][2];
        }
    }
}

void LennardJones(){
    
    // Run through first index
    for (int n1=0; n1<(N-1); n1++){
        // Run through second index
        for (int n2=n1+1; n2<N; n2++){
            double dr[3];
            double dr2 = 0;
            
            // Running through dimensions
            for (int d=0; d<dim; d++){
                dr[d]=R[n1][d]-R[n2][d];
                dr[d]-=L*dnearbyint(dr[d]/L);
                dr2+= dr[d]*dr[d];
            }
            
            // If smaller than cutoff distance
            if (dr2<rcut2){
                
                double p3 = sig2/dr2;
                p3 = p3*p3*p3;
                
                for (int d=0; d<dim; d++){
                    double tempF = eps48*(p3*p3 - p3/2.)*dr[d]/dr2;
                    //cout << tempF << "\t" << dr[d] << endl;
                    F[n1][d]+= tempF;
                    F[n2][d]-= tempF;
                }
            }
        }
    }
}
