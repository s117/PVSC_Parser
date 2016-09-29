#ifndef __H_INST_OP55
#define __H_INST_OP55

#include "InstPluginInterface.h"
#include "DSC_Info.h"
#include "DSC_Inst.h"

class Inst_op_55 :
    public DSC_Inst {
public:
    virtual STEP parse_inst(IN const uint8_t* sequence, IN uint32_t len_sequence);
    Inst_op_55();
    Inst_op_55(DSC_Info* info);
    ~Inst_op_55();
};

#endif
