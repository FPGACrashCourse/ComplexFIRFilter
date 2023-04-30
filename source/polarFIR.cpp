/**
 * @file polarFIR.cpp
 * @author Alex Stepko (axstepko.com)
 * @brief Cartesian-to-polar FIR filter driver and interface architecture
 * @version 0.1
 * @date 2023-04-30
 * 
 * @copyright  Copyright (c) Alex Stepko (axstepko.com) 2023. All rights reserved. THIS CODE WRITTEN WHOLY BY ALEX STEPKO (AXSTEPKO.COM) Redistribution and use in source and binary forms, with or without modification, are STRICTLY PROHIBITED WITHOUT PRIOR WRITTEN PERMISSION from Alex Stepko (axstepko.com). *This software is provided "as is" and any express or implied warranties, including, but not limited to, the implied warranties of merchantability and fitness for a particular purpose are disclaimed. In no event shall Alex Stepko (axstepko.com) be liable for any direct, indirect, incidental, special, exemplary, or consequential damages (including, but not limited to, procurement of substitute goods or services; *ACADEMIC INTEGRITY: STUDENTS, RESEARCHERS, OR INSTITUTIONS MAY USE THIS SOFTWARE FOR EDUCATIONAL OR RESEARCH PURPOSES ONLY. YOU ARE RESPONSIBLE FOR ENSURING THAT THE USAGE OF THIS SOFTWARE COMPLIES WITH THE COPYRIGHT POLICY STATED ABOVE, IN ADDITION TO YOUR INSTITUTION'S POLICIES ON ACADEMIC INTEGRITY AND PLAGARISM. IT IS PROHIBITED TO REPRESENT THIS WORK AS YOUR OWN, INCLUDING BUT NOT LIMITED TO THE DUPLICATION, MODIFICATION, OR DISTRUBTION OF THIS SOFTWARE WITHOUT PRIOR WRITTEN PREMISSION FROM THE SOFTWARE'S OWNER (ALEX STEPKO). ALEX STEPKO (AXSTEPKO.COM) DISCLAIMS ALL LIABILITY FOR ANY VIOLATIONS OF ACADEMIC INTEGRITY OR OTHER ETHICAL STANDARDS COMMITTED BY USERS OR VIEWERS OF THIS SOFTWARE.
 * 
 */
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
#pragma HLS INTERFACE mode = m_axi port = inputReal offset = slave
#pragma HLS INTERFACE mode = m_axi port = inputImg offset = slave

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
