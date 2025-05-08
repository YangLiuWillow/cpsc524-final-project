// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XSHORTEST_H
#define XSHORTEST_H

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
#include "xshortest_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u64 Sqrt_BaseAddress;
    u64 Control_BaseAddress;
} XShortest_Config;
#endif

typedef struct {
    u64 Sqrt_BaseAddress;
    u64 Control_BaseAddress;
    u32 IsReady;
} XShortest;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XShortest_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XShortest_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XShortest_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XShortest_ReadReg(BaseAddress, RegOffset) \
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
int XShortest_Initialize(XShortest *InstancePtr, u16 DeviceId);
XShortest_Config* XShortest_LookupConfig(u16 DeviceId);
int XShortest_CfgInitialize(XShortest *InstancePtr, XShortest_Config *ConfigPtr);
#else
int XShortest_Initialize(XShortest *InstancePtr, const char* InstanceName);
int XShortest_Release(XShortest *InstancePtr);
#endif


void XShortest_Set_src(XShortest *InstancePtr, u32 Data);
u32 XShortest_Get_src(XShortest *InstancePtr);
void XShortest_Set_col(XShortest *InstancePtr, u64 Data);
u64 XShortest_Get_col(XShortest *InstancePtr);
void XShortest_Set_nzr(XShortest *InstancePtr, u64 Data);
u64 XShortest_Get_nzr(XShortest *InstancePtr);
void XShortest_Set_visited(XShortest *InstancePtr, u64 Data);
u64 XShortest_Get_visited(XShortest *InstancePtr);
void XShortest_Set_q(XShortest *InstancePtr, u64 Data);
u64 XShortest_Get_q(XShortest *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
