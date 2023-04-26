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
#pragma HLS INTERFACE mode = m_axi port = inputReal offset = slave bundle=dataInputReal
#pragma HLS INTERFACE mode = m_axi port = inputImg offset = slave bundle=dataInputImg

// Polar outputs:
#pragma HLS INTERFACE mode = m_axi port = outputMag offset = slave bundle=magOut
#pragma HLS INTERFACE mode = m_axi port = outputPhase offset = slave bundle=phaseOut

#pragma HLS INTERFACE mode = s_axilite port = inputLength
#pragma HLS INTERFACE mode = s_axilite port = return


	FIR_INT_INPUT kernelImg[FILTER_SIZE]; //!< Imaginary filter coefficient storage location
    FIR_INT_INPUT kernelReal[FILTER_SIZE]; //!< Real filter coefficient storage location


#pragma HLS ARRAY_PARTITION variable=kernelReal type=complete
#pragma HLS ARRAY_PARTITION variable=kernelImg type=complete

    // Initialize kernel with filter coefficients, using data from the first 0 -> FILTER_SIZE-1 spaces
#ifdef POLAR_FIR_DEBUG_MODE
    printf("FILTER:\n");
#endif
    FILTER_INIT:for (int i = 0; i < FILTER_SIZE; i++)
    {
        kernelReal[i] = FIR_INT_INPUT(inputReal[i]);
        kernelImg[i] = FIR_INT_INPUT(inputImg[i]);

#ifdef POLAR_FIR_DEBUG_MODE
      printf("POLARFIR: kernelReal[%d] = %d, kernelImg[%d] = %d \n", i, kernelReal[i].to_int(), i, kernelImg[i].to_int());
//      printf("POLARFIR: img = %d\n", kernelImg[i]);
#endif
    }



#ifdef POLAR_FIR_DEBUG_MODE
    printf("INPUTS:\n");
    for(int j = 0; j < inputLength; j++)
    {
    	printf("POLARFIR: inputReal[%d] = %d, inputImg[%d] = %d\n", j, inputReal[FILTER_SIZE + j], j, inputImg[FILTER_SIZE + j]);
    }
#endif

//    FIR_INT_INPUT* inputRealFIR = (FIR_INT_INPUT*) inputReal;
//    FIR_INT_INPUT* inputImgFIR = (FIR_INT_INPUT*) inputImg;

    //Declare stream objects:
    hls::stream<FIR_INT_OUTPUT> realStream; //!< Stream between FIR output and CORDIC input (real)
    hls::stream<FIR_INT_OUTPUT> imgStream; //!< Stream between FIR output and CORDIC input (imaginary)

//#pragma HLS STREAM variable=realStream
//#pragma HLS STREAM variable=imgStream

#pragma HLS DATAFLOW
    //Declare the CORDIC and FIR, and connect them with the stream objects:
    complexFIR(inputReal, inputImg, kernelReal, kernelImg, realStream, imgStream, inputLength);
    bulkCordicConvert(realStream, imgStream, outputMag, outputPhase, inputLength);

}
