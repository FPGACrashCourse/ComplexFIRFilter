/**
 * @file datatypes.h
 * @author Alex Stepko (axstepko.com)
 * @brief Custom-width arbitrary datatype definitions.
 * @version 1.0
 * @date 2023-04-27
 * 
 * @copyright  Copyright (c) Alex Stepko (axstepko.com) 2023. All rights reserved. THIS CODE WRITTEN WHOLY BY ALEX STEPKO (AXSTEPKO.COM) Redistribution and use in source and binary forms, with or without modification, are STRICTLY PROHIBITED WITHOUT PRIOR WRITTEN PERMISSION from Alex Stepko (axstepko.com). *This software is provided "as is" and any express or implied warranties, including, but not limited to, the implied warranties of merchantability and fitness for a particular purpose are disclaimed. In no event shall Alex Stepko (axstepko.com) be liable for any direct, indirect, incidental, special, exemplary, or consequential damages (including, but not limited to, procurement of substitute goods or services; *ACADEMIC INTEGRITY: STUDENTS, RESEARCHERS, OR INSTITUTIONS MAY USE THIS SOFTWARE FOR EDUCATIONAL OR RESEARCH PURPOSES ONLY. YOU ARE RESPONSIBLE FOR ENSURING THAT THE USAGE OF THIS SOFTWARE COMPLIES WITH THE COPYRIGHT POLICY STATED ABOVE, IN ADDITION TO YOUR INSTITUTION'S POLICIES ON ACADEMIC INTEGRITY AND PLAGARISM. IT IS PROHIBITED TO REPRESENT THIS WORK AS YOUR OWN, INCLUDING BUT NOT LIMITED TO THE DUPLICATION, MODIFICATION, OR DISTRUBTION OF THIS SOFTWARE WITHOUT PRIOR WRITTEN PREMISSION FROM THE SOFTWARE'S OWNER (ALEX STEPKO). ALEX STEPKO (AXSTEPKO.COM) DISCLAIMS ALL LIABILITY FOR ANY VIOLATIONS OF ACADEMIC INTEGRITY OR OTHER ETHICAL STANDARDS COMMITTED BY USERS OR VIEWERS OF THIS SOFTWARE.
 * 
 */
#ifndef DATATYPES_H
#define DATATYPES_H
#include <ap_fixed.h>
#include "ap_int.h"

#define FIXED_BITS_M 24 // 24
#define FIXED_BITS_N 17 // 12
typedef ap_fixed<FIXED_BITS_M, FIXED_BITS_N> FIXED_POINT; //!< AP-Fixed datype for consistent calculation in the CORDIC

#define FIR_INT_INPUT_WIDTH 6 // 6 bits wide
#define FIR_INT_OUTPUT_WIDTH 18 // 18 bits wide
typedef ap_int<FIR_INT_INPUT_WIDTH> FIR_INT_INPUT; //!< Fixed-width integer datatype for FIR inputs
typedef ap_int<FIR_INT_OUTPUT_WIDTH> FIR_INT_OUTPUT; //!< Fixed-width integer datatype for FIR outputs

#endif
