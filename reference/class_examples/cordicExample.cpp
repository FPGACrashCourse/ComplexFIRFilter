// Rotates a vector from 0 degrees to a desired angle

#include "cordicExample.h"

const int NUM_ITERATIONS = 32; // Number of iterations to run the CORDIC for. Determines the precision of the system at the cost of system latency.
//Limited to 64 iterations, as that's all we have in the phase gains




//Create the LUT for the cordic calculations in the array:
//cordic_phase[i-1] is the rotator angle at iteration I
const FIXED_POINT cordicPhase[64]={0.78539816339744828000,0.46364760900080609000,0.24497866312686414000,0.12435499454676144000,0.06241880999595735000,0.03123983343026827700,0.01562372862047683100,0.00781234106010111110,0.00390623013196697180,0.00195312251647881880,0.00097656218955931946,0.00048828121119489829,0.00024414062014936177,0.00012207031189367021,0.00006103515617420877,0.00003051757811552610,0.00001525878906131576,0.00000762939453110197,0.00000381469726560650,0.00000190734863281019,0.00000095367431640596,0.00000047683715820309,0.00000023841857910156,0.00000011920928955078,0.00000005960464477539,0.00000002980232238770,0.00000001490116119385,0.00000000745058059692,0.00000000372529029846,0.00000000186264514923,0.00000000093132257462,0.00000000046566128731,0.00000000023283064365,0.00000000011641532183,0.00000000005820766091,0.00000000002910383046,0.00000000001455191523,0.00000000000727595761,0.00000000000363797881,0.00000000000181898940,0.00000000000090949470,0.00000000000045474735,0.00000000000022737368,0.00000000000011368684,0.00000000000005684342,0.00000000000002842171,0.00000000000001421085,0.00000000000000710543,0.00000000000000355271,0.00000000000000177636,0.00000000000000088818,0.00000000000000044409,0.00000000000000022204,0.00000000000000011102,0.00000000000000005551,0.00000000000000002776,0.00000000000000001388,0.00000000000000000694,0.00000000000000000347,0.00000000000000000173,0.00000000000000000087,0.00000000000000000043,0.00000000000000000022,0.00000000000000000011};


void cordicRotator(FIXED_POINT theta, FIXED_POINT *sin, FIXED_POINT *cos)
{
	FIXED_POINT currentCos; //x values, should be 1 at the start of the algorithm
	FIXED_POINT currentSin; //y values, should be 0 at the start of the algorithm
	FIXED_POINT currentTheta = theta; // Current theta for the algorithm. Represents remaining angle to rotate. Initially set to the target angle

	//Pre-scale the values (doesn't matter, can do it at beginning or the end)
	currentCos = 0.60735; //Sets the current cos to 1/CORDIC_GAIN = 1/1.6xxx to pre-apply the scaling factor
	currentSin = 0.0; //Sets the current sin to 0, which is 0deg on the unit circle



	/**
	 * Bring any theta angle >1/2pi or <0 back to within 0 -> 1/2pi.
	 *
	 * Greater than 2pi, divide by 2pi, and the remainder is the working angle
	 *
	 * */

	for(int i = 0; i < NUM_ITERATIONS; i++)
	{
		//Given the cordic matrix, these results are equivalent to multiplying/dividing by 2^(-i), given the fixed point nature of the system
		FIXED_POINT cosShift = currentCos >> i;
		FIXED_POINT sinShift = currentSin >> i;

		//Each iteration needs to compare the amount we've already rotated, and see if that matches the target angle desired.
		// That tells us how we should be rotating the angle via +/-
		if(currentTheta > 0)
		{
			// Rotate the vector counter-clockwise, given our starting vector starts at (1, 0) (x,y):
			// This is accomplished by the matrix multiplication/bit-shifting, but is really algebra after the shift has been accomplished.
			currentCos = currentCos - sinShift;
			currentSin = currentSin + cosShift;


			// Afterwards, update the currentTheta by subtracting the amount shifted (angle rotated) to the value.
			currentTheta = currentTheta - cordicPhase[i];
		}
		else //Current theta <= 0, we have an overshoot
		{
			// Rotate the vector clockwise:
			currentCos = currentCos + sinShift;
			currentSin = currentSin - cosShift;

			//Update currentTheta by adding the amount shifted
			currentTheta = currentTheta + cordicPhase[i];
		}

		//Set the final output values
		*sin = currentSin;
		*cos = currentCos;
	}
}
























