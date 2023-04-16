#include <stdio.h>
#include <stdlib.h>

#include "complexFIR.h"

#define DEBUG_MODE

// Complex FIR filter function
// inputReal: real part of input signal
// inputImg: imaginary part of input signal
// kernelReal: real part of filter coefficients
// kernelImg: imaginary part of filter coefficients
// outputReal: real part of the output signal
// outputImg: imaginary part of the output signal
// inputLength: length of the input signal
// kernelSize: size of the FIR filter kernel
void complexFIR(int *inputReal, int *inputImg, int *kernelReal, int *kernelImg, float *outputReal, float *outputImg, int inputLength, int kernelSize)
{
    printf("Start of hardware FIR...\n");
    
    // Real and imaginary filter coefficient buffers
    int filterReal[kernelSize];
    int filterImg[kernelSize];

    // Real and imaginary delay line buffers
    int delayLineReal[kernelSize];
    int delayLineImg[kernelSize];

    float tempR, tempI;

    // Load filter coefficients into buffer arrays
    // This loop iterates over the kernel coefficients and copies them
    // into local arrays for further processing.
    for (int i = 0; i < kernelSize; i++)
    {
        filterReal[i] = kernelReal[i];
        filterImg[i] = kernelImg[i];
    }

    // Initialize the delay line arrays
    // This loop iterates over the delay line arrays and sets each
    // element to zero.
    for (int j = 0; j < kernelSize; j++)
    {
        delayLineReal[j] = 0;
        delayLineImg[j] = 0;
    }

    // DEBUG: Print loaded coefficients
#ifdef DEBUG_MODE
    printf("Loaded coefficients:\n");
    for (int a = 0; a < kernelSize; a++)
    {
        printf("filterReal[%d] = %d, filterImg[%d] = %d\n", a, filterReal[a], a, filterImg[a]);
    }
#endif

    // Perform complex convolution for each input sample
    // This loop iterates over the input samples and calls the
    // computeComplexFIR function to compute the complex convolution
    // for each sample.
    for (int k = 0; k < inputLength; k++)
    {
        computeComplexFIR(inputReal[k], inputImg[k], filterReal, filterImg, kernelSize, delayLineReal, delayLineImg, &tempR, &tempI);
        outputReal[k] = tempR;
        outputImg[k] = tempI;

        // DEBUG: Print output for each sample
#ifdef DEBUG_MODE
        printf("outReal = %f, outImg = %f\n", tempR, tempI);
#endif
    }
}

// Compute complex FIR function
// inputReal: real part of input sample
// inputImg: imaginary part of input sample
// filterReal: real part of filter coefficients
// filterImg: imaginary part of filter coefficients
// filterLength: length of the filter
// delayLineReal: real part of delay line
// delayLineImg: imaginary part of delay line
// outputReal: pointer to real part of output sample
// outputImg: pointer to imaginary part of output sample
void computeComplexFIR(int inputReal, int inputImg, int *filterReal, int *filterImg, int filterLength, int *delayLineReal, int *delayLineImg, float *outputReal, float *
outputImg)
{
    float resultReal = 0.0;
    float resultImg = 0.0;

    // Shift the pipeline input array and update the delay line
    // This loop iterates backwards through the delay line arrays,
    // shifting each element to the next position.
    for (int i = filterLength - 1; i >= 1; i--)
    {
        delayLineReal[i] = delayLineReal[i - 1];
        delayLineImg[i] = delayLineImg[i - 1];
    }
    // Add the new input sample to the beginning of the delay line arrays
    delayLineReal[0] = inputReal;
    delayLineImg[0] = inputImg;

    // Compute the 1-d complex convolution for the filter
    // This loop iterates over the filter coefficients and delay line
    // arrays, performing the complex multiplication and accumulation
    // to compute the convolution output.
    for (int j = 0; j < filterLength; j++)
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
