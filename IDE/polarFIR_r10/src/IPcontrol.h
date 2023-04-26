/**
 * @file IPcontrol.h
 * @author Alex Stepko (axstepko.com)
 * @brief Header file for higher-level bulk control of hardware IP in the design
 * @version 0.1
 * @date 2023-04-26
 * 
 * @copyright Copyright (c) 2023
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
