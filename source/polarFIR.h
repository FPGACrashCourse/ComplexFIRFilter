#ifndef POLAR_FIR_H
#define POLAR_FIR_H
#include <stdio.h>
#include <math.h>
#include "hls_stream.h"

#include "CORDIC.h"
#include "complexFIR.h"
#include "datatypes.h"

//#define POLAR_FIR_DEBUG_MODE

void polarFir(int *inputReal, int *inputImg, float *outputMag, float *outputPhase, int inputLength);

#endif // POLAR_FIR_H
