//
//  Inst_nop.hpp
//  PVSC_Parser
//
//  Created by s117 on 16/9/13.
//  Copyright © 2016年 s117. All rights reserved.
//

#ifndef __H_INST_NOP
#define __H_INST_NOP

#include "InstPluginInterface.h"
#include "DSC_Info.h"

class Inst_nop :
    public InstPluginInterface {
public:
    virtual bool register_inst(IN EngineCore* engine, OUT uint32_t* opcode);
    virtual bool unregister_inst(IN EngineCore* engine);
    virtual STEP parse_inst(IN const uint8_t* sequence, IN uint32_t len_sequence);
    Inst_nop(DSC_Info* info);
    ~Inst_nop();
private:
    EngineCore* core = nullptr;
    DSC_Info* info = nullptr;
    uint32_t opcode;
};

#endif /* Inst_nop_hpp */
