// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xpolarfir.h"

extern XPolarfir_Config XPolarfir_ConfigTable[];

XPolarfir_Config *XPolarfir_LookupConfig(u16 DeviceId) {
	XPolarfir_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XPOLARFIR_NUM_INSTANCES; Index++) {
		if (XPolarfir_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XPolarfir_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XPolarfir_Initialize(XPolarfir *InstancePtr, u16 DeviceId) {
	XPolarfir_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XPolarfir_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XPolarfir_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

