/**
 * @file IPcontrol.c
 * @author Alex Stepko (axstepko.com)
 * @brief Higher-level bulk control of hardware IP in the design
 * @version 0.1
 * @date 2023-04-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "IPcontrol.h"

XPolarfir polarFIRinst;

/**
 * @brief Initializes the processing system
 * 
 */
void systemInit()
{
    printf("Initializing processing system.\n");
    init_platform();
    Xil_DCacheEnable();
    srand(0);
    printf("Initialization complete...\n");
}

/**
 * @brief De-initializes the processing system
 * 
 */
void systemDeInit()
{
    printf("Cleaning system\n");
    cleanup_platform();
}

/**
 * @brief Initializes an instance of the hardware accelerator
 *
 * @param instance
 * @return int general status return. Getting this return means the accelerator is ready to be loaded with input.
 */
int polarFIRinit(XPolarfir *instance)
{
    XPolarfir_Config *configPtr;
    int status = 0;
    printf("Initializing accelerator...\n");
    configPtr = XPolarfir_LookupConfig(XPAR_POLARFIR_0_DEVICE_ID);
    if (!configPtr)
    {
        fprintf(stderr, "ERROR: Failed to find accelerator configuration\n\r");
        return XST_FAILURE;
    }
    print("SUCCESS: Accelerator config found..\n\r");
    status = XPolarfir_CfgInitialize(instance, configPtr);
    if (status != XST_SUCCESS)
    {
        print("ERROR: Failed to initialize accelerator.\n\r");
        return XST_FAILURE;
    }
    print("SUCCESS: Accelerator initialized...\n\r");
    return status;
}

/**
 * @brief Primes the accelerator for run.
 *
 * @param instance Pointer to the accelerator instance
 */
void polarFIRstart(void *instance)
{
    XPolarfir *pAccel = (XPolarfir *)instance;
    XPolarfir_InterruptEnable(pAccel, 1);
    XPolarfir_InterruptGlobalEnable(pAccel);
    XPolarfir_Start(pAccel);
}

/**
 * @brief Runs the hardware accelerator
 * 
 * @return int status return when hardware is done writing. 0 is OK, 1 is error.
 */
int runHardware()
{
	int c = 0;
    Xil_DCacheFlush();
    printf("Wait for accel ready");
    while(!XPolarfir_IsReady(&polarFIRinst))
    {
    	printf(".");
    }
    printf("\n");
    if (XPolarfir_IsReady(&polarFIRinst))
    {
        print("Starting peripheral...\n");
    }
    else
    {
        print("ERROR: peripheral not ready to run...\n\r");
        return 1;
    }
    XPolarfir_Start(&polarFIRinst);
    c = 0;
    while (!XPolarfir_IsReady(&polarFIRinst))
    {
        printf("Waiting for completion... %i\r", ++c);
    }
    Xil_DCacheInvalidate();
    print("Peripheral complete\n");
    return 0;
}
