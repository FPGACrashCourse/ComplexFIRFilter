/**
 * @file main.c
 * @author Alex Stepko (axstepko.com)
 * @brief Runs iterations of a 1-d FIR filter
 * @version 0.1
 * @date 2023-04-26
 *
 * @copyright  Copyright (c) Alex Stepko (axstepko.com) 2023. All rights reserved. THIS CODE WRITTEN WHOLY BY ALEX STEPKO (AXSTEPKO.COM) Redistribution and use in source and binary forms, with or without modification, are STRICTLY PROHIBITED WITHOUT PRIOR WRITTEN PERMISSION from Alex Stepko (axstepko.com). *This software is provided "as is" and any express or implied warranties, including, but not limited to, the implied warranties of merchantability and fitness for a particular purpose are disclaimed. In no event shall Alex Stepko (axstepko.com) be liable for any direct, indirect, incidental, special, exemplary, or consequential damages (including, but not limited to, procurement of substitute goods or services; *ACADEMIC INTEGRITY: STUDENTS, RESEARCHERS, OR INSTITUTIONS MAY USE THIS SOFTWARE FOR EDUCATIONAL OR RESEARCH PURPOSES ONLY. YOU ARE RESPONSIBLE FOR ENSURING THAT THE USAGE OF THIS SOFTWARE COMPLIES WITH THE COPYRIGHT POLICY STATED ABOVE, IN ADDITION TO YOUR INSTITUTION'S POLICIES ON ACADEMIC INTEGRITY AND PLAGARISM. IT IS PROHIBITED TO REPRESENT THIS WORK AS YOUR OWN, INCLUDING BUT NOT LIMITED TO THE DUPLICATION, MODIFICATION, OR DISTRUBTION OF THIS SOFTWARE WITHOUT PRIOR WRITTEN PREMISSION FROM THE SOFTWARE'S OWNER (ALEX STEPKO). ALEX STEPKO (AXSTEPKO.COM) DISCLAIMS ALL LIABILITY FOR ANY VIOLATIONS OF ACADEMIC INTEGRITY OR OTHER ETHICAL STANDARDS COMMITTED BY USERS OR VIEWERS OF THIS SOFTWARE.
 *
 */
#ifndef GLOBAL_DEFINES
#define GLOBAL_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h" // Parameter definitions for processor periperals
#include "xscugic.h"     // Processor interrupt controller device driver
#include "xil_cache.h"
#endif // GLOBAL_DEFINES

#ifndef DEPENDENCIES
#define DEPENDENCIES
#include "IPcontrol.h"
#endif // DEPENDENCIES

#define MAIN_DEBUG_MODE

//#define RANDOM_INPUT_GEN

//#define WORST_CASE 50


#define COEFF_LENGTH 25
#define DATA_LENGTH 30
#define INPUT_LENGTH COEFF_LENGTH + DATA_LENGTH

