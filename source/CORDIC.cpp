/**
 * @file CORDIC.c
 * @author Alex Stepko (axstepko.com)
 * @brief Rectangular to polar CORDIC converter
 * @version 0.1
 * @date 2023-04-17
 *
 * @copyright  Copyright (c) Alex Stepko (axstepko.com) 2023. All rights reserved.
 * 
 */

/**
 * Copyright (c) Alex Stepko (axstepko.com) 2023. All rights reserved.
 * 
 * THIS CODE WRITTEN WHOLLY BY ALEX STEPKO (AXSTEPKO.COM) Redistribution and
 * use in source and binary forms, with or without modification, are
 * STRICTLY PROHIBITED WITHOUT PRIOR WRITTEN PERMISSION from Alex Stepko (axstepko.com). 
 * 
 * This software is provided "as is" and any express or implied warranties, including,
 * but not limited to, the implied warranties of merchantability and fitness for a 
 * particular purpose are disclaimed. In no event shall Alex Stepko (axstepko.com) be 
 * liable for any direct, indirect, incidental, special, exemplary, or consequential 
 * damages (including, but not limited to, procurement of substitute goods or services; 
 * 
 * ACADEMIC INTEGRITY: STUDENTS, RESEARCHERS, OR INSTITUTIONS MAY USE THIS SOFTWARE 
 * FOR EDUCATIONAL OR RESEARCH PURPOSES ONLY. YOU ARE RESPONSIBLE FOR ENSURING THAT 
 * THE USAGE OF THIS SOFTWARE COMPLIES WITH THE COPYRIGHT POLICY STATED ABOVE, IN 
 * ADDITION TO YOUR INSTITUTION'S POLICIES ON ACADEMIC INTEGRITY AND PLAGARISM. 
 * IT IS PROHIBITED TO REPRESENT THIS WORK AS YOUR OWN, INCLUDING BUT NOT LIMITED 
 * TO THE DUPLICATION, MODIFICATION, OR DISTRUBTION OF THIS SOFTWARE WITHOUT PRIOR 
 * WRITTEN PREMISSION FROM THE SOFTWARE'S OWNER (ALEX STEPKO). 
 * ALEX STEPKO (AXSTEPKO.COM) DISCLAIMS ALL LIABILITY FOR ANY VIOLATIONS OF ACADEMIC 
 * INTEGRITY OR OTHER ETHICAL STANDARDS COMMITTED BY USERS OR VIEWERS OF THIS SOFTWARE.
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "CORDIC.h"

void bulkCordicConvert(hls::stream<FIR_INT_OUTPUT> &cos, hls::stream<FIR_INT_OUTPUT> &sin, float * mag, float *theta, int convertSize)
{
	FIXED_POINT cosFixed = 0.0;
	FIR_INT_OUTPUT cosInt, sinInt = 0;
	FIXED_POINT sinFixed = 0.0;
	FIXED_POINT outMag = 0.0;
	FIXED_POINT outTheta = 0.0;
	// Initialize a bunch of CORDIC's to convert the incoming data:
	BULK_CORDIC: for(int i = 0; i < convertSize; i++)
	{
#pragma HLS UNROLL
		//Read from the stream and convert to fixed point:
		cos.read(cosInt);
		sin.read(sinInt);
		cosFixed = (FIXED_POINT)cosInt;
		sinFixed = (FIXED_POINT)sinInt;

		//Send to CORDIC:
		cordic(cosFixed, sinFixed, &outMag, &outTheta);
		theta[i] = outTheta.to_float();
		mag[i] = outMag.to_float();
#ifdef DEBUG_MODE
		printf("CORDIC.cpp: Magnitude: %f, Phase: %f\n", outMag.to_float(), outTheta.to_float());
#endif
	}
}

/**
 * @brief Rectangular to polar coordinate converter
 *
 * @param cos Rectangular real component input (cos)
 * @param sin Rectangular imaginary component input (sin)
 * @param mag Output vector magnitude
 * @param theta Output vector angle (radians)
 */
