#ifndef __H_TIMESTAMP
#define __H_TIMESTAMP

#include "InstPluginInterface.h"
#include "DSC_Info.h"
#include "DSC_Inst.h"

class Inst_Timestamp :
    public DSC_Inst {
public:
    virtual STEP parse_inst(IN const uint8_t* sequence, IN uint32_t len_sequence);
    Inst_Timestamp();
    Inst_Timestamp(DSC_Info* info);
    ~Inst_Timestamp();
};

#endif
