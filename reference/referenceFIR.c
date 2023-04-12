/**
 * @file complexFIR.c
 * @author Alex Stepko (axstepko.com)
 * @brief Hardware implementation of a FIR filter using Vitis HLS
 * @version 0.1
 * @date 2023-034-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef GLOBAL_INCLUDES
#define GLOBAL_INCLUDES
#include <stdio.h>

#endif // GLOBAL_INCLUDES

#ifndef DEPENDENCIES
#define DEPENDENCIES

#include "complexFIR.h"

#endif // DEPENDENCIES

#define LENGTH 20 //!< Length of the data incoming to the filter
#define TAPS 3	  //!< Depth of the filter coefficients

/**
 * @brief Computes a 1-d FIR filter
 *
 * @param data Pointer to the input and output dataset
 * @param filter  Pointer to the filter coefficients
 * @param length Dummy variable, unused.
 */
void fpga417_fir(int* data, int* filter, int length)
{
#pragma HLS INTERFACE mode=m_axi port=data offset=slave
#pragma HLS INTERFACE mode=m_axi port=filter offset=slave
#pragma HLS INTERFACE mode=s_axilite port=return
#pragma HLS INTERFACE mode=s_axilite port=length

int length_n=length; //!< Dummy variable for the interface setup.


	int filter_coeff[TAPS];
	
	int temp;
	// Load in filter coefficients
	for (int i = 0; i < TAPS; i++)
	{
		filter_coeff[i] = filter[i];
	}

	for (int j = 0; j < LENGTH; j++)
	{
		fir(data[j], filter_coeff, &temp);
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
void fir(int input, int filter[TAPS], int *output)
{
	static int delay_line[TAPS] = {};
	int result = 0;

	for (int i = TAPS-1; i > 0; i--) // Shift "pipeline" input array
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
