//functions.h

#pragma once
#include "MersenneTwister.h"

// init.cpp
void initialize();
void initPositions();
void initVelocities();

// force.cpp
void propulsion();
void LennardJones();

// write.cpp
void vmdwrite();

// integrate.cpp
void integ1();
void integ2();
void resetForce();
void resetVelocity();

// random.cpp
//inline double get_ran_gaussian(MTRand& randi);
