// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xshortest.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XShortest_CfgInitialize(XShortest *InstancePtr, XShortest_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Sqrt_BaseAddress = ConfigPtr->Sqrt_BaseAddress;
    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XShortest_Set_src(XShortest *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XShortest_WriteReg(InstancePtr->Sqrt_BaseAddress, XSHORTEST_SQRT_ADDR_SRC_DATA, Data);
}

u32 XShortest_Get_src(XShortest *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XShortest_ReadReg(InstancePtr->Sqrt_BaseAddress, XSHORTEST_SQRT_ADDR_SRC_DATA);
    return Data;
}

void XShortest_Set_column_indices(XShortest *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XShortest_WriteReg(InstancePtr->Control_BaseAddress, XSHORTEST_CONTROL_ADDR_COLUMN_INDICES_DATA, (u32)(Data));
    XShortest_WriteReg(InstancePtr->Control_BaseAddress, XSHORTEST_CONTROL_ADDR_COLUMN_INDICES_DATA + 4, (u32)(Data >> 32));
}

u64 XShortest_Get_column_indices(XShortest *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XShortest_ReadReg(InstancePtr->Control_BaseAddress, XSHORTEST_CONTROL_ADDR_COLUMN_INDICES_DATA);
    Data += (u64)XShortest_ReadReg(InstancePtr->Control_BaseAddress, XSHORTEST_CONTROL_ADDR_COLUMN_INDICES_DATA + 4) << 32;
    return Data;
}

void XShortest_Set_row_offsets(XShortest *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XShortest_WriteReg(InstancePtr->Control_BaseAddress, XSHORTEST_CONTROL_ADDR_ROW_OFFSETS_DATA, (u32)(Data));
    XShortest_WriteReg(InstancePtr->Control_BaseAddress, XSHORTEST_CONTROL_ADDR_ROW_OFFSETS_DATA + 4, (u32)(Data >> 32));
}

u64 XShortest_Get_row_offsets(XShortest *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XShortest_ReadReg(InstancePtr->Control_BaseAddress, XSHORTEST_CONTROL_ADDR_ROW_OFFSETS_DATA);
    Data += (u64)XShortest_ReadReg(InstancePtr->Control_BaseAddress, XSHORTEST_CONTROL_ADDR_ROW_OFFSETS_DATA + 4) << 32;
    return Data;
}

void XShortest_Set_visited(XShortest *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XShortest_WriteReg(InstancePtr->Control_BaseAddress, XSHORTEST_CONTROL_ADDR_VISITED_DATA, (u32)(Data));
    XShortest_WriteReg(InstancePtr->Control_BaseAddress, XSHORTEST_CONTROL_ADDR_VISITED_DATA + 4, (u32)(Data >> 32));
}

u64 XShortest_Get_visited(XShortest *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XShortest_ReadReg(InstancePtr->Control_BaseAddress, XSHORTEST_CONTROL_ADDR_VISITED_DATA);
    Data += (u64)XShortest_ReadReg(InstancePtr->Control_BaseAddress, XSHORTEST_CONTROL_ADDR_VISITED_DATA + 4) << 32;
    return Data;
}

void XShortest_Set_queue(XShortest *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XShortest_WriteReg(InstancePtr->Control_BaseAddress, XSHORTEST_CONTROL_ADDR_QUEUE_DATA, (u32)(Data));
    XShortest_WriteReg(InstancePtr->Control_BaseAddress, XSHORTEST_CONTROL_ADDR_QUEUE_DATA + 4, (u32)(Data >> 32));
}

u64 XShortest_Get_queue(XShortest *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XShortest_ReadReg(InstancePtr->Control_BaseAddress, XSHORTEST_CONTROL_ADDR_QUEUE_DATA);
    Data += (u64)XShortest_ReadReg(InstancePtr->Control_BaseAddress, XSHORTEST_CONTROL_ADDR_QUEUE_DATA + 4) << 32;
    return Data;
}

