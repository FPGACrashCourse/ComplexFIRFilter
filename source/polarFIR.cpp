#ifndef POLAR_FIR_INCLUDES
#define POLAR_FIR_INCLUDES
#include <stdio.h>
#include <math.h>
#include <ap_fixed.h>

#include "polarFIR.h"

#endif // POLAR_FIR_INCLUDES

/**
 * @brief Computes a 1-d FIR complex FIR filter and displays the result in polar coordinates.
 * 
 * @param inputReal Real inputs, first 25 elements are the filter
 * @param inputImg Imaginary inputs, first 25 elements are the filter
 * @param outputMag Output magnitude
 * @param outputPhase Output phase
 * @param inputLength Length of the input dataset to compute
 */
void polarFir(int *inputReal, int *inputImg, float *outputMag, float *outputPhase, int inputLength)
{

// Define the system's AXI interface:
// Data inputs:
#pragma HLS INTERFACE mode = m_axi port = inputReal offset = slave bundle=realIn
#pragma HLS INTERFACE mode = m_axi port = inputImg offset = slave bundle=imgIn

// Polar outputs:
#pragma HLS INTERFACE mode = m_axi port = outputMag offset = slave
#pragma HLS INTERFACE mode = m_axi port = outputPhase offset = slave

#pragma HLS INTERFACE mode = s_axilite port = inputLength
#pragma HLS INTERFACE mode = s_axilite port = return


#ifdef POLAR_FIR_DEBUG_MODE
    printf("INPUTS:\n");
    for(int j = 0; j < inputLength; j++)
    {
    	printf("POLARFIR: inputReal[%d] = %d, inputImg[%d] = %d\n", j, inputReal[FILTER_SIZE + j], j, inputImg[FILTER_SIZE + j]);
    }
#endif


    //Declare stream objects:
    hls::stream<FIR_INT_OUTPUT> realStream; //!< Stream between FIR output and CORDIC input (real)
    hls::stream<FIR_INT_OUTPUT> imgStream; //!< Stream between FIR output and CORDIC input (imaginary)

#pragma HLS STREAM variable=realStream
#pragma HLS STREAM variable=imgStream

#pragma HLS DATAFLOW
    //Declare the CORDIC and FIR, and connect them with the stream objects:
    complexFIR(inputReal, inputImg, realStream, imgStream, inputLength);
    bulkCordicConvert(realStream, imgStream, outputMag, outputPhase, inputLength);

}
