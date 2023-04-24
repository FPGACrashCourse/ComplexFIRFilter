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
 * @param inputReal
 * @param inputImg
 * @param kernelReal
 * @param kernelImg
 * @param outputMag
 * @param outputReal
 * @param inputLength
 */
void polarFir(int *inputReal, int *inputImg, int *filterReal, int *filterImg, float *outputMag, float *outputPhase, int inputLength)
{

// Define the system's AXI interface:

// Data inputs:
#pragma HLS INTERFACE mode = m_axi port = inputReal offset = slave bundle = dataIn
#pragma HLS INTERFACE mode = m_axi port = inputImg offset = slave bundle = dataIn

// Filter inputs:
#pragma HLS INTERFACE mode = m_axi port = filterReal offset = slave bundle = filter
#pragma HLS INTERFACE mode = m_axi port = filterImg offset = slave bundle = filter

// Cartesian outputs:
#pragma HLS INTERFACE mode = m_axi port = outputMag offset = slave bundle = dataOut
#pragma HLS INTERFACE mode = m_axi port = outputPhase offset = slave bundle = dataOut

#pragma HLS DATAFLOW

    int kernelReal[FILTER_SIZE]     //!< Real filter coefficient storage location
        int kernelImg[FILTER_SIZE]; //!< Imaginary filter coefficient storage location

    // Intiialize kernel with filter coefficients:
    for (int i = 0; i < FILTER_SIZE; i++)
    {
#pragma HLS UNROLL
        kernelReal[i] = filterReal[i];
        kernelImg[i] = filterImg[i];
    }

    //Declare stream objects:
    hls::stream<int> realStream;
    hls::stream<int> imgStream;
}
