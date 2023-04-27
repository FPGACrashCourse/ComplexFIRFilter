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
void complexFIR(int *inputReal, int *inputImg, hls::stream<FIR_INT_OUTPUT> &outputReal, hls::stream<FIR_INT_OUTPUT> &outputImg, int filterLength)
{

//Partition the arrays accordingly:
#pragma HLS ARRAY_PARTITION variable = outputReal type = complete
#pragma HLS ARRAY_PARTITION variable = outputImg type = complete

#ifdef FIR_DEBUG_MODE
    printf("Start of hardware FIR...\n");
#endif

	FIR_INT_INPUT kernelImg[FILTER_SIZE]; //!< Imaginary filter coefficient storage location
    FIR_INT_INPUT kernelReal[FILTER_SIZE]; //!< Real filter coefficient storage location

#pragma HLS ARRAY_PARTITION variable=kernelReal type=complete
#pragma HLS ARRAY_PARTITION variable=kernelImg type=complete

    // Initialize kernel with filter coefficients, using data from the first 0 -> FILTER_SIZE-1 spaces
#ifdef POLAR_FIR_DEBUG_MODE
    printf("FILTER:\n");
#endif
    FILTER_INIT:for (int i = 0; i < FILTER_SIZE; i++)
    {
#pragma HLS UNROLL
        kernelReal[i] = FIR_INT_INPUT(inputReal[i]);
        kernelImg[i] = FIR_INT_INPUT(inputImg[i]);
    }

#ifdef FIR_DEBUG_MODE
    printf("complexFIR: Loaded coefficients:\n");
    for (int a = 0; a < FILTER_SIZE; a++)
    {
        printf("complexFIR: kernel [%d] = %d + j%d\n", a, kernelReal[a].to_int(), kernelImg[a].to_int());
    }
    printf("complexFIR: Loaded inputs:\n");
    for(int b = 0; b < filterLength; b++)
    {
    	printf("complexFIR: input[%d] = %d + j%d\n", b, inputReal[FILTER_SIZE + b], inputImg[FILTER_SIZE + b]);
    }
#endif

	FIR_INT_OUTPUT tempR = 0;
	FIR_INT_OUTPUT tempI = 0;

COMPUTE:
    for (int k = 0; k < filterLength; k++)
    {
#pragma HLS UNROLL factor = 2
    	FIR_INT_INPUT inTempReal = FIR_INT_INPUT(inputReal[FILTER_SIZE + k]);
    	FIR_INT_INPUT inTempImg = FIR_INT_INPUT(inputImg[FILTER_SIZE + k]);

        // Perform a single pass of an input with the coefficients:
        computeComplexFIR(inTempReal, inTempImg, kernelReal, kernelImg, &tempR, &tempI);
#ifdef FIR_DEBUG_MODE
		printf("complexFIR: result = %d + j%d\n", tempR.to_int(), tempI.to_int());
#endif
        outputReal.write(tempR);
        outputImg.write(tempI);
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
void computeComplexFIR(FIR_INT_INPUT inputReal, FIR_INT_INPUT inputImg, FIR_INT_INPUT filterReal[FILTER_SIZE], FIR_INT_INPUT filterImg[FILTER_SIZE], FIR_INT_OUTPUT *outputReal, FIR_INT_OUTPUT *outputImg)
{
//#pragma HLS PIPELINE
	FIR_INT_OUTPUT resultReal = 0;
	FIR_INT_OUTPUT resultImg = 0; //!< Temporary result hold for the filter pass

    static FIR_INT_INPUT delayLineReal[FILTER_SIZE] = {}; //!< Input pipeline delay buffer (real)
    static FIR_INT_INPUT delayLineImg[FILTER_SIZE] = {};  //!< Input pipeline delay buffer (imaginary

#pragma HLS ARRAY_PARTITION variable = delayLineReal type = complete
#pragma HLS ARRAY_PARTITION variable = delayLineImg type = complete

#ifdef FIR_DEBUG_MODE
    printf("computeComplexFIR: Recieved input %d + j%d\n", inputReal.to_int(), inputImg.to_int());
#endif

PIPELINE_DELAY:
    for (int i = FILTER_SIZE - 1; i >= 1; i--)
    {
#pragma HLS UNROLL
        // Iterate backwards through the array to shift to the right.
        delayLineReal[i] = delayLineReal[i - 1];
        delayLineImg[i] = delayLineImg[i - 1];
#ifdef FIR_DEBUG_MODE
        printf("computeComplexFIR: delay[%d] = %d + %di\n", i, delayLineReal[i].to_int(), delayLineImg[i].to_int());
#endif
    }
    // Add the new input sample to the beginning of the delay line arrays
    delayLineReal[0] = inputReal;
    delayLineImg[0] = inputImg;

    // Compute a pass of the filter
FILTER_TAPS:
    for (int j = 0; j < FILTER_SIZE; j++)
    {
#pragma HLS PIPELINE
        resultReal += (delayLineReal[j] * filterReal[j]) - (delayLineImg[j] * filterImg[j]);
        resultImg += (delayLineReal[j] * filterImg[j]) + (filterReal[j] * delayLineImg[j]);
    }

    //Send outputs of the filter pass
    *outputReal = resultReal;
    *outputImg = resultImg;
}
