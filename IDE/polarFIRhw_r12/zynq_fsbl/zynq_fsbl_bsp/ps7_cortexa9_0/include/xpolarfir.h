// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XPOLARFIR_H
#define XPOLARFIR_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xpolarfir_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u64 Control_BaseAddress;
} XPolarfir_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XPolarfir;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XPolarfir_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XPolarfir_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XPolarfir_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XPolarfir_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XPolarfir_Initialize(XPolarfir *InstancePtr, u16 DeviceId);
XPolarfir_Config* XPolarfir_LookupConfig(u16 DeviceId);
int XPolarfir_CfgInitialize(XPolarfir *InstancePtr, XPolarfir_Config *ConfigPtr);
#else
int XPolarfir_Initialize(XPolarfir *InstancePtr, const char* InstanceName);
int XPolarfir_Release(XPolarfir *InstancePtr);
#endif

void XPolarfir_Start(XPolarfir *InstancePtr);
u32 XPolarfir_IsDone(XPolarfir *InstancePtr);
u32 XPolarfir_IsIdle(XPolarfir *InstancePtr);
u32 XPolarfir_IsReady(XPolarfir *InstancePtr);
void XPolarfir_EnableAutoRestart(XPolarfir *InstancePtr);
void XPolarfir_DisableAutoRestart(XPolarfir *InstancePtr);

void XPolarfir_Set_inputReal(XPolarfir *InstancePtr, u64 Data);
u64 XPolarfir_Get_inputReal(XPolarfir *InstancePtr);
void XPolarfir_Set_inputImg(XPolarfir *InstancePtr, u64 Data);
u64 XPolarfir_Get_inputImg(XPolarfir *InstancePtr);
void XPolarfir_Set_outputMag(XPolarfir *InstancePtr, u64 Data);
u64 XPolarfir_Get_outputMag(XPolarfir *InstancePtr);
void XPolarfir_Set_outputPhase(XPolarfir *InstancePtr, u64 Data);
u64 XPolarfir_Get_outputPhase(XPolarfir *InstancePtr);
void XPolarfir_Set_inputLength(XPolarfir *InstancePtr, u32 Data);
u32 XPolarfir_Get_inputLength(XPolarfir *InstancePtr);

void XPolarfir_InterruptGlobalEnable(XPolarfir *InstancePtr);
void XPolarfir_InterruptGlobalDisable(XPolarfir *InstancePtr);
void XPolarfir_InterruptEnable(XPolarfir *InstancePtr, u32 Mask);
void XPolarfir_InterruptDisable(XPolarfir *InstancePtr, u32 Mask);
void XPolarfir_InterruptClear(XPolarfir *InstancePtr, u32 Mask);
u32 XPolarfir_InterruptGetEnabled(XPolarfir *InstancePtr);
u32 XPolarfir_InterruptGetStatus(XPolarfir *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
