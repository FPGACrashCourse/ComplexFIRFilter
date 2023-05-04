// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xpolarfir.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XPolarfir_CfgInitialize(XPolarfir *InstancePtr, XPolarfir_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XPolarfir_Start(XPolarfir *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPolarfir_ReadReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_AP_CTRL) & 0x80;
    XPolarfir_WriteReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XPolarfir_IsDone(XPolarfir *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPolarfir_ReadReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XPolarfir_IsIdle(XPolarfir *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPolarfir_ReadReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XPolarfir_IsReady(XPolarfir *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPolarfir_ReadReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XPolarfir_EnableAutoRestart(XPolarfir *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPolarfir_WriteReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XPolarfir_DisableAutoRestart(XPolarfir *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPolarfir_WriteReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_AP_CTRL, 0);
}

void XPolarfir_Set_inputReal(XPolarfir *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPolarfir_WriteReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_INPUTREAL_DATA, (u32)(Data));
    XPolarfir_WriteReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_INPUTREAL_DATA + 4, (u32)(Data >> 32));
}

u64 XPolarfir_Get_inputReal(XPolarfir *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPolarfir_ReadReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_INPUTREAL_DATA);
    Data += (u64)XPolarfir_ReadReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_INPUTREAL_DATA + 4) << 32;
    return Data;
}

void XPolarfir_Set_inputImg(XPolarfir *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPolarfir_WriteReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_INPUTIMG_DATA, (u32)(Data));
    XPolarfir_WriteReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_INPUTIMG_DATA + 4, (u32)(Data >> 32));
}

u64 XPolarfir_Get_inputImg(XPolarfir *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPolarfir_ReadReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_INPUTIMG_DATA);
    Data += (u64)XPolarfir_ReadReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_INPUTIMG_DATA + 4) << 32;
    return Data;
}

void XPolarfir_Set_outputMag(XPolarfir *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPolarfir_WriteReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_OUTPUTMAG_DATA, (u32)(Data));
    XPolarfir_WriteReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_OUTPUTMAG_DATA + 4, (u32)(Data >> 32));
}

u64 XPolarfir_Get_outputMag(XPolarfir *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPolarfir_ReadReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_OUTPUTMAG_DATA);
    Data += (u64)XPolarfir_ReadReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_OUTPUTMAG_DATA + 4) << 32;
    return Data;
}

void XPolarfir_Set_outputPhase(XPolarfir *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPolarfir_WriteReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_OUTPUTPHASE_DATA, (u32)(Data));
    XPolarfir_WriteReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_OUTPUTPHASE_DATA + 4, (u32)(Data >> 32));
}

u64 XPolarfir_Get_outputPhase(XPolarfir *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPolarfir_ReadReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_OUTPUTPHASE_DATA);
    Data += (u64)XPolarfir_ReadReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_OUTPUTPHASE_DATA + 4) << 32;
    return Data;
}

void XPolarfir_Set_inputLength(XPolarfir *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPolarfir_WriteReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_INPUTLENGTH_DATA, Data);
}

u32 XPolarfir_Get_inputLength(XPolarfir *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPolarfir_ReadReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_INPUTLENGTH_DATA);
    return Data;
}

void XPolarfir_InterruptGlobalEnable(XPolarfir *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPolarfir_WriteReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_GIE, 1);
}

void XPolarfir_InterruptGlobalDisable(XPolarfir *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPolarfir_WriteReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_GIE, 0);
}

void XPolarfir_InterruptEnable(XPolarfir *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XPolarfir_ReadReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_IER);
    XPolarfir_WriteReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_IER, Register | Mask);
}

void XPolarfir_InterruptDisable(XPolarfir *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XPolarfir_ReadReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_IER);
    XPolarfir_WriteReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_IER, Register & (~Mask));
}

void XPolarfir_InterruptClear(XPolarfir *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPolarfir_WriteReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_ISR, Mask);
}

u32 XPolarfir_InterruptGetEnabled(XPolarfir *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XPolarfir_ReadReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_IER);
}

u32 XPolarfir_InterruptGetStatus(XPolarfir *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XPolarfir_ReadReg(InstancePtr->Control_BaseAddress, XPOLARFIR_CONTROL_ADDR_ISR);
}