int main()
{
    systemInit();
    int ret = 0; //!< Status return variable

    ret = polarFIRinit(&polarFIRinst);
    if (ret != XST_SUCCESS)
    {
        print("Peripheral setup failed\n\r");
        exit(-1);
    }

    printf("Initializing filter\n");

    int inputReal[INPUT_LENGTH] = {};
    int inputImg[INPUT_LENGTH] = {};
#ifdef WORST_CASE
    COEFF_GEN:for (int i = 0; i < COEFF_LENGTH; i++)
        {
            inputReal[i] = WORST_CASE;
            inputImg[i] = WORST_CASE;
        }
#else
COEFF_GEN:for (int i = 0; i < COEFF_LENGTH; i++)
    {
        inputReal[i] = COEFF_LENGTH - i;
        inputImg[i] = i + 1;
    }
#endif
// Generate data input:
#ifdef RANDOM_INPUT_GEN
INPUT_GEN:for (int i = 0; i < DATA_LENGTH; i++)
    {
        inputReal[COEFF_LENGTH + i] = rand() % 50;
        inputImg[COEFF_LENGTH + i] = -1 * rand() * rand() % 50;
    }
#else
INPUT_GEN:
	for(int i = 0; i < DATA_LENGTH; i++)
	{
		inputReal[COEFF_LENGTH + i] = 1;
		inputImg[COEFF_LENGTH + i] = 0;
	}
#endif

#ifdef WORST_CASE
#ifndef RANDOM_INPUT_GEN
	INPUT_GEN:
		for(int i = 0; i < DATA_LENGTH; i++)
		{
			inputReal[COEFF_LENGTH + i] = 50;
			inputImg[COEFF_LENGTH + i] = 50;
		}
#endif
#endif

    // Locate and clean memory for the peripheral I/O:
	u32 *INPUT_REAL_BUFFER = XPAR_PS7_DDR_0_S_AXI_BASEADDR;
	u32 *INPUT_IMG_BUFFER = XPAR_PS7_DDR_0_S_AXI_BASEADDR + 0x20000;
	u32 *HW_MAG_BUFFER = XPAR_PS7_DDR_0_S_AXI_BASEADDR +  0x20000 + 0x20000;
	u32 *HW_PHASE_BUFFER = XPAR_PS7_DDR_0_S_AXI_BASEADDR + 0x20000+ 0x20000 + 0x20000;

    memset(INPUT_IMG_BUFFER, 0, (INPUT_LENGTH << 2));
    memset(INPUT_REAL_BUFFER, 0, (INPUT_LENGTH << 2));
    memset(HW_MAG_BUFFER, 0, (DATA_LENGTH << 2));
    memset(HW_PHASE_BUFFER, 0, (DATA_LENGTH << 2));

INPUT_BUFF_SET:
    for (int i = 0; i < INPUT_LENGTH; i++)
    {
        INPUT_IMG_BUFFER[i] = inputImg[i];
        INPUT_REAL_BUFFER[i] = inputReal[i];
    }

    XPolarfir_Set_inputReal(&polarFIRinst, (u64)INPUT_REAL_BUFFER);
    XPolarfir_Set_inputImg(&polarFIRinst, (u64)INPUT_IMG_BUFFER);
    XPolarfir_Set_inputLength(&polarFIRinst, (u32)DATA_LENGTH);
    XPolarfir_Set_outputMag(&polarFIRinst, (u64)HW_MAG_BUFFER);
    XPolarfir_Set_outputPhase(&polarFIRinst, (u64)HW_PHASE_BUFFER);

#ifdef MAIN_DEBUG_MODE
    printf("Filter set with\n");
    for (int i = 0; i < COEFF_LENGTH; i++)
    {
        printf("coeff[%d] = %d + j%d\n", i, INPUT_REAL_BUFFER[i], INPUT_IMG_BUFFER[i]);
    }

    printf("Input set with\n");
    for (int i = 0; i < DATA_LENGTH; i++)
    {
        printf("input[%d] = %d + j%d\n", i, (int)INPUT_REAL_BUFFER[COEFF_LENGTH + i], (int)INPUT_IMG_BUFFER[COEFF_LENGTH + i]);
    }
#endif

    printf("Filter initialized.\n");

    int hardwareRet = runHardware();

    if(hardwareRet == 0)
    {
        printf("Result is ready\n");

        //Somewhere here, we need to access the output arrays, because the result is done.

        //////////////////////////////////////////////////
        printf("Received output from hardware:\n");
        for(int i = 0; i < DATA_LENGTH; i++)
        {
        	//printf("hwMag[%d] = %f, ph = %f\n", i, (float*)(HW_MAG_BUFFER + i), (float*)(HW_PHASE_BUFFER + i));
        	printf("hwMag[%d] = %f, ph = %f\r", i, (*(float*)(HW_MAG_BUFFER  + i)), (*(float*)(HW_PHASE_BUFFER  + i)));
        }
    }
    else
    {
        printf("Result failed to generate. No output to show. :( \n");
    }

    systemDeInit();
    return 0;
}




