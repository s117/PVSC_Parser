//
//  EndianUtils.hpp
//  PVSC_Parser
//
//  Created by s117 on 16/9/13.
//  Copyright © 2016年 s117. All rights reserved.
//

#ifndef EndianUtils_hpp
#define EndianUtils_hpp

#include <stdio.h>
#include <stdint.h>




#define __UINT32_ADDR_DEREF(p, offset) (*(uint32_t*)(((uint8_t*)(p))+(offset)))

static inline uint32_t ENDIAN_REVERSE_32(uint32_t src) {
    return (((src << 8) & 0x00ff0000) | ((src << 24) & 0xff000000) | ((src >> 8) & 0x0000ff00) | ((src >> 24) & 0x000000ff));
}

static inline uint32_t __GET_UINT32_WITH_REVERSE(uint32_t* addr) {
    uint32_t raw = __UINT32_ADDR_DEREF(addr,0);
    return ENDIAN_REVERSE_32(raw);
}

static inline uint32_t __GET_UINT32_RAW(uint32_t* addr) {
    return __UINT32_ADDR_DEREF(addr,0);
}

#ifdef _MACH_BE
#define LE32(addr) __GET_UINT32_WITH_REVERSE((addr))
#define BE32(addr) __GET_UINT32_RAW((addr))
#define DEF32_HEX(byte0, byte1, byte2, byte3) (0x##byte0##byte1##byte2##byte3)
#else
#define LE32(addr) __GET_UINT32_RAW((addr))
#define BE32(addr) __GET_UINT32_WITH_REVERSE((addr))
#define DEF32_HEX(byte0, byte1, byte2, byte3) (0x##byte3##byte2##byte1##byte0)
#endif


enum ENDIAN_TYPE {ENDIAN_BE = 0, ENDIAN_LE};

static inline uint32_t DATA32(ENDIAN_TYPE endian, uint32_t* addr) {
    if(endian == ENDIAN_BE)
        return BE32(addr);
    else
        return LE32(addr);
}


#endif /* EndianUtils_hpp */
