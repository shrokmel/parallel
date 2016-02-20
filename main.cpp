// Copyleft Arvind Ravichandran & Ozer Duman
// Fri Feb 19 23:53:11 CET 2016
// main.cpp
// Description: The world's most awesome MD parallel code!!
 
#include "main.h"

using namespace std;

int main()
{

    initialize();
    vmdwrite();

    resetVelocity();

    // Main Loop
    for (int t=0; t<total_steps; t++){
        integ1();
        resetForce();
        LennardJones();
        propulsion();
        integ2();
        

        // Write data
        if (t % nsamp == 0) {
            vmdwrite();
        }

    }
        return 0;
}
