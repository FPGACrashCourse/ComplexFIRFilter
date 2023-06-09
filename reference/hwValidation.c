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
#include "fpga417_lab4.h"
#endif // DEPENDENCIES

#define LENGTH 20 //!< Length of the array
#define TAPS 3    //!< Order of the filter

int *hw_array;     //!< Hardware-accelerated array pointer
int *sw_array;     //!< Software-accelerated array pointer
int *common_array; //!< Common (validation) array pointer

void init();
void deinit();
void initializeArray(int **array, int length);
int compareArray(int *a, int *b, int length);
void copyArray(int *a, int *b, int length);
void doFIRreference(int *data, int *taps);
void swFIR(int input, int filter[TAPS], int *output);

/**
 * @brief Main application
 */
int main(void)
{
    int filter[3] = {3, 5, 3};
    init();
    doFIRreference(sw_array, filter);
    fpga417_fir(hw_array, filter, 10);

    if (compareArray(hw_array, sw_array, LENGTH) == 1)
        printf("HW does not match SW\n");
    else
        printf("HW and SW match\n");

    deinit();
    return 0;
}

/**
 * @brief Initializes arrays and copies software array to hardware array
 */
void init()
{
    srand(0);
    initializeArray(&hw_array, LENGTH);
    initializeArray(&sw_array, LENGTH);
    initializeArray(&common_array, LENGTH);
    copyArray(hw_array, sw_array, LENGTH);
}

/**
 * @brief Frees space in the created arrays to avoid a memory leakage.
 */
void deinit()
{
    free(hw_array);
    free(sw_array);
    free(common_array);
}

/**
 * @brief Initializes array to a set of random numbers
 *
 * @param arr Pointer to the input array
 * @param length Length of the input array
 */
void initializeArray(int **arr, int length)
{
    *arr = (int *)malloc(sizeof(int) * length); //!< Allocated space for random number array
    for (int idx = 0; idx < length; ++idx)
        (*arr)[idx] = rand() % 255;
}

/**
 * @brief Compares two arrays searching for a different value
 *
 * @param a Array 1 to be compared
 * @param b Array 2 to be compared
 * @param length Length of both arrays to be compared
 * @return int return status of the function (0 = ok, 1 = fail)
 */
int compareArray(int *a, int *b, int length)
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

/**
 * @brief Computes a 1-d FIR filter
 *
 * @param data Pointer to the input and output dataset
 * @param filter  Pointer to the filter coefficients
 */
void doFIRreference(int *data, int *filter)
{
    int filter_coeff[TAPS];
    int temp;
    // Load in filter coefficients
    for (int i = 0; i < TAPS; i++)
    {
        filter_coeff[i] = filter[i];
    }

    for (int j = 0; j < LENGTH; j++)
    {
        swFIR(data[j], filter_coeff, &temp);
        data[j] = temp;
        printf("%d \n", temp);
    }
}

/**
 * @brief 1-cycle latency FIR filter computation
 *
 * @param input Input element
 * @param filter Filter data
 * @param output Output element
 */
void swFIR(int input, int filter[TAPS], int *output)
{
    static int delay_line[TAPS] = {};
    int result = 0;
    for (int i = TAPS; i > 0; i--) // Shift "pipeline" input array
    {
        delay_line[i] = delay_line[i - 1];
    }
    delay_line[0] = input;

    for (int j = 0; j < TAPS; j++) // Compute filter value
    {
        result += delay_line[j] * filter[j];
    }
    *output = result; // Send output
}
