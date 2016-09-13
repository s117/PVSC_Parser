#ifndef __H_INST_OP55
#define __H_INST_OP55

#include "InstPluginInterface.h"
#include "DSC_Info.h"

class Inst_op_55 :
    public InstPluginInterface {
public:
    virtual bool register_inst(IN EngineCore* engine, OUT uint32_t* opcode);
    virtual bool unregister_inst(IN EngineCore* engine);
    virtual STEP parse_inst(IN const uint8_t* sequence, IN uint32_t len_sequence);
    Inst_op_55(DSC_Info* info);
    ~Inst_op_55();
private:
    EngineCore* core = nullptr;
    DSC_Info* info = nullptr;
    uint32_t opcode;
};

#endif
