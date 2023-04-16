/**
 * @file fpga417_lab4_test.c
 * @author Alex Stepko (axstepko.com), Web Simmara
 * @brief Test application for a simple FIR filter
 * @version 0.1
 * @date 2023-03-22
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef GLOBAL_INCLUDES
#define GLOBAL_INCLUDES
#include <stdio.h>
#include <stdlib.h>
#endif // GLOBAL_INCLUDES

#ifndef DEPENDENCIES
#define DEPENDENCIES
#include "complexFIR.h"
#endif // DEPENDENCIES

#define DEBUG_MODE //!< Enable this to have verbose debug console output

#define LENGTH 25 //!< Length of the array

int *hwInputReal;  //!< Hardware-accelerated array pointer real components
int *hwInputImg;   //!< Hardware-accelerated array pointer imaginary components
float *hwOutputReal; //!< Hardware-accelerated array pointer real components
float *hwOutputImg;  //!< Hardware-accelerated array pointer imaginary components

int *swInputReal;  //!< Softwae-accelerated array pointer real components
int *swInputImg;   //!< Software-accelerated array pointer imaginary components
float *swOutputReal; //!< Hardware-accelerated array pointer real components
float *swOutputImg;  //!< Hardware-accelerated array pointer imaginary components

// int *common_array; //!< Common (validation) array pointer

void init();
void deinit();
void initializeArray(int **arr, int length);
int compareArray(float *a, float *b, int length);
void copyArray(int *a, int *b, int length);
void complexFIRReference(int *inputReal, int *inputImg, int *kernelReal, int *kernelImg, float *outputReal, float *outputImg, int inputLength, int kernelSize);
void computeComplexFIRReference(int inputReal, int inputImg, int *filterReal, int *filterImg, int filterLength, float *outputReal, float *outputImg);

/**
 * @brief Main application
 */
int main(void)
{
	printf("-----------------  Start validation  ------------------- \n");
    init();
#ifdef DEBUG_MODE
    for(int d = 0; d < LENGTH; d++)
    {
    	printf(" HARDWARE input real: %d, input imaginary: %d\n", hwInputReal[d], hwInputImg[d]);
    	printf(" SOFTWARE input real: %d, input imaginary: %d\n", swInputReal[d], swInputImg[d]);
    }
#endif
    printf("Arrays initialized\n");

    printf("Running filters...\n");
#ifdef DEBUG_MODE
    complexFIR(hwInputReal, hwInputImg, debugCoeffReal, debugCoeffImg, hwOutputReal, hwOutputImg, LENGTH, LENGTH);
    //complexFIRReference(swInputReal, swInputImg, debugCoeffReal, debugCoeffImg, swOutputReal, swOutputImg, LENGTH, LENGTH);
#endif
    printf("Filters complete.\n");

    printf("Comparing arrays...\n");
//    if ((compareArray(hwOutputReal, swOutputReal, LENGTH) == 0) || (compareArray(hwOutputImg, swOutputImg, LENGTH) == 0))
//    {
//        printf("TEST FAILED. ELEMENTS DO NOT MATCH");
//    }
//    else
//    {
//        printf("Test passed\n");
//    }

    deinit();
    printf("Arrays freed.\n");
	printf("---------------  End of validation program  ---------------\n");
    return 0;
}

/**
 * @brief Initializes arrays and copies software array to hardware array
 */
void init()
{
    srand(0);
    // Intiialize the real input arrays:
    initializeArray(&hwInputReal, LENGTH);
    initializeArray(&swInputReal, LENGTH);
    copyArray(hwInputReal, swInputReal, LENGTH);

    // Initialize the imaginary input arrays:
    initializeArray(&hwInputImg, LENGTH);
    initializeArray(&swInputImg, LENGTH);
    copyArray(hwInputImg, swInputImg, LENGTH);

    //Initialize output arrays (really, allocate memory and set to zero)
    hwOutputReal = (float *)malloc(sizeof(float) * LENGTH); //!< Allocated space for random number array
    hwOutputImg = (float *)malloc(sizeof(float) * LENGTH); //!< Allocated space for random number array
    swOutputReal = (float *)malloc(sizeof(float) * LENGTH); //!< Allocated space for random number array
    swOutputImg = (float *)malloc(sizeof(float) * LENGTH); //!< Allocated space for random number array
    for(int i = 0; i < LENGTH; i++)
    {
    	hwOutputReal[i] = 0.0;
    	hwOutputImg[i] = 0.0;
    	swOutputReal[i] = 0.0;
    	swOutputImg[i] = 0.0;
    }
}

/**
 * @brief Frees space in the created arrays to avoid a memory leakage.
 */
void deinit()
{
    free(hwInputReal);
    free(hwInputImg);
    free(swInputReal);
    free(swInputImg);
}

/**
 * @brief Allocates memory and initializes array to a set of random numbers
 *
 * @param arr Pointer to the input array
 * @param length Length of the input array
 */
void initializeArray(int **arr, int length)
{
    *arr = (int *)malloc(sizeof(int) * length); //!< Allocated space for random number array
    for (int idx = 0; idx < length; ++idx)
    {
    	//(*arr)[idx] = rand() % 255;
    	(*arr)[idx] = idx;

    }

}

/**
 * @brief Compares two arrays searching for a different value
 *
 * @param a Array 1 to be compared
 * @param b Array 2 to be compared
 * @param length Length of both arrays to be compared
 * @return int return status of the function (0 = ok, 1 = fail)
 */
int compareArray(float *a, float *b, int length)
{

    for (int i = 0; i < length; ++i)
        if (a[i] != b[i])
            return 1;
    return 0;
}

/**
 * @brief Copies array b to a
 *
 * @param a Pointer to an array to be copied into
 * @param b Pointer to an array to be copied from
 * @param length Length of the arrays.
 */
void copyArray(int *a, int *b, int length)
{
    for (int i = 0; i < length; ++i)
        a[i] = b[i];
}

//////////////////////// REFERENCE FILTER DESIGNS //////////////////////
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
void complexFIRReference(int *inputReal, int *inputImg, int *kernelReal, int *kernelImg, float *outputReal, float *outputImg, int inputLength, int kernelSize)
{

	int filterReal[kernelSize]; //!< Real filter coefficent buffer
	int filterImg[kernelSize];	//!< Imaginary filter coefficent buffer

	float tempR, tempI = 0;

	// Load in filter coefficents to a buffer array
	for (int i = 0; i < kernelSize; i++)
	{
		filterReal[i] = kernelReal[i];
		filterImg[i] = kernelImg[i];
	}

	// Pass input to the filter instances
	for (int j = 0; j < kernelSize; j++)
	{
		//computeComplexFIR(inputReal[j], inputImg[j], filterReal, filterImg, kernelSize, &tempR, &tempI);
		outputReal[j] = tempR;
		outputImg[j] = tempI;
#ifdef DEBUG_MODE
		printf("Real: %f, imaginary: %f", tempR, tempI);
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
void computeComplexFIRReference(int inputReal, int inputImg, int *filterReal, int *filterImg, int filterLength, float *outputReal, float *outputImg)
{
	int * delayLineReal;
	int * delayLineImg;
	float resultReal, resultImg = 0.0;

	// Shift the pipeline input array
	for (int i = filterLength - 1; i > 0; i--)
	{
		delayLineReal[i] = delayLineReal[i - 1];
		delayLineImg[i] = delayLineImg[i - 1];
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
