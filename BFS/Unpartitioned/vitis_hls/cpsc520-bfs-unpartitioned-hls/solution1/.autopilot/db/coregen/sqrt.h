// 0x00 : reserved
// 0x04 : reserved
// 0x08 : reserved
// 0x0c : reserved
// 0x10 : Data signal of src
//        bit 31~0 - src[31:0] (Read/Write)
// 0x14 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define SQRT_ADDR_SRC_DATA 0x10
#define SQRT_BITS_SRC_DATA 32
