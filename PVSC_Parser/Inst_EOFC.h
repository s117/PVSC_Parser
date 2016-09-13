//
//  Inst_EOFC.hpp
//  PVSC_Parser
//
//  Created by s117 on 16/9/13.
//  Copyright © 2016年 s117. All rights reserved.
//

#ifndef __H_INST_EOFC
#define __H_INST_EOFC

#include "InstPluginInterface.h"
#include "DSC_Info.h"

class Inst_EOFC :
    public InstPluginInterface {
public:
    virtual bool register_inst(IN EngineCore* engine, OUT uint32_t* opcode);
    virtual bool unregister_inst(IN EngineCore* engine);
    virtual STEP parse_inst(IN const uint8_t* sequence, IN uint32_t len_sequence);
    Inst_EOFC(DSC_Info* info);
    ~Inst_EOFC();
private:
    EngineCore* core = nullptr;
    DSC_Info* info = nullptr;
    uint32_t opcode;
};

#endif /* Inst_EOFC_hpp */