void cordic(FIXED_POINT &cos, FIXED_POINT &sin, FIXED_POINT *mag, FIXED_POINT *theta)
{
        FIXED_POINT currentCos = cos;
        FIXED_POINT currentSin = sin;
        FIXED_POINT thetaRotated = 0.0;
        FIXED_POINT ninetyDeg = (FIXED_POINT)M_PI_2;
        FIXED_POINT circleRads = (FIXED_POINT)M_2_PI;
        FIXED_POINT CORDIC_SCALE_FACTOR = 0.60735;

        FIXED_POINT swapTemp = 0.0; // Temporary value used for swapping coordinates to perform initial vector rotation

#ifdef DEBUG_MODE
      printf("Received input %d + j%d\n", cos.to_int(), sin.to_int());
#endif

        // Rotate the vector to within quadrant I or IV, based upon the sin (y) value of the system

        if ((currentSin > 0) & (currentCos < 0)) // Y value is in quadrant II
        {
// Rotate the vector by -90deg:
// This is accomplished by swapping X, Y, and negating the swapped Y.
#ifdef DEBUG_MODE
                printf("QUAD II SWAP\n");
                printf("BEFORE SWAP: X = %f, Y = %f\n", (float)currentCos, (float)currentSin);
#endif
                swapTemp = -1 * currentCos; // Set temp to opposite of X coordinate
                currentCos = currentSin;    // Set Y to X
                currentSin = swapTemp;      // Set X to negated Y
                thetaRotated = ninetyDeg;       

#ifdef DEBUG_MODE
                printf("AFTER SWAP: X = %f, Y = %f\n", (float)currentCos, (float)currentSin);
#endif
        }
        else if ((currentSin < 0) & (currentCos < 0)) // Y value is in quadrant III
        {
// Rotate the vector by +90deg:
// This is accomplished by swapping the X and Y, and negating the swapped X.
#ifdef DEBUG_MODE
                printf("QUAD IV SWAP\n");
                printf("BEFORE SWAP: X = %f, Y = %f\n", (float)currentCos, (float)currentSin);
#endif
                swapTemp = -1 * currentSin; // Set temp to opposite of X coordinate
                currentSin = currentCos;    // Set Y to X
                currentCos = swapTemp;      // Set X to negated Y
                thetaRotated = -1 * ninetyDeg;
#ifdef DEBUG_MODE
                printf("AFTER SWAP: X = %f, Y = %f\n", (float)currentCos, (float)currentSin);
#endif
        }
#ifdef DEBUG_MODE
        else
        {
                printf("No coordinate swap needed.\n");
                thetaRotated = 0.0;
        }
#endif
// ^At this point, the vector is in quadrant I or IV.

// Rotate the vector back to 0deg to find the thetaRotated value
ROTATOR:
        for (int i = 0; i < NUM_ITERATIONS; i++)
        {
#pragma HLS PIPELINE II = 1
                // Compute a shift iteration for the system:
                FIXED_POINT cosShift = currentCos >> i;
                FIXED_POINT sinShift = currentSin >> i;
                // Determine which direction to rotate the vector, and rotate accordingly:
#ifdef DEBUG_MODE
                printf("Prior to rotation: X = %f, Y = %f, theta = %f\n", (float)currentCos, (float)currentSin, (float)thetaRotated);
#endif
                if (currentSin > 0) // Quadrant I, rotate clockwise
                {
#ifdef DEBUG_MODE
                        printf("Clockwise rotation\n");
#endif
                        // Perform a clockwise rotation down to the X-axis
                        currentCos = currentCos + sinShift;
                        currentSin = currentSin - cosShift;
                        // Update the rotated theta
                        thetaRotated = thetaRotated + cordicPhase[i];
                }
                else // if (currentSin < 0) // Quadrant IV, rotate counter-clockwise
                {
#ifdef DEBUG_MODE
                        printf("Counter-clockwise rotation\n");
#endif
                        // Counter-clockwise rotation up to the X-axis
                        currentCos = currentCos - sinShift;
                        currentSin = currentSin + cosShift;
                        // Update the rotated theta
                        thetaRotated = thetaRotated - cordicPhase[i];
                }
#ifdef DEBUG_MODE
                printf("End of iteration\n");
#endif
                // End of iterations, so value can be updated
        }

        // Assign output values
        currentCos = currentCos * cordicGain[NUM_ITERATIONS - 1];
        *mag = currentCos;
        *theta = thetaRotated;
#ifdef DEBUG_MODE
        printf("Magnitude: %f\n", (float)currentCos);
        printf("Angle: %f\n", (float)thetaRotated);
#endif
}
