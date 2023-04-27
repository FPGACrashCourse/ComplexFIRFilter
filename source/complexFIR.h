/**
 * @file complexFIR.h
 * @author Alex Stepko (axstepko.com)
 * @brief Header file for a 1-d rectangular coordinate FIR filter
 * @version 1.0
 * @date 2023-04-24
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef COMPLEX_FIR_H
#define COMPLEX_FIR_H
#include <stdio.h>
#include <math.h>
#include "hls_stream.h"

#include "datatypes.h"

//#define FIR_DEBUG_MODE //!< Enables rich debugging support within these functions

#define DEBUG_SIZE 25  //!< Constant-width known-values for debug.
#define FILTER_SIZE 25 //!< Constant-width value for HLS optimization

//const int FILTER_SIZE = 25;

static int debugInputReal[DEBUG_SIZE] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
static int debugInputImg[DEBUG_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static int debugCoeffReal[DEBUG_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
static int debugCoeffImg[DEBUG_SIZE] = {25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

void complexFIR(int *inputReal, int *inputImg, hls::stream<FIR_INT_OUTPUT> &outputReal, hls::stream<FIR_INT_OUTPUT> &outputImg, int filterLength);
void computeComplexFIR(FIR_INT_INPUT inputReal, FIR_INT_INPUT inputImg, FIR_INT_INPUT filterReal[FILTER_SIZE], FIR_INT_INPUT filterImg[FILTER_SIZE], FIR_INT_OUTPUT *outputReal, FIR_INT_OUTPUT *outputImg);
#endif // COMPLEX_FIR_H
