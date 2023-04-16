
#include <stdio.h>

#include "complexFIR.h"

/**
 * @brief
 *
 * @param inputReal
 * @param inputImg
 * @param kernelReal
 * @param kernelImg
 * @param outputMag
 * @param outputReal
 * @param inputLength
 * @param kernelSize
 */
void complexFIR(int *inputReal, int *inputImg, int *kernelReal, int *kernelImg, float *outputReal, float *outputImg, int inputLength, int kernelSize)
{

	printf("Start of hardware FIR...\n");
	int filterReal[kernelSize]; //!< Real filter coefficent buffer
	int filterImg[kernelSize];	//!< Imaginary filter coefficent buffer

	float tempR, tempI = 0.0;

	// Load in filter coefficents to a buffer array
	for (int i = 0; i < kernelSize; i++)
	{
		filterReal[i] = kernelReal[i];
		filterImg[i] = kernelImg[i];
	}
#ifdef DEBUG_MODE
	printf("Loaded coefficents\n");
	for(int a = 0; a < kernelSize; a++)
	{
		printf("filterReal[%d] = %d, filterImg[%d] = %d\n", a, filterReal[a], a, filterImg[a]);
	}
#endif

	// Pass input to the filter instances

	for (int j = 0; j < kernelSize; j++)
	{
		//computeComplexFIR(inputReal[j], inputImg[j], filterReal, filterImg, kernelSize, &tempR, &tempI);
		computeComplexFIR(inputReal[j], inputImg[j], filterReal, filterImg, kernelSize, &tempR, &tempI);
		outputReal[j] = tempR;
		outputImg[j] = tempI;
#ifdef DEBUG_MODE
		printf("Output Real: %f, imaginary: %f\n", tempR, tempI);
#endif
	}
}

/**
 * @brief Performs a 1-d convolution for a complex input and filter set.
 *
 * @param inputReal
 * @param inputImg
 * @param filterReal
 * @param filterImg
 * @param filterLength
 * @param outputReal
 * @param outputImg
 */
void computeComplexFIR(int inputReal, int inputImg, int *filterReal, int *filterImg, int filterLength, float *outputReal, float *outputImg)
{
	int *delayLineReal;
	int *delayLineImg;
	float resultReal, resultImg = 0.0;
	printf("Starting the hardware convolution:\n");
	// Shift the pipeline input array
	for (int i = filterLength - 1; i > 0; i--)
	{
		delayLineReal[i] = delayLineReal[i - 1];
		delayLineImg[i] = delayLineImg[i - 1];
		printf("delaylineReal = %d, delayLineImg = %d", delayLineReal[i], delayLineImg[i]);

	}
	delayLineReal[i] = inputReal;
	delayLineImg[i] = inputImg;

	// Compute the 1-d complex convolution for the filter:
	for (int j = 0; j < filterLength; j++)
	{
		resultReal += (inputReal * filterReal[j]) - (inputImg * filterImg[j]);
		resultImg += (inputReal * filterImg[j]) + (filterReal[j] * inputImg);
	}

	// Send the output:
	*outputReal = resultReal;
	*outputImg = resultImg;
}
