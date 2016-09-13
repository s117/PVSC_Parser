#ifndef __H_DSC_INFO
#define __H_DSC_INFO

#include "GlobalDef.h"



class DSC_Info {
public:
    enum VERSION {F, F2, X};

    uint32_t base_time;
    VERSION ver;
    ENDIAN_TYPE endian;
    uint32_t payload_len;
};

#endif
