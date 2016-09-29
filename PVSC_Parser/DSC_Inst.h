//
//  Inst_DSC.hpp
//  PVSC_Parser
//
//  Created by s117 on 16/9/30.
//  Copyright © 2016年 s117. All rights reserved.
//

#ifndef __H_INST_DSC
#define __H_INST_DSC

#include <stdio.h>
#include "GlobalDef.h"
#include "DSC_Info.h"
#include "EngineCore.h"

class DSC_Inst :
    public InstPluginInterface {
public:
    virtual bool register_inst(IN EngineCore* engine, OUT uint32_t* opcode);
    virtual bool unregister_inst(IN EngineCore* engine);
    virtual STEP parse_inst(IN const uint8_t* sequence, IN uint32_t len_sequence);
    void set_info(DSC_Info* info);
    DSC_Info* get_info();

    DSC_Inst(uint32_t OPCODE, uint32_t SIZE);
    DSC_Inst(uint32_t OPCODE, uint32_t SIZE, DSC_Info* info);
    ~DSC_Inst();
protected:
    EngineCore* core = nullptr;
    DSC_Info* info = nullptr;
    uint32_t opcode;
    uint32_t size;
};

#endif /* Inst_DSC_hpp */
