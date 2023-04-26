/**
 * @file main.c
 * @author Alex Stepko (axstepko.com)
 * @brief Runs iterations of a 1-d FIR filter
 * @version 0.1
 * @date 2023-04-26
 *
 * @copyright Copyright (c) 2023
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



#define COEFF_LENGTH 25
#define DATA_LENGTH 25
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

// Generate coefficient input:
COEFF_GEN:for (int i = 0; i < COEFF_LENGTH; i++)
    {
        inputReal[i] = COEFF_LENGTH - i;
        inputImg[i] = i + 1;
#ifdef MAIN_DEBUG_MODE
        printf("coeff = %d + j%d\n", inputReal[i], inputImg[i]);
#endif
    }
// Generate data input:
INPUT_GEN:for (int i = 0; i < DATA_LENGTH; i++)
    {
        inputReal[COEFF_LENGTH + i] = rand() % 50;
        inputImg[COEFF_LENGTH + i] = rand() % 50;
#ifdef MAIN_DEBUG_MODE
        printf("input[%d] = %d + j%d\n", i, inputReal[COEFF_LENGTH + i], inputImg[COEFF_LENGTH + i] );
#endif
    }

    // Locate and clean memory for the peripheral
    u64 *INPUT_REAL_BUFFER = XPAR_PS7_DDR_0_S_AXI_BASEADDR + 0x20000;
    u64 *INPUT_IMG_BUFFER = XPAR_PS7_DDR_0_S_AXI_BASEADDR;
    memset(INPUT_IMG_BUFFER, 0, INPUT_LENGTH << 2);
    memset(INPUT_REAL_BUFFER, 0, INPUT_LENGTH << 2);

    // Allocate memory for the peripheral outputs:
    // Output size is the same as the input data size.
    // Memory is cleaned explicitly with the = {} field.
    u64 hw_outputMag[DATA_LENGTH] = {};
    u64 hw_outputPhase[DATA_LENGTH] = {};


INPUT_BUFF_SET:
    for (int i = 0; i < INPUT_LENGTH; i++)
    {
        INPUT_IMG_BUFFER[i] = inputImg[i];
        INPUT_REAL_BUFFER[i] = inputReal[i];
    }

    XPolarfir_Set_inputReal(&polarFIRinst, INPUT_REAL_BUFFER);
    XPolarfir_Set_inputImg(&polarFIRinst, INPUT_IMG_BUFFER);
    XPolarfir_Set_inputLength(&polarFIRinst, (u32)DATA_LENGTH);

#ifdef MAIN_DEBUG_MODE
    printf("Filter set with\n");
    for (int i = 0; i < COEFF_LENGTH; i++)
    {
        printf("coeff[%d] = %d + j%d\n", i, inputReal[i], inputImg[i]);
    }

    printf("Input set with\n");
    for (int i = 0; i < DATA_LENGTH; i++)
    {
        printf("input[%d] = %d + j%d\n", i, (int)INPUT_REAL_BUFFER[COEFF_LENGTH + i], (int)INPUT_IMG_BUFFER[COEFF_LENGTH + i]);
    }
#endif

    int hardwareRet = runHardware();

    if(hardwareRet == 0)
    {
        printf("Result is ready\n");

        //Somewhere here, we need to access the output arrays, because the result is done.

        XPolarfir_Set_outputMag(&polarFIRinst, hw_outputMag);
        XPolarfir_Set_outputPhase(&polarFIRinst, hw_outputPhase);

        //////////////////////////////////////////////////
        printf("Recieved output from hardware:\n");
        for(int i = 0; i < DATA_LENGTH; i++)
        {
            printf("Mag = %llu, Phase = %llu\n", hw_outputMag[i], hw_outputPhase[i]);
        }
    }
    else
    {
        printf("Result failed to generate. No output to show.\n");
    }

    systemDeInit();
    return 0;
}




