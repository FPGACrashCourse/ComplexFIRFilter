#ifndef INCLUDES
#define INCLUDES
#include <stdio.h>
#include <math.h>

#endif // Includes

#ifndef DEFINES
#define DEFINES

//#define DEBUG_MODE

#define DEBUG_SIZE 25

static int debugInputReal[DEBUG_SIZE] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
static int debugInputImg[DEBUG_SIZE] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

static int debugCoeffReal[DEBUG_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
static int debugCoeffImg[DEBUG_SIZE] = {25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};


void complexFIR(int *inputReal, int *inputImg, int *kernelReal, int *kernelImg, float *outputReal, float *outputImg, int inputLength, int kernelSize);
void computeComplexFIR(int inputReal, int inputImg, int *filterReal, int *filterImg, int filterLength, int *delayLineReal, int *delayLineImg, float *outputReal, float *outputImg);

#endif // Defines
