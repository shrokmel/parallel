//  write.cpp
//  Created by Arvind Ravichandran on 20/2/16.

#include "main.h"

using namespace std;

ofstream fp("output/coords.xyz");

void vmdwrite(){
    fp << N << "\n\n";
    if (dim==2){
        for (int n=0; n< N; n++){
            fp << "C\t" << R[n][0]-L*ifloor(R[n][0]/L) << "\t" << R[n][1]-L*ifloor(R[n][1]/L) << "\t" << 0 << endl;
        }
    }
    if (dim==3){
        for (int n=0; n<N; n++){
            fp << "C\t" << R[n][0]-L*ifloor(R[n][0]/L) << "\t" << R[n][1]-L*ifloor(R[n][1]/L) << "\t" << R[n][2]-L*ifloor(R[n][2]/L) << endl;
        }
    }
    
}
