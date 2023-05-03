/**
 * @file polarFIR.h
 * @author Alex Stepko (axstepko.com)
 * @brief Header file for cartesian-to-polar FIR filter driver architecture.
 * @version 0.1
 * @date 2023-04-30
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
#ifndef POLAR_FIR_H
#define POLAR_FIR_H
#include <stdio.h>
#include <math.h>
#include "hls_stream.h"

#include "CORDIC.h"
#include "complexFIR.h"
#include "datatypes.h"

//#define POLAR_FIR_DEBUG_MODE

void polarFir(int *inputReal, int *inputImg, float *outputMag, float *outputPhase, int inputLength);

#endif // POLAR_FIR_H
