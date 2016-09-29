#ifndef __H_INST_NOTE
#define __H_INST_NOTE

#include "InstPluginInterface.h"
#include "DSC_Info.h"
#include "DSC_Inst.h"

class Inst_Note :
    public DSC_Inst {
public:
    virtual STEP parse_inst(IN const uint8_t* sequence, IN uint32_t len_sequence);
    Inst_Note();
    Inst_Note(DSC_Info* info);
    ~Inst_Note();
};

#endif
