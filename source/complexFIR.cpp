/**
 * @file complexFIR.c
 * @author Alex Stepko (axstepko.com)
 * @brief Hardware-accelerated 1-d complex FIR filter
 * @version 0.1
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
void complexFIR(int *inputReal, int *inputImg, int *kernelReal, int *kernelImg, float *outputReal, float *outputImg)
{
#ifdef FIR_DEBUG_MODE
    printf("Start of hardware FIR...\n");
#endif
    int filterReal[FILTER_SIZE]; //!< Filter coefficent buffer (real)
    int filterImg[FILTER_SIZE];  //!< Filter coefficent buffer (imaginary)

    float tempR, tempI; //!< Raw output from a filter pass

LOAD_FILTER:
    for (int i = 0; i < FILTER_SIZE; i++)
    {
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
        // Perform a single pass of an input with the coefficents:
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
 * @param filterReal Real part of filter coefficents
 * @param filterImg Imaginary part of filter coefficents
 * @param filterLength Length of the filter
 * @param delayLineReal Real part of pipleine delay component
 * @param delayLineImg Imaginary part of pipeline delay component
 * @param outputReal Real part of discrete output
 * @param outputImg Imaginary part of discrete output
 */
void computeComplexFIR(int inputReal, int inputImg, int *filterReal, int *filterImg, float *outputReal, float *outputImg)
{
    float resultReal, resultImg = 0.0; //!< Temporary result hold for the filter pass

    static int delayLineReal[FILTER_SIZE] = {}; //!< Input pipeline delay buffer (real)
    static int delayLineImg[FILTER_SIZE] = {};  //!< Input pipeline delay buffer (imaginary

PIPELINE_DELAY:
    for (int i = FILTER_SIZE - 1; i >= 1; i--)
    {
        // Iterate backwards through the array to shift to the right.
        delayLineReal[i] = delayLineReal[i - 1];
        delayLineImg[i] = delayLineImg[i - 1];
    }
    // Add the new input sample to the beginning of the delay line arrays
    delayLineReal[0] = inputReal;
    delayLineImg[0] = inputImg;

FILTER_PASS:
    for (int j = 0; j < FILTER_SIZE; j++)
    {
        // Calculate the real and imaginary parts of the convolution
        // output using the filter coefficients and the delay line.
        resultReal += (delayLineReal[j] * filterReal[j]) - (delayLineImg[j] * filterImg[j]);
        resultImg += (delayLineReal[j] * filterImg[j]) + (filterReal[j] * delayLineImg[j]);
    }

    // Send the output
    // Update the output pointers with the computed real and imaginary parts
    *outputReal = resultReal;
    *outputImg = resultImg;
}