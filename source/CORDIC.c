#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "CORDIC.h"

void cordic(FIXED_POINT cos, FIXED_POINT sin, FIXED_POINT *mag, FIXED_POINT *theta)
{
    FIXED_POINT currentCos = cos;
    FIXED_POINT currentSin = sin;
    FIXED_POINT thetaRotated = 0.0;
    FIXED_POINT ninetyDeg = (FIXED_POINT)M_PI_2;
    FIXED_POINT circleRads = (FIXED_POINT)M_2_PI;
    FIXED_POINT CORDIC_SCALE_FACTOR = 0.60735;

    // Compute magnitude using standard pythagorean theorem:

    // Rotate initially within the first quadrant:
    while (currentCos < 0 | currentSin < 0)
    {
        printf("Angles not in first quadrant. Rotating...\n");
        // Rotate back 90 degrees
        currentCos += ninetyDeg;
        currentSin += ninetyDeg;
#ifdef DEBUG_MODE
        printf("Rotated to currentCos = %f, currentSin = %f\n", (float)currentCos, (float)curerntSin);
#endif
    }

    
}