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
#pragma HLS INTERFACE mode = m_axi port = inputReal offset = slave bundle=dataInputReal
#pragma HLS INTERFACE mode = m_axi port = inputImg offset = slave bundle=dataInputImg

// Filter inputs:
#pragma HLS INTERFACE mode = m_axi port = filterReal offset = slave bundle=filterInputReal
#pragma HLS INTERFACE mode = m_axi port = filterImg offset = slave bundle=filterInputImg


// Polar outputs:
#pragma HLS INTERFACE mode = m_axi port = outputMag offset = slave bundle=magOut
#pragma HLS INTERFACE mode = m_axi port = outputPhase offset = slave bundle=phaseOut

#pragma HLS INTERFACE mode = s_axilite port = inputLength
#pragma HLS INTERFACE mode = s_axilite port = return

    int kernelReal[FILTER_SIZE]; //!< Real filter coefficient storage location
    int kernelImg[FILTER_SIZE]; //!< Imaginary filter coefficient storage location

#pragma HLS ARRAY_PARTITION variable=kernelReal type=complete
#pragma HLS ARRAY_PARTITION variable=kernelImg type=complete

#pragma HLS ARRAY_PARTITION variable=filterReal type=complete
#pragma HLS ARRAY_PARTITION variable=filterImg type=complete

    // Initialize kernel with filter coefficients:
    FILTER_INIT:for (int i = 0; i < FILTER_SIZE; i++)
    {
        kernelReal[i] = filterReal[i];
        kernelImg[i] = filterImg[i];
    }

    //Declare stream objects:
    hls::stream<int> realStream;
    hls::stream<int> imgStream;

#pragma HLS STREAM variable=realStream
#pragma HLS STREAM variable=imgStream

#pragma HLS DATAFLOW
    //Declare the CORDIC and FIR, and connect them with the stream objects:
    complexFIR(inputReal, inputImg, kernelReal, kernelImg, realStream, imgStream);
    bulkCordicConvert(realStream, imgStream, outputMag, outputPhase, FILTER_SIZE);

}
