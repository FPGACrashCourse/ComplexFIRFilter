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
#ifndef HW_VALIDATION_INCLUDES
#define HW_VALIDATION_INCLUDES

#include <stdio.h>
#include <stdlib.h>

#endif // HW_VALIDATION_INCLUDES



#ifndef HW_VALIDATION_DEPENDENCIES
#define HW_VALIDATION_DEPENDENCIES

#include "complexFIR.h"
#include "CORDIC.h"
#include "polarFIR.h"

#endif // HW_VALIDATION_DEPENDENCIES

#define HW_VALIDATION_DEBUG_MODE //!< Enable this to have verbose debug console output

#define LENGTH 25 //!< Length of the array

int *hwInputReal;  //!< Hardware-accelerated array pointer real components
int *hwInputImg;   //!< Hardware-accelerated array pointer imaginary components
float *hwOutputReal; //!< Hardware-accelerated array pointer real components
float *hwOutputImg;  //!< Hardware-accelerated array pointer imaginary components

int *swInputReal;  //!< Softwae-accelerated array pointer real components
int *swInputImg;   //!< Software-accelerated array pointer imaginary components
float *swOutputReal; //!< Hardware-accelerated array pointer real components
float *swOutputImg;  //!< Hardware-accelerated array pointer imaginary components

void init();
void deinit();
void initializeArray(int **arr, int length);
int compareArray(float *a, float *b, int length);
void copyArray(int *a, int *b, int length);
void complexFIRReference(int *inputReal, int *inputImg, int *kernelReal, int *kernelImg, float *outputReal, float *outputImg, int inputLength, int kernelSize);
void computeComplexFIRReference(int inputReal, int inputImg, int *filterReal, int *filterImg, int filterLength, int *delayLineReal, int *delayLineImg, float *outputReal, float *outputImg);
/**
 * @brief Main application
 */
int main(void)
{
	printf("-----------------  Start validation  ------------------- \n");
    init();
    printf("Arrays initialized.\n");


#ifndef HW_VALIDATION_DEBUG_MODE
    printf("Running filters...\n");
    complexFIR(hwInputReal, hwInputImg, debugCoeffReal, debugCoeffImg, hwOutputReal, hwOutputImg);
    complexFIRReference(swInputReal, swInputImg, debugCoeffReal, debugCoeffImg, swOutputReal, swOutputImg, LENGTH, LENGTH);
    printf("Filters complete.\n");
#else
    printf("Running filters...\n");
    complexFIR(debugInputReal, debugInputImg, debugCoeffReal, debugCoeffImg, hwOutputReal, hwOutputImg);
    complexFIRReference(debugInputReal, debugInputImg, debugCoeffReal, debugCoeffImg, swOutputReal, swOutputImg, LENGTH, LENGTH);
    printf("Filters complete.\n");
#endif

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



    printf("Running CORDIC:\n");
    double cosDouble;
    double sinDouble;

    FIXED_POINT cos = -2.0;
    FIXED_POINT sin = -2.0;
    FIXED_POINT mag = 0.0;
    FIXED_POINT theta = 0.0;
    
    cordic(cos, sin, &mag, &theta);

    cosDouble = cos.to_double();
    sinDouble = sin.to_double();

    printf("Fixed_point MAG = %s, ANG = %s\n", mag.to_string(10), theta.to_string(10));
	printf("---------------  End of validation program  ---------------\n");
    return 0;
}

/**
 * @brief Initializes arrays and copies software array to hardware array
 */
void init()
{
    srand(0);
    // Initialize the real input arrays:
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
    	(*arr)[idx] = rand() % 255;
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
 * @brief Complete processor for a 1-d FIR filter
 * @remark The real and imaginary parts of the input, and kernel, must have the same length.
 *
 * @param inputReal Real part of data input
 * @param inputImg  Imaginary part of data input
 * @param kernelReal Real part of filter coefficents
 * @param kernelImg Pointer to imaginary part of filter coefficents
 * @param outputReal Real part of filter output
 * @param outputImg Imaginary part of filter output
 * @param inputLength Length of the input dataset
 * @param kernelSize Length of the filter coefficent dataset
 */
void complexFIRReference(int *inputReal, int *inputImg, int *kernelReal, int *kernelImg, float *outputReal, float *outputImg, int inputLength, int kernelSize)
{
#ifdef DEBUG_MODE
    printf("Start of hardware FIR...\n");
#endif
    int filterReal[kernelSize]; //!< Filter coefficent buffer (real)
    int filterImg[kernelSize];  //!< Filter coefficent buffer (imaginary)

    int delayLineReal[kernelSize]; //!< Input pipeline delay buffer (real)
    int delayLineImg[kernelSize];  //!< Input pipeline delay buffer (imaginary)
    // ^^ These must remain in the top-level processing function to retain "static" qualities when instantiating multiple filter passes.

    float tempR, tempI; //!< Raw output from a filter pass

LOAD_FILTER:
    for (int i = 0; i < kernelSize; i++)
    {
        filterReal[i] = kernelReal[i];
        filterImg[i] = kernelImg[i];
    }

PIPELINE_DELAY_ARRAY_INIT:
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

COMPUTE:
    for (int k = 0; k < inputLength; k++)
    {
        // Perform a single pass of an input with the coefficents:
        computeComplexFIRReference(inputReal[k], inputImg[k], filterReal, filterImg, kernelSize, delayLineReal, delayLineImg, &tempR, &tempI);
        outputReal[k] = tempR;
        outputImg[k] = tempI;
#ifdef DEBUG_MODE
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
void computeComplexFIRReference(int inputReal, int inputImg, int *filterReal, int *filterImg, int filterLength, int *delayLineReal, int *delayLineImg, float *outputReal, float *outputImg)
{
    float resultReal, resultImg = 0.0; //!< Temporary result hold for the filter pass

PIPELINE_DELAY:
    for (int i = filterLength - 1; i >= 1; i--)
    {
        // Iterate backwards through the array to shift to the right.
        delayLineReal[i] = delayLineReal[i - 1];
        delayLineImg[i] = delayLineImg[i - 1];
    }
    // Add the new input sample to the beginning of the delay line arrays
    delayLineReal[0] = inputReal;
    delayLineImg[0] = inputImg;

FILTER_PASS:
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
