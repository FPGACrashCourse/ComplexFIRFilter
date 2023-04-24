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

#define FIR_DEBUG_MODE //!< Enables rich debugging support within these functions

#define DEBUG_SIZE 25 //!< Constant-width known-values for debug.
#define FILTER_SIZE 25 //!< Constant-width value for HLS optimization

static int debugInputReal[DEBUG_SIZE] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
static int debugInputImg[DEBUG_SIZE] =  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static int debugCoeffReal[DEBUG_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
static int debugCoeffImg[DEBUG_SIZE] = {25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};


void complexFIR(int inputReal[FILTER_SIZE], int inputImg[FILTER_SIZE], int kernelReal[FILTER_SIZE], int kernelImg[FILTER_SIZE], float outputReal[FILTER_SIZE], float outputImg[FILTER_SIZE]);
void computeComplexFIR(int inputReal, int inputImg, int filterReal[FILTER_SIZE], int filterImg[FILTER_SIZE], float *outputReal, float *outputImg);



#endif // COMPLEX_FIR_H
