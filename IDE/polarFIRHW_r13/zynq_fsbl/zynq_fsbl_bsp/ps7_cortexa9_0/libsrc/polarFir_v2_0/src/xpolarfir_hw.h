// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read/COR)
//        bit 7  - auto_restart (Read/Write)
//        bit 9  - interrupt (Read)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0 - enable ap_done interrupt (Read/Write)
//        bit 1 - enable ap_ready interrupt (Read/Write)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0 - ap_done (Read/TOW)
//        bit 1 - ap_ready (Read/TOW)
//        others - reserved
// 0x10 : Data signal of inputReal
//        bit 31~0 - inputReal[31:0] (Read/Write)
// 0x14 : Data signal of inputReal
//        bit 31~0 - inputReal[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of inputImg
//        bit 31~0 - inputImg[31:0] (Read/Write)
// 0x20 : Data signal of inputImg
//        bit 31~0 - inputImg[63:32] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of outputMag
//        bit 31~0 - outputMag[31:0] (Read/Write)
// 0x2c : Data signal of outputMag
//        bit 31~0 - outputMag[63:32] (Read/Write)
// 0x30 : reserved
// 0x34 : Data signal of outputPhase
//        bit 31~0 - outputPhase[31:0] (Read/Write)
// 0x38 : Data signal of outputPhase
//        bit 31~0 - outputPhase[63:32] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of inputLength
//        bit 31~0 - inputLength[31:0] (Read/Write)
// 0x44 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XPOLARFIR_CONTROL_ADDR_AP_CTRL          0x00
#define XPOLARFIR_CONTROL_ADDR_GIE              0x04
#define XPOLARFIR_CONTROL_ADDR_IER              0x08
#define XPOLARFIR_CONTROL_ADDR_ISR              0x0c
#define XPOLARFIR_CONTROL_ADDR_INPUTREAL_DATA   0x10
#define XPOLARFIR_CONTROL_BITS_INPUTREAL_DATA   64
#define XPOLARFIR_CONTROL_ADDR_INPUTIMG_DATA    0x1c
#define XPOLARFIR_CONTROL_BITS_INPUTIMG_DATA    64
#define XPOLARFIR_CONTROL_ADDR_OUTPUTMAG_DATA   0x28
#define XPOLARFIR_CONTROL_BITS_OUTPUTMAG_DATA   64
#define XPOLARFIR_CONTROL_ADDR_OUTPUTPHASE_DATA 0x34
#define XPOLARFIR_CONTROL_BITS_OUTPUTPHASE_DATA 64
#define XPOLARFIR_CONTROL_ADDR_INPUTLENGTH_DATA 0x40
#define XPOLARFIR_CONTROL_BITS_INPUTLENGTH_DATA 32

