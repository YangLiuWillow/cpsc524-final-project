// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.1 (64-bit)
// Tool Version Limit: 2022.04
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// sqrt
// 0x00 : reserved
// 0x04 : reserved
// 0x08 : reserved
// 0x0c : reserved
// 0x10 : Data signal of src
//        bit 31~0 - src[31:0] (Read/Write)
// 0x14 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XSHORTEST_SQRT_ADDR_SRC_DATA 0x10
#define XSHORTEST_SQRT_BITS_SRC_DATA 32

// control
// 0x00 : reserved
// 0x04 : reserved
// 0x08 : reserved
// 0x0c : reserved
// 0x10 : Data signal of col
//        bit 31~0 - col[31:0] (Read/Write)
// 0x14 : Data signal of col
//        bit 31~0 - col[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of nzr
//        bit 31~0 - nzr[31:0] (Read/Write)
// 0x20 : Data signal of nzr
//        bit 31~0 - nzr[63:32] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of visited
//        bit 31~0 - visited[31:0] (Read/Write)
// 0x2c : Data signal of visited
//        bit 31~0 - visited[63:32] (Read/Write)
// 0x30 : reserved
// 0x34 : Data signal of q
//        bit 31~0 - q[31:0] (Read/Write)
// 0x38 : Data signal of q
//        bit 31~0 - q[63:32] (Read/Write)
// 0x3c : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XSHORTEST_CONTROL_ADDR_COL_DATA     0x10
#define XSHORTEST_CONTROL_BITS_COL_DATA     64
#define XSHORTEST_CONTROL_ADDR_NZR_DATA     0x1c
#define XSHORTEST_CONTROL_BITS_NZR_DATA     64
#define XSHORTEST_CONTROL_ADDR_VISITED_DATA 0x28
#define XSHORTEST_CONTROL_BITS_VISITED_DATA 64
#define XSHORTEST_CONTROL_ADDR_Q_DATA       0x34
#define XSHORTEST_CONTROL_BITS_Q_DATA       64

