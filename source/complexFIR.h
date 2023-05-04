/**
 * @file complexFIR.h
 * @author Alex Stepko (axstepko.com)
 * @brief Header file for a 1-d rectangular coordinate FIR filter
 * @version 1.0
 * @date 2023-04-24
 * 
 * @copyright  Copyright (c) Alex Stepko (axstepko.com) 2023. All rights reserved.
 * 
 */

/**
 * Copyright (c) Alex Stepko (axstepko.com) 2023. All rights reserved.
 * 
 * THIS CODE WRITTEN WHOLLY BY ALEX STEPKO (AXSTEPKO.COM) Redistribution and
 * use in source and binary forms, with or without modification, are
 * STRICTLY PROHIBITED WITHOUT PRIOR WRITTEN PERMISSION from Alex Stepko (axstepko.com). 
 * 
 * This software is provided "as is" and any express or implied warranties, including,
 * but not limited to, the implied warranties of merchantability and fitness for a 
 * particular purpose are disclaimed. In no event shall Alex Stepko (axstepko.com) be 
 * liable for any direct, indirect, incidental, special, exemplary, or consequential 
 * damages (including, but not limited to, procurement of substitute goods or services; 
 * 
 * ACADEMIC INTEGRITY: STUDENTS, RESEARCHERS, OR INSTITUTIONS MAY USE THIS SOFTWARE 
 * FOR EDUCATIONAL OR RESEARCH PURPOSES ONLY. YOU ARE RESPONSIBLE FOR ENSURING THAT 
 * THE USAGE OF THIS SOFTWARE COMPLIES WITH THE COPYRIGHT POLICY STATED ABOVE, IN 
 * ADDITION TO YOUR INSTITUTION'S POLICIES ON ACADEMIC INTEGRITY AND PLAGARISM. 
 * IT IS PROHIBITED TO REPRESENT THIS WORK AS YOUR OWN, INCLUDING BUT NOT LIMITED 
 * TO THE DUPLICATION, MODIFICATION, OR DISTRUBTION OF THIS SOFTWARE WITHOUT PRIOR 
 * WRITTEN PREMISSION FROM THE SOFTWARE'S OWNER (ALEX STEPKO). 
 * ALEX STEPKO (AXSTEPKO.COM) DISCLAIMS ALL LIABILITY FOR ANY VIOLATIONS OF ACADEMIC 
 * INTEGRITY OR OTHER ETHICAL STANDARDS COMMITTED BY USERS OR VIEWERS OF THIS SOFTWARE.
 * 
 */
#ifndef COMPLEX_FIR_H
#define COMPLEX_FIR_H
#include <stdio.h>
#include <math.h>
#include "hls_stream.h"

#include "datatypes.h"

//#define FIR_DEBUG_MODE //!< Enables rich debugging support within these functions

#define DEBUG_SIZE 25  //!< Constant-width known-values for debug.
#define FILTER_SIZE 25 //!< Constant-width value for HLS optimization

//const int FILTER_SIZE = 25;

static int debugInputReal[DEBUG_SIZE] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
static int debugInputImg[DEBUG_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static int debugCoeffReal[DEBUG_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
static int debugCoeffImg[DEBUG_SIZE] = {25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

void complexFIR(int *inputReal, int *inputImg, hls::stream<FIR_INT_OUTPUT> &outputReal, hls::stream<FIR_INT_OUTPUT> &outputImg, int filterLength);
void computeComplexFIR(FIR_INT_INPUT inputReal, FIR_INT_INPUT inputImg, FIR_INT_INPUT filterReal[FILTER_SIZE], FIR_INT_INPUT filterImg[FILTER_SIZE], FIR_INT_OUTPUT *outputReal, FIR_INT_OUTPUT *outputImg);
#endif // COMPLEX_FIR_H
