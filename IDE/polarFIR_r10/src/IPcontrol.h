/**
 * @file IPcontrol.h
 * @author Alex Stepko (axstepko.com)
 * @brief Header file for higher-level bulk control of hardware IP in the design
 * @version 0.1
 * @date 2023-04-26
 * 
 * @copyright  Copyright (c) Alex Stepko (axstepko.com) 2023. All rights reserved. THIS CODE WRITTEN WHOLY BY ALEX STEPKO (AXSTEPKO.COM) Redistribution and use in source and binary forms, with or without modification, are STRICTLY PROHIBITED WITHOUT PRIOR WRITTEN PERMISSION from Alex Stepko (axstepko.com). *This software is provided "as is" and any express or implied warranties, including, but not limited to, the implied warranties of merchantability and fitness for a particular purpose are disclaimed. In no event shall Alex Stepko (axstepko.com) be liable for any direct, indirect, incidental, special, exemplary, or consequential damages (including, but not limited to, procurement of substitute goods or services; *ACADEMIC INTEGRITY: STUDENTS, RESEARCHERS, OR INSTITUTIONS MAY USE THIS SOFTWARE FOR EDUCATIONAL OR RESEARCH PURPOSES ONLY. YOU ARE RESPONSIBLE FOR ENSURING THAT THE USAGE OF THIS SOFTWARE COMPLIES WITH THE COPYRIGHT POLICY STATED ABOVE, IN ADDITION TO YOUR INSTITUTION'S POLICIES ON ACADEMIC INTEGRITY AND PLAGARISM. IT IS PROHIBITED TO REPRESENT THIS WORK AS YOUR OWN, INCLUDING BUT NOT LIMITED TO THE DUPLICATION, MODIFICATION, OR DISTRUBTION OF THIS SOFTWARE WITHOUT PRIOR WRITTEN PREMISSION FROM THE SOFTWARE'S OWNER (ALEX STEPKO). ALEX STEPKO (AXSTEPKO.COM) DISCLAIMS ALL LIABILITY FOR ANY VIOLATIONS OF ACADEMIC INTEGRITY OR OTHER ETHICAL STANDARDS COMMITTED BY USERS OR VIEWERS OF THIS SOFTWARE.
 * 
 */
#ifndef IPCONTROL_H
#define IPCONTROL_H
#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xpolarfir.h"
#include "xpolarfir_hw.h"

extern XPolarfir polarFIRinst;

void systemInit();
void systemDeInit();
int polarFIRinit(XPolarfir *instance);
void polarFIRstart(void *instance);
int runHardware();


#endif // IPCONTROL_H
