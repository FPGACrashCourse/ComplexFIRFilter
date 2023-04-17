#ifndef CORDIC_H
#define CORDIC_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ap_fixed.h>

#define FIXED_BITS_M 32
#define FIXED_BITS_N 20

//#define DEBUG_MODE

//typedef ap_fixed <FIXED_BITS_M, FIXED_BITS_N> FIXED_POINT; //!< AP-Fixed datype for consistent calculation
typedef float FIXED_POINT; //!< Placeholder datatype for vscode development ease.

#endif // CORDIC_H