// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xshortest.h"

extern XShortest_Config XShortest_ConfigTable[];

XShortest_Config *XShortest_LookupConfig(u16 DeviceId) {
	XShortest_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XSHORTEST_NUM_INSTANCES; Index++) {
		if (XShortest_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XShortest_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XShortest_Initialize(XShortest *InstancePtr, u16 DeviceId) {
	XShortest_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XShortest_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XShortest_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

