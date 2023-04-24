#include <ap_fixed.h>
#include <stdio.h>

typedef ap_fixed<32, 16> FIXED_POINT;


void cordicRotator(FIXED_POINT theta, FIXED_POINT *sin, FIXED_POINT *cos);
