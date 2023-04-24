/**
 * @file complexFIR.c
 * @author Alex Stepko (axstepko.com)
 * @brief Hardware-accelerated 1-d rectangular FIR filter
 * @remark Outputs values in rectangular float form
 * @version 1.0
 * @date 2023-04-16
 *
 * @copyright Copyright (c) 2023
 */
#ifndef INCLUDES
#include <stdio.h>
#include <stdlib.h>

#endif // INCLUDES

#ifndef DEPENDENCIES
#define DEPENDENCIES
#include "complexFIR.h"

#endif
/**
 * @brief Complete processor for a 1-d FIR filter
 * @remark The real and imaginary parts of the input, and kernel, must have the same length.
 *
 * @param inputReal Real part of data input
 * @param inputImg  Imaginary part of data input
 * @param kernelReal Real part of filter coefficents
 * @param kernelImg Pointer to imaginary part of filter coefficents
 * @param outputReal Real part of filter output
 * @param outputImg Imaginary part of filter output
 */
void complexFIR(int inputReal[FILTER_SIZE], int inputImg[FILTER_SIZE], int kernelReal[FILTER_SIZE], int kernelImg[FILTER_SIZE], float outputReal[FILTER_SIZE], float outputImg[FILTER_SIZE])
{

#pragma HLS ARRAY_PARTITION variable = inputReal type = complete
#pragma HLS ARRAY_PARTITION variable = inputImg type = complete
#pragma HLS ARRAY_PARTITION variable = kernelReal type = complete
#pragma HLS ARRAY_PARTITION variable = kernelImg type = complete
#pragma HLS ARRAY_PARTITION variable = outputReal type = complete
#pragma HLS ARRAY_PARTITION variable = outputImg type = complete

#ifdef FIR_DEBUG_MODE
    printf("Start of hardware FIR...\n");
#endif
    int filterReal[FILTER_SIZE]; //!< Filter coefficient buffer (real)
    int filterImg[FILTER_SIZE];  //!< Filter coefficient buffer (imaginary)

    float tempR, tempI; //!< Raw output from a filter pass

LOAD_FILTER:
    for (int i = 0; i < FILTER_SIZE; i++)
    {
#pragma HLS UNROLL
        filterReal[i] = kernelReal[i];
        filterImg[i] = kernelImg[i];
    }

#ifdef FIR_DEBUG_MODE
    printf("Loaded coefficients:\n");
    for (int a = 0; a < FILTER_SIZE; a++)
    {
        printf("filterReal[%d] = %d, filterImg[%d] = %d\n", a, filterReal[a], a, filterImg[a]);
    }
#endif

COMPUTE:
    for (int k = 0; k < FILTER_SIZE; k++)
    {
#pragma HLS PIPELINE
        // Perform a single pass of an input with the coefficients:
        computeComplexFIR(inputReal[k], inputImg[k], filterReal, filterImg, &tempR, &tempI);
        outputReal[k] = tempR;
        outputImg[k] = tempI;
#ifdef FIR_DEBUG_MODE
        printf("outReal = %f, outImg = %f\n", tempR, tempI);
#endif
    }
}

/**
 * @brief Performs a FIR on a single element of a complex datapoint
 *
 * @param inputReal Real part of input sample
 * @param inputImg Imaginary part of input sample
 * @param filterReal Real part of filter coefficients
 * @param filterImg Imaginary part of filter coefficients
 * @param filterLength Length of the filter
 * @param delayLineReal Real part of pipeline delay component
 * @param delayLineImg Imaginary part of pipeline delay component
 * @param outputReal Real part of discrete output
 * @param outputImg Imaginary part of discrete output
 */
void computeComplexFIR(int inputReal, int inputImg, int filterReal[FILTER_SIZE], int filterImg[FILTER_SIZE], float *outputReal, float *outputImg)
{
#pragma HLS PIPELINE
    float resultReal[FILTER_SIZE], resultImg[FILTER_SIZE] = {}; //!< Temporary result hold for the filter pass


    static int delayLineReal[FILTER_SIZE] = {}; //!< Input pipeline delay buffer (real)
    static int delayLineImg[FILTER_SIZE] = {};  //!< Input pipeline delay buffer (imaginary

#pragma HLS ARRAY_PARTITION variable = delayLineReal type = complete
#pragma HLS ARRAY_PARTITION variable = delayLineImg type = complete

PIPELINE_DELAY:
    for (int i = FILTER_SIZE - 1; i >= 1; i--)
    {
#pragma HLS UNROLL
        // Iterate backwards through the array to shift to the right.
        delayLineReal[i] = delayLineReal[i - 1];
        delayLineImg[i] = delayLineImg[i - 1];
    }
    // Add the new input sample to the beginning of the delay line arrays
    delayLineReal[0] = inputReal;
    delayLineImg[0] = inputImg;

    // Compute the filter output for each tap simultaneously
FILTER_TAPS:
    for (int j = 0; j < FILTER_SIZE; j++)
    {
#pragma HLS UNROLL
        resultReal[j] = (delayLineReal[j] * filterReal[j]) - (delayLineImg[j] * filterImg[j]);
        resultImg[j] = (delayLineReal[j] * filterImg[j]) + (filterReal[j] * delayLineImg[j]);
    }

    // Sum up the results and send the output
SUM_RESULTS:
    for (int k = 1; k < FILTER_SIZE; k++)
    {
#pragma HLS UNROLL
        resultReal[0] += resultReal[k];
        resultImg[0] += resultImg[k];
    }
    *outputReal = resultReal[0];
    *outputImg = resultImg[0];
}
