#ifndef DATATYPES_H
#define DATATYPES_H
#include <ap_fixed.h>
#include "ap_int.h"

////////////////////    CORDIC-SPECIFIC TYPES    //////////////////////////
#define FIXED_BITS_M 24
#define FIXED_BITS_N 12

typedef ap_fixed<FIXED_BITS_M, FIXED_BITS_N> FIXED_POINT; //!< AP-Fixed datype for consistent calculation in the CORDIC
// typedef float FIXED_POINT; //!< Placeholder datatype for vscode development ease.

////////////////////////////////////////////////////////////////////////////



//////////////////////////  FIR-SPECIFIC TYPES /////////////////////////////
#define FIR_INT_INPUT_WIDTH 10
#define FIR_INT_OUTPUT_WIDTH 10

typedef ap_int<FIR_INT_INPUT_WIDTH> FIR_INT_INPUT; //!< Fixed-width integer datatype for FIR inputs
typedef ap_int<FIR_INT_OUTPUT_WIDTH> FIR_INT_OUTPUT; //!< Fixed-width integer datatype for FIR outputs

////////////////////////////////////////////////////////////////////////////





#endif
