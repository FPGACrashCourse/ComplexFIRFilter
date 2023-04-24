#ifndef POLAR_FIR_H
#define POLAR_FIR_H
#include <stdio.h>
#include <math.h>
#include <hls_stream.h>

#include "cordic.h"
#include "complexFIR.h"

void polarFir(int *inputReal, int *inputImg, int *filterReal, int *filterImg, float *outputMag, float *outputPhase, int inputLength);


#endif // POLARpFIR_H