#include <stdio.h>
#include <stdlib.h>

#include "complexFIR.h"

#define DEBUG_MODE

void complexFIR(int *inputReal, int *inputImg, int *kernelReal, int *kernelImg, float *outputReal, float *outputImg, int inputLength, int kernelSize)
{
    printf("Start of hardware FIR...\n");
    int filterReal[kernelSize]; //!< Real filter coefficient buffer
    int filterImg[kernelSize];  //!< Imaginary filter coefficient buffer

    int delayLineReal[kernelSize]; //!< Real delay line buffer
    int delayLineImg[kernelSize];  //!< Imaginary delay line buffer

    float tempR, tempI;

    // Load filter coefficients into a buffer array
    for (int i = 0; i < kernelSize; i++)
    {
        filterReal[i] = kernelReal[i];
        filterImg[i] = kernelImg[i];
    }

    // Initialize the delay line arrays
    for (int j = 0; j < kernelSize; j++)
    {
        delayLineReal[j] = 0;
        delayLineImg[j] = 0;
    }

#ifdef DEBUG_MODE
    printf("Loaded coefficients:\n");
    for (int a = 0; a < kernelSize; a++)
    {
        printf("filterReal[%d] = %d, filterImg[%d] = %d\n", a, filterReal[a], a, filterImg[a]);
    }
#endif

    // Perform complex convolution for each input sample
    for (int k = 0; k < inputLength; k++)
    {
        computeComplexFIR(inputReal[k], inputImg[k], filterReal, filterImg, kernelSize, delayLineReal, delayLineImg, &tempR, &tempI);
        outputReal[k] = tempR;
        outputImg[k] = tempI;

#ifdef DEBUG_MODE
        printf("outReal = %f, outImg = %f\n", tempR, tempI);
#endif
    }
}

void computeComplexFIR(int inputReal, int inputImg, int *filterReal, int *filterImg, int filterLength, int *delayLineReal, int *delayLineImg, float *outputReal, float *outputImg)
{
    float resultReal = 0.0;
    float resultImg = 0.0;

    // Shift the pipeline input array and update the delay line
    for (int i = filterLength - 1; i >= 1; i--)
    {
        delayLineReal[i] = delayLineReal[i - 1];
        delayLineImg[i] = delayLineImg[i - 1];
    }
    delayLineReal[0] = inputReal;
    delayLineImg[0] = inputImg;

    // Compute the 1-d complex convolution for the filter
    for (int j = 0; j < filterLength; j++)
    {
        resultReal += (delayLineReal[j] * filterReal[j]) - (delayLineImg[j] * filterImg[j]);
        resultImg += (delayLineReal[j] * filterImg[j]) + (filterReal[j] * delayLineImg[j]);
    }

    // Send the output
    *outputReal = resultReal;
    *outputImg = resultImg;
}
